# generated from rosidl_generator_py/resource/_idl.py.em
# with input from race_orchestrator:msg/RaceStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'current_position'
# Member 'next_checkpoint'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RaceStatus(type):
    """Metaclass of message 'RaceStatus'."""

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
            module = import_type_support('race_orchestrator')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'race_orchestrator.msg.RaceStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__race_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__race_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__race_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__race_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__race_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RaceStatus(metaclass=Metaclass_RaceStatus):
    """Message class 'RaceStatus'."""

    __slots__ = [
        '_race_id',
        '_robot_id',
        '_current_time',
        '_remaining_time',
        '_current_object',
        '_objects_collected',
        '_total_objects',
        '_current_position',
        '_next_checkpoint',
        '_race_completed',
        '_race_failed',
        '_failure_reason',
    ]

    _fields_and_field_types = {
        'race_id': 'string',
        'robot_id': 'string',
        'current_time': 'float',
        'remaining_time': 'float',
        'current_object': 'string',
        'objects_collected': 'int32',
        'total_objects': 'int32',
        'current_position': 'sequence<float>',
        'next_checkpoint': 'sequence<float>',
        'race_completed': 'boolean',
        'race_failed': 'boolean',
        'failure_reason': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.race_id = kwargs.get('race_id', str())
        self.robot_id = kwargs.get('robot_id', str())
        self.current_time = kwargs.get('current_time', float())
        self.remaining_time = kwargs.get('remaining_time', float())
        self.current_object = kwargs.get('current_object', str())
        self.objects_collected = kwargs.get('objects_collected', int())
        self.total_objects = kwargs.get('total_objects', int())
        self.current_position = array.array('f', kwargs.get('current_position', []))
        self.next_checkpoint = array.array('f', kwargs.get('next_checkpoint', []))
        self.race_completed = kwargs.get('race_completed', bool())
        self.race_failed = kwargs.get('race_failed', bool())
        self.failure_reason = kwargs.get('failure_reason', str())

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
        if self.race_id != other.race_id:
            return False
        if self.robot_id != other.robot_id:
            return False
        if self.current_time != other.current_time:
            return False
        if self.remaining_time != other.remaining_time:
            return False
        if self.current_object != other.current_object:
            return False
        if self.objects_collected != other.objects_collected:
            return False
        if self.total_objects != other.total_objects:
            return False
        if self.current_position != other.current_position:
            return False
        if self.next_checkpoint != other.next_checkpoint:
            return False
        if self.race_completed != other.race_completed:
            return False
        if self.race_failed != other.race_failed:
            return False
        if self.failure_reason != other.failure_reason:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def race_id(self):
        """Message field 'race_id'."""
        return self._race_id

    @race_id.setter
    def race_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'race_id' field must be of type 'str'"
        self._race_id = value

    @builtins.property
    def robot_id(self):
        """Message field 'robot_id'."""
        return self._robot_id

    @robot_id.setter
    def robot_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'robot_id' field must be of type 'str'"
        self._robot_id = value

    @builtins.property
    def current_time(self):
        """Message field 'current_time'."""
        return self._current_time

    @current_time.setter
    def current_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current_time = value

    @builtins.property
    def remaining_time(self):
        """Message field 'remaining_time'."""
        return self._remaining_time

    @remaining_time.setter
    def remaining_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'remaining_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'remaining_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._remaining_time = value

    @builtins.property
    def current_object(self):
        """Message field 'current_object'."""
        return self._current_object

    @current_object.setter
    def current_object(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'current_object' field must be of type 'str'"
        self._current_object = value

    @builtins.property
    def objects_collected(self):
        """Message field 'objects_collected'."""
        return self._objects_collected

    @objects_collected.setter
    def objects_collected(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'objects_collected' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'objects_collected' field must be an integer in [-2147483648, 2147483647]"
        self._objects_collected = value

    @builtins.property
    def total_objects(self):
        """Message field 'total_objects'."""
        return self._total_objects

    @total_objects.setter
    def total_objects(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_objects' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'total_objects' field must be an integer in [-2147483648, 2147483647]"
        self._total_objects = value

    @builtins.property
    def current_position(self):
        """Message field 'current_position'."""
        return self._current_position

    @current_position.setter
    def current_position(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'current_position' array.array() must have the type code of 'f'"
            self._current_position = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'current_position' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._current_position = array.array('f', value)

    @builtins.property
    def next_checkpoint(self):
        """Message field 'next_checkpoint'."""
        return self._next_checkpoint

    @next_checkpoint.setter
    def next_checkpoint(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'next_checkpoint' array.array() must have the type code of 'f'"
            self._next_checkpoint = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'next_checkpoint' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._next_checkpoint = array.array('f', value)

    @builtins.property
    def race_completed(self):
        """Message field 'race_completed'."""
        return self._race_completed

    @race_completed.setter
    def race_completed(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'race_completed' field must be of type 'bool'"
        self._race_completed = value

    @builtins.property
    def race_failed(self):
        """Message field 'race_failed'."""
        return self._race_failed

    @race_failed.setter
    def race_failed(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'race_failed' field must be of type 'bool'"
        self._race_failed = value

    @builtins.property
    def failure_reason(self):
        """Message field 'failure_reason'."""
        return self._failure_reason

    @failure_reason.setter
    def failure_reason(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'failure_reason' field must be of type 'str'"
        self._failure_reason = value
