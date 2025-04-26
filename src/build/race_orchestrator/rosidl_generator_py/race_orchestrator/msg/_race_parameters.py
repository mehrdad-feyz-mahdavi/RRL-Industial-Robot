# generated from rosidl_generator_py/resource/_idl.py.em
# with input from race_orchestrator:msg/RaceParameters.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'checkpoints'
# Member 'start_position'
# Member 'goal_position'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RaceParameters(type):
    """Metaclass of message 'RaceParameters'."""

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
                'race_orchestrator.msg.RaceParameters')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__race_parameters
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__race_parameters
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__race_parameters
            cls._TYPE_SUPPORT = module.type_support_msg__msg__race_parameters
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__race_parameters

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RaceParameters(metaclass=Metaclass_RaceParameters):
    """Message class 'RaceParameters'."""

    __slots__ = [
        '_race_id',
        '_object_sequence',
        '_time_limit',
        '_checkpoints',
        '_enable_obstacles',
        '_obstacle_density',
        '_start_position',
        '_goal_position',
    ]

    _fields_and_field_types = {
        'race_id': 'string',
        'object_sequence': 'sequence<string>',
        'time_limit': 'float',
        'checkpoints': 'sequence<float>',
        'enable_obstacles': 'boolean',
        'obstacle_density': 'float',
        'start_position': 'sequence<float>',
        'goal_position': 'sequence<float>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.race_id = kwargs.get('race_id', str())
        self.object_sequence = kwargs.get('object_sequence', [])
        self.time_limit = kwargs.get('time_limit', float())
        self.checkpoints = array.array('f', kwargs.get('checkpoints', []))
        self.enable_obstacles = kwargs.get('enable_obstacles', bool())
        self.obstacle_density = kwargs.get('obstacle_density', float())
        self.start_position = array.array('f', kwargs.get('start_position', []))
        self.goal_position = array.array('f', kwargs.get('goal_position', []))

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
        if self.object_sequence != other.object_sequence:
            return False
        if self.time_limit != other.time_limit:
            return False
        if self.checkpoints != other.checkpoints:
            return False
        if self.enable_obstacles != other.enable_obstacles:
            return False
        if self.obstacle_density != other.obstacle_density:
            return False
        if self.start_position != other.start_position:
            return False
        if self.goal_position != other.goal_position:
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
    def object_sequence(self):
        """Message field 'object_sequence'."""
        return self._object_sequence

    @object_sequence.setter
    def object_sequence(self, value):
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
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'object_sequence' field must be a set or sequence and each value of type 'str'"
        self._object_sequence = value

    @builtins.property
    def time_limit(self):
        """Message field 'time_limit'."""
        return self._time_limit

    @time_limit.setter
    def time_limit(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'time_limit' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'time_limit' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._time_limit = value

    @builtins.property
    def checkpoints(self):
        """Message field 'checkpoints'."""
        return self._checkpoints

    @checkpoints.setter
    def checkpoints(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'checkpoints' array.array() must have the type code of 'f'"
            self._checkpoints = value
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
                "The 'checkpoints' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._checkpoints = array.array('f', value)

    @builtins.property
    def enable_obstacles(self):
        """Message field 'enable_obstacles'."""
        return self._enable_obstacles

    @enable_obstacles.setter
    def enable_obstacles(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'enable_obstacles' field must be of type 'bool'"
        self._enable_obstacles = value

    @builtins.property
    def obstacle_density(self):
        """Message field 'obstacle_density'."""
        return self._obstacle_density

    @obstacle_density.setter
    def obstacle_density(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'obstacle_density' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'obstacle_density' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._obstacle_density = value

    @builtins.property
    def start_position(self):
        """Message field 'start_position'."""
        return self._start_position

    @start_position.setter
    def start_position(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'start_position' array.array() must have the type code of 'f'"
            self._start_position = value
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
                "The 'start_position' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._start_position = array.array('f', value)

    @builtins.property
    def goal_position(self):
        """Message field 'goal_position'."""
        return self._goal_position

    @goal_position.setter
    def goal_position(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'goal_position' array.array() must have the type code of 'f'"
            self._goal_position = value
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
                "The 'goal_position' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._goal_position = array.array('f', value)
