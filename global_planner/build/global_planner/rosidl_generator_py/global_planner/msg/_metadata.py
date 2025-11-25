# generated from rosidl_generator_py/resource/_idl.py.em
# with input from global_planner:msg/Metadata.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Metadata(type):
    """Metaclass of message 'Metadata'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('global_planner')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'global_planner.msg.Metadata')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__metadata
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__metadata
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__metadata
            cls._TYPE_SUPPORT = module.type_support_msg__msg__metadata
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__metadata

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Metadata(metaclass=Metaclass_Metadata):
    """Message class 'Metadata'."""

    __slots__ = [
        '_average_speed',
        '_total_time',
        '_lap_time',
    ]

    _fields_and_field_types = {
        'average_speed': 'float',
        'total_time': 'float',
        'lap_time': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.average_speed = kwargs.get('average_speed', float())
        self.total_time = kwargs.get('total_time', float())
        self.lap_time = kwargs.get('lap_time', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.average_speed != other.average_speed:
            return False
        if self.total_time != other.total_time:
            return False
        if self.lap_time != other.lap_time:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def average_speed(self):
        """Message field 'average_speed'."""
        return self._average_speed

    @average_speed.setter
    def average_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'average_speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'average_speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._average_speed = value

    @builtins.property
    def total_time(self):
        """Message field 'total_time'."""
        return self._total_time

    @total_time.setter
    def total_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'total_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'total_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._total_time = value

    @builtins.property
    def lap_time(self):
        """Message field 'lap_time'."""
        return self._lap_time

    @lap_time.setter
    def lap_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'lap_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'lap_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._lap_time = value
