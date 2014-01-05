import logging


class BaseHandler(object):
    """
        Base handler class. Sets up logging. Used for All Handling.
    """

    logger = logging.getLogger(__name__ + ".BaseHandler")
    request = None
    context = None

    def __init__(self, context, request):
        ''' 
            Initializes the logging, request, and context. 
        '''
        self.logger.debug("in %s __init__" % self.__class__.__name__)
        self.request = request
        self.context = context

    def now(self):
        import datetime
        return datetime.datetime.now()


class APIHandler(BaseHandler):
    """
        API handler class. Used for Handling REST requests.
    """

    response = None
    return_format = "JSON"
    params = {}
    status_code = 500
    error_msg = ''
    
    def __init__(self, context, request):
        ''' 
            Route the request method type to the proper function.
        '''
        super(APIHandler, self).__init__(context, request)
        self.status_code = 200
        self.error_msg = ''
        self.params = request.params
        #Check to route to the right function based on request method
        if self.request.method == 'GET':
            self.response = self._get()
        elif self.request.method == 'POST':
            self.response = self._post()
        elif self.request.method == 'PUT':
            self.response = self._put()
        elif self.request.method == 'DELETE':
            self.response = self._delete()

    def json_response(self, payload=None, status_code=200, error_msg=None):
        ''' Constructs a response body for handling by the JSON renderer '''
        import json

        return json.dumps({
            "status_code": status_code,
            "response": "" if payload is None else payload,
        })

    def api_response(self, payload=None, status_code=200, error_msg=None):
        ''' 
            Create a Response object with headers
            Prepare a standard API response 
            TODO Add a CASE statement to handle response types
        '''
        from pyramid.response import Response
        from cgi import escape
        if payload is not None:
            self.response = payload
        response = self.response
        self.request.response.status_code = status_code
        new_response = Response(status=status_code, content_type='application/json')
        if isinstance(self.response, Response):
            try:
                response = self.response.json_body
            except:
                response = self.response.body
        elif self.response is None:
            self.request.response.status_code = 404
            status_code = 404
            error_msg = "Nothing here"
        json_body = self.json_response(response, status_code, error_msg)
        new_response.body = json_body
        new_response.body = escape(new_response.body)
        return new_response

    def render_resource(self):
        ''' Return the returnables in the correct format with data '''
        return self.api_response(status_code=self.status_code,
                                 error_msg=self.error_msg)
