from sqlalchemy import (
    Column,
    Index,
    Integer,
    Text,
    String,
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
    user = Column(String(50), unique=True)

    def __init__(self, user):
        self.user = user


class Session(Base):
    __tablename__ = 'sessions'
    id = Column(Integer, primary_key=True)
    value = Column(String(255))

    def __init__(self, value):
        self.value = value


class AppRoot(object):
    """
        Traversal application root object
    """
    __name__ = None
    __parent__ = None

    def __init__(self, request):
        ''' initialize the root with a user object '''
        from zenbattle.factories.base import (UserFactory, SessionFactory)
        self.request = request
        self.dict['zen'] = {'user': UserFactory(), 'session': SessionFactory()}
    def __getitem__(self, key):
        LOGGER.debug("AppRoot.__getitem__ called with key %s" % key)
        #item = self.dict[key]
        item = self.dict.get(key)
        LOGGER.debug("returning %r" % item)
        return item

def root_factory(request):
    ''' Get the factory for the traversal process. '''
    return AppRoot(request)

def appmaker(engine):
    ''' Set up the app '''
    return root_factory