import transaction

from sqlalchemy import desc
from sqlalchemy.exc import IntegrityError, ResourceClosedError
from sqlalchemy.orm.exc import FlushError

from zenbattle.models import DBSession, LOGGER
from zenbattle.models import (User, Session)

from functools import wraps


def safe_db_access(f):
    """
    Wraps the function in a single transaction detaches the returned models.
    f can be any method which returns a sequence of models
    models returned can be used without fear of unintended sql updates
    """
    @wraps(f)
    def wrapper(*args, **kwargs):
        session = DBSession()
        session.begin(subtransactions=True)
        try:
            models = f(*args, **kwargs)
            [session.expunge(m) for m in models]
        except:
            transaction.abort()
            raise
        return models
    return wrapper


class BaseFactory(object):
    """
        Base factory providing basic CRUD operations.
    """

    def __init__(self, type_):
        self.type = type_

    def _check_for_id(self, obj_):
        if "id" not in  obj_.__dict__:
            return False
        return True

    def get_count(self, filters=[]):
        from sqlalchemy import func
        session = DBSession()
        session.expire_on_commit = False
        query = session.query(func.count(self.type.id))
        if len(filters):
            query = query.filter(*filters)
        return query.scalar()

    def get_query(self, limit=None, sort=None, reversed=False, filters=[]):
        ''' Get a query of my type '''
        session = DBSession()
        session.expire_on_commit = False
        query = session.query(self.type)
        if len(filters):
            query = query.filter(*filters)
        if sort is not None:
            query = query.order_by(sort)
        elif reversed:
            query = query.order_by(self.type.id.desc())
        if limit is not None:
            query = query.limit(limit)
        return query

    def mutable_get(self, limit=None, sort=None, reversed=False, filters=[]):
        return self.get_query(limit=limit, sort=sort, reversed=reversed,
                              filters=filters).all()

    @safe_db_access
    def get(self, *args, **kwargs):
        return self.mutable_get(*args, **kwargs)

    @safe_db_access
    def filter_by(self, **kwargs):
        ''' Retrieve a query filtered by the kwargs '''
        query = self.get_query()
        return query.filter_by(**kwargs)

    def get_by_attribute(self, attribute, value):
        ''' Get the item with the given name '''
        args = {attribute: value}
        return self.filter_by(**args).scalar()

    def get_all_by_attribute(self, attribute, value):
        ''' Get the item with the given name '''
        args = {attribute: value}
        return self.filter_by(**args).all()

    def get_by_id(self, id_):
        ''' Retrieve the object with the given id. '''
        int_id = int(id_)
        return self.filter_by(id=int_id).scalar()

    def delete(self, id_):
        ''' Delete the object with the given id. '''
        session = DBSession()
        session.expire_on_commit = False
        LOGGER.debug("delete received id %s" % id_)
        object_ = self.get_by_id(id_)
        if object_ is not None:
            session.delete(object_)
            session.flush()
            transaction.commit()
        else:
            LOGGER.debug("tried deleting a nonexistent item")

    def delete_obj(self, object_):
        '''
        Delete the object
        :param object_: The actual object being deleted
        '''
        if object_ is not None:
            session = DBSession()
            session.expire_on_commit = False
            session.delete(object_)
            session.flush()
            transaction.commit()
        else:
            LOGGER.debug("tried deleting a nonexistent item")

    def add(self, object_):
        ''' Add the given object to the system. '''
        session = DBSession()
        session.expire_on_commit = False
        has_id = False
        if object_ is None:
            raise Exception('None type object received')
        try:
            session.add(object_)
            session.flush()
            has_id = self._check_for_id(object_)
            if has_id:
                obj_id = object_.id
            transaction.commit()
        except IntegrityError, FlushError:
            session.rollback()
            transaction.abort()
            raise
        except ResourceClosedError:
            transaction.abort()
            raise
        if has_id:
            return self.get_by_id(obj_id)
        return object_

    def merge(self, object_):
        ''' Update object when obj is not currently in session scope '''
        session = DBSession()
        session.expire_on_commit = False
        if object_ is None:
            raise Exception('None type object received')
        try:
            assert object_ not in session
            obj = session.merge(object_)
            obj_id = obj.id
            session.flush()
            transaction.commit()
        except IntegrityError:
            session.rollback()
            transaction.abort()
            raise
        except ResourceClosedError:
            transaction.abort()
            raise
        return self.get_by_id(obj_id)

    def update(self, object_):
        ''' Update object '''
        session = DBSession()
        session.expire_on_commit = False
        has_id = self._check_for_id(object_)
        if object_ is None:
            raise Exception('None type object received')
        try:
            obj = None
            obj_id = None
            if has_id:
                obj = self.get_by_id(object_.id)
                obj_id = obj.id
            obj = object_
            session.flush()
            transaction.commit()
        except IntegrityError:
            session.rollback()
            transaction.abort()
            raise
        except ResourceClosedError:
            transaction.abort()
            raise
        if has_id:
            return self.get_by_id(obj_id)
        return obj

    def in_session(self, object_):
        session = DBSession()
        if object_ not in session:
            return False
        return True


class SessionFactory(BaseFactory):

    def __init__(self):
        BaseFactory.__init__(self, Session)

    def create_session(self, value):
        session = Session(value)
        return self.add(session)

    def get_session(self, value):
        return self.get_query([self.type.value==value]).scalar()

    def remove(self, app_key, value):
        session = self.get_query([self.type.value==value]).scalar()
        if session is not None:
            self.delete(session.id)

    
class UserFactory(BaseFactory):

    def __init__(self):
        BaseFactory.__init__(self, User)

    def create_user(self, user_info):
        user = self.type(user_info)
        return self.add(user)

