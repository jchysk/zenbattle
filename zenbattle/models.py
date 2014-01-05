import logging
from sqlalchemy import (
    Column,
    Index,
    Integer,
    Text,
    String,
    Float,
    DateTime,
    Boolean,
    )

from sqlalchemy.ext.declarative import declarative_base

from sqlalchemy.orm import (
    scoped_session,
    sessionmaker,
    )

from zope.sqlalchemy import ZopeTransactionExtension

DBSession = scoped_session(sessionmaker(extension=ZopeTransactionExtension()))
Base = declarative_base()
LOGGER = logging.getLogger(__name__)


class User(Base):
    """ Have user object identified by unique identifier given from API """
    __tablename__ = 'users'
    id = Column(Integer, primary_key=True)
    user = Column(String(150), unique=True)

    def __init__(self, user):
        self.user = user


class Session(Base):
    __tablename__ = 'sessions'
    id = Column(Integer, primary_key=True)
    value = Column(String(255))

    def __init__(self, value):
        self.value = value


class Game(Base):
    __tablename__ = 'games'
    id = Column(Integer, primary_key=True)
    start_time = Column(DateTime)
    run_time = Column(DateTime)
    player_id = Column(Integer)
    player1_score = Column(Float)
    player2_score = Column(Float)
    purse = Column(Integer)
    status = Column(Boolean)

    def __init__(self, player_id, purse):
        import datetime
        self.start_time = datetime.datetime.now()
        self.player_id = player_id
        self.purse = purse
        self.status = True


class GameData(Base):
    __tablename__ = 'gamedata'
    id = Column(Integer, primary_key=True)
    game_id = Column(Integer)
    user_id = Column(Integer)
    attention = Column(Integer)
    meditation = Column(Integer)
    date_created = Column(DateTime)

    def __init__(self, game_id, user_id, attention, meditation):
        import datetime
        self.game_id = game_id
        self.user_id = user_id
        self.attention = attention
        self.meditation = meditation
        self.date_created = datetime.datetime.now()


class AppRoot(object):
    """
        Traversal application root object
    """
    __name__ = None
    __parent__ = None

    def __init__(self, request):
        ''' initialize the root with a user object '''
        from zenbattle.factories.base import (UserFactory, SessionFactory, GameFactory)
        self.request = request
        self.dict = {}
        self.dict['zen'] = {'user': UserFactory(), 'session': SessionFactory(), 'game': GameFactory()}
    def __getitem__(self, key):
        LOGGER.debug("AppRoot.__getitem__ called with key %s" % key)
        #item = self.dict[key]
        item = self.dict.get(key)
        LOGGER.debug("returning %r" % item)
        return item

def root_factory(request):
    ''' Get the factory for the traversal process. '''
    return AppRoot(request)

def initialize_sql(engine, test=False):
    """ setup the db engine """
    DBSession.configure(bind=engine)
    Base.metadata.bind = engine
    if test:
        Base.metadata.drop_all(engine)
    Base.metadata.create_all(engine)
    return DBSession

def appmaker(engine):
    ''' Set up the app '''
    initialize_sql(engine)
    return root_factory