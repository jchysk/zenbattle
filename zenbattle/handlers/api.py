from zenbattle.handlers.base import APIHandler


class Device(APIHandler):

    def _get(self):
        return {}

    def _post(self):
        '''
        Device registration
        Takes uuid
        Returns 4 digit unique game code
        '''
        print "\n\njson\n" + repr(self.request.json['uuid']) + "\n\n"
        uuid = self.request.json['uuid']
        user = self.context['user'].create_user(uuid)

        return {"user_id": user.id}


class EEG(APIHandler):

    def _post(self):
        '''
        Accept EEG JSON string and figure out strength
        Return Integer strength
        jsonData: {
 "poorSignal" : 25,
 "eegLowGamma" : 4306,
 "eegDelta" : 60270,
 "eSenseAttention" : 0,
 "eegHighBeta" : 708,
 "eegTheta" : 5205,
 "eegLowBeta" : 1559,
 "eSenseMeditation" : 0,
 "eegHighGamma" : 3506,
 "eegLowAlpha" : 3251,
 "eegHighAlpha" : 522,
 "rawCount" : 268
}
jsonData: {
 "blinkStrength" : 38

        Return a winner/loser when the game is over
}'''
        import datetime
        print "\n\nincoming\n" + repr(self.request.json)
        data = self.request.json
        uuid = data['uuid']
        #Find out if the uuid is mid-game
        user = self.context['user'].get_by_attribute("user", uuid)
        #Get game id
        if "game_id" not in data:
            self.status_code = 500
            return {"error": "requires game_id"}
        game_id = data['game_id']
        game = self.context['game'].get_active(user.id)
        if game is None:
            game = self.context['game'].get_by_id(game_id)
            if game is not None and game.status == "finished":
                #print out winner/loser and amount
                game_count = self.context['gamedata'].count(game_id)
                score1 = game.player1_score / game_count / game.purse
                score2 = game.player2_score / game_count / game.purse
                return {"status": "finished", str(game.player_id): score1,
                        str(game.player2_id): score2}
            return {"error": "what's it doing here?"}
        if game.id != game_id:
            return {"error": "wrong game"}

        attention = self.request.json['eSenseAttention']
        meditation = self.request.json['eSenseMeditation']
        self.context['gamedata'].create(game_id, user.id, attention, meditation)
        #Now figure out current score
        game_data = self.context['gamedata'].get_all_by_attribute('game_id', game_id) #order by date_created desc

        for count, each in enumerate(game_data):
            if each.user_id == game.player_id:
                is_player1 = True
            else:
                is_player1 = False
            current = each
            if count + 1 < len(game_data):
                prev = game_data[-(count + 2)]
                delta = current.date_created - prev.date_created
                milli = (delta.microseconds + delta.seconds * 1000000) / 1000
                incr = 2
                while prev.user_id == current.user_id and count + incr < len(game_data):
                    incr += 1
                    prev = game_data[-(count + incr)]
                #Sanity check
                if prev.user_id != current.user_id:
                    first = (current.attention - prev.attention) * milli / 1000.0
                    second = (prev.attention - current.attention) * milli / 1000.0
                    if is_player1:
                        game.player1_score += first
                        game.player2_score += second
                    else:
                        game.player2_score += first
                        game.player1_score += second
                else:
                    #Shouldn't get here except on first runs where another user hasn't posted
                    return {"error": "logic issues or perhaps first run?"}


        #If game just started set game start
        if game.start_time is None:
            game.start_time = datetime.datetime.now()
            self.context['game'].update(game)
        #End game if over
        if datetime.datetime.now() > game.start_time + datetime.timedelta(seconds=10):
            game.status = "finished"
            self.context['game'].update(game)
        game_count = self.context['gamedata'].count(game_id)
        score1 = game.player1_score / game_count / game.purse
        score2 = game.player2_score / game_count / game.purse
        return {"status": game.status, str(game.player_id): score1,
                str(game.player2_id): score2}


class Start(APIHandler):

    def _get(self):
        uuid = self.request.json['uuid']
        user = self.context['user'].get_by_attribute("user", uuid)
        if user is None:
            return {}
        game = self.context['game'].get_created(user.id)
        if game is not None:
            game.status = "started"
            self.context['game'].update(game)
            return {"game_id": game.id}
        return {}

    def _post(self):
        uuid = self.request.json['uuid']
        user_id = self.request.json['user_id']
        wager = self.request.json['wager']
        user = self.context['user'].get_by_id(int(user_id))
        print "\n\nuuid\n" + repr(uuid)
        user2 = self.context['user'].get_by_attribute("user", uuid)
        print "\n\nuser is \n" + repr(user) + "\n\n" + repr(user2) + "\n"
        if user is not None and user2 is not None and user.user != uuid:
            game = self.context['game'].create(user_id, user2.id, wager)
            return {"game_id": game.id}
        return {}


class Payment(APIHandler):

    def payment(self):
        import requests
        params = {"client_id": "yv59rvjxj43s99gbg7y3tn0j0yoe2jv0", "client_secret": "znerf47rbkfrls1zbqtoejkdmurjdoug",
                  "scope": "PAYMENT", "grant_type": "client_credentials"}
        response = requests.post("https://api.att.com/oauth/token", params=params)
        access_token = response.json()['access_token']
        merch = {"Description":"Payment Description","Category":"1","Amount":"0.00","Channel":"MOBILE_WEB","MerchantPaymentRedirectUrl":"http:\/\/localhost","MerchantProductId":"TransactionP1","MerchantTransactionId":"M4304771141"}
        headers = {}
        headers['Authorization'] = "Bearer " + access_token
        headers['Content-Type'] = "application/json"
        response = requests.post("https://api.att.com/Security/Notary/Rest/1/SignedPayload", headers=headers, params=params)
        print repr(response.text)

    def _get(self):
        #uuid
        return {"redirect_url": "http://redirect.url"}
