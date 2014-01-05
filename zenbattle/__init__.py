from pyramid.config import Configurator
from pyramid_beaker import session_factory_from_settings
from sqlalchemy import engine_from_config
from zenbattle.models import appmaker

def main(global_config, **settings):
    """ This function returns a Pyramid WSGI application.
    """
    engine = engine_from_config(settings, 'sqlalchemy.', encoding='utf-8')
    get_root = appmaker(engine)
    session_factory = session_factory_from_settings(settings)
    config = Configurator(settings=settings, root_factory=get_root)
    config.include('pyramid_handlers')
    config.include('pyramid_mako')
    config.set_session_factory(session_factory)

    #API endpoints
    config.add_handler("eeg", "/eeg*id", action="render_resource",
                       handler="zenbattle.handlers.api.EEG",
                       traverse='/zen')
    config.add_handler("device", "/device*id", action="render_resource",
                       handler="zenbattle.handlers.api.Device",
                       traverse='/zen')
    config.add_handler("start", "/start*id", action="render_resource",
                       handler="zenbattle.handlers.api.Start",
                       traverse='/zen')
    #config.add_route('home', '/')
    config.add_route

    config.scan()
    return config.make_wsgi_app()
