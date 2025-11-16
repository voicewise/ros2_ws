# generated from rosidl_generator_py/resource/_idl.py.em
# with input from puppy_control_msgs:msg/Gait.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Gait(type):
    """Metaclass of message 'Gait'."""

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
            module = import_type_support('puppy_control_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'puppy_control_msgs.msg.Gait')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__gait
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__gait
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__gait
            cls._TYPE_SUPPORT = module.type_support_msg__msg__gait
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__gait

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Gait(metaclass=Metaclass_Gait):
    """Message class 'Gait'."""

    __slots__ = [
        '_overlap_time',
        '_swing_time',
        '_clearance_time',
        '_z_clearance',
    ]

    _fields_and_field_types = {
        'overlap_time': 'float',
        'swing_time': 'float',
        'clearance_time': 'float',
        'z_clearance': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.overlap_time = kwargs.get('overlap_time', float())
        self.swing_time = kwargs.get('swing_time', float())
        self.clearance_time = kwargs.get('clearance_time', float())
        self.z_clearance = kwargs.get('z_clearance', float())

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
        if self.overlap_time != other.overlap_time:
            return False
        if self.swing_time != other.swing_time:
            return False
        if self.clearance_time != other.clearance_time:
            return False
        if self.z_clearance != other.z_clearance:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def overlap_time(self):
        """Message field 'overlap_time'."""
        return self._overlap_time

    @overlap_time.setter
    def overlap_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'overlap_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'overlap_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._overlap_time = value

    @builtins.property
    def swing_time(self):
        """Message field 'swing_time'."""
        return self._swing_time

    @swing_time.setter
    def swing_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'swing_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'swing_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._swing_time = value

    @builtins.property
    def clearance_time(self):
        """Message field 'clearance_time'."""
        return self._clearance_time

    @clearance_time.setter
    def clearance_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'clearance_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'clearance_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._clearance_time = value

    @builtins.property
    def z_clearance(self):
        """Message field 'z_clearance'."""
        return self._z_clearance

    @z_clearance.setter
    def z_clearance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'z_clearance' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'z_clearance' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._z_clearance = value
