from zenbattle.handlers.base import APIHandler


class Device(APIHandler):

    def _post(self):
        '''
        Device registration
        Takes uuid
        Returns 4 digit unique game code
        '''
        game = self.context['game'].create(self.params['uuid'])
        return {"game_id": game.id}


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
        return {}


class Session(APIHandler):

    def _post(self):
        return {}