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
}'''
        print "\n\nincoming\n" + repr(self.request.json)
        data = self.request.json
        uuid = data['uuid']

        return {}


class Start(APIHandler):

    def _get(self):
        uuid = self.request.json['uuid']
        user = self.context['user'].get_by_attribute("user", uuid)
        if user is None:
            return {}
        game = self.context['game'].get_active(user.id)
        if game is not None:
            return {"game_id": game.id}
        return {}

    def _post(self):
        uuid = self.request.json['uuid']
        user_id = self.request.json['user_id']
        wager = self.request.json['wager']
        user = self.context['user'].get_by_id(user_id)
        if user is not None and user.uuid != uuid:
            game = self.context['game'].create(user_id, wager)
            return {"game_id": game.id}
        return {}