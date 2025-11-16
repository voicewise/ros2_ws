// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from puppy_control_msgs:msg/Pose.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "puppy_control_msgs/msg/detail/pose__struct.h"
#include "puppy_control_msgs/msg/detail/pose__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool puppy_control_msgs__msg__pose__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[34];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("puppy_control_msgs.msg._pose.Pose", full_classname_dest, 33) == 0);
  }
  puppy_control_msgs__msg__Pose * ros_message = _ros_message;
  {  // roll
    PyObject * field = PyObject_GetAttrString(_pymsg, "roll");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->roll = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // height
    PyObject * field = PyObject_GetAttrString(_pymsg, "height");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->height = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // x_shift
    PyObject * field = PyObject_GetAttrString(_pymsg, "x_shift");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->x_shift = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // stance_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "stance_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->stance_x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // stance_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "stance_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->stance_y = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // run_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "run_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->run_time = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * puppy_control_msgs__msg__pose__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Pose */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("puppy_control_msgs.msg._pose");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Pose");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  puppy_control_msgs__msg__Pose * ros_message = (puppy_control_msgs__msg__Pose *)raw_ros_message;
  {  // roll
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->roll);
    {
      int rc = PyObject_SetAttrString(_pymessage, "roll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // height
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->height);
    {
      int rc = PyObject_SetAttrString(_pymessage, "height", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // x_shift
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->x_shift);
    {
      int rc = PyObject_SetAttrString(_pymessage, "x_shift", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // stance_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->stance_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "stance_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // stance_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->stance_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "stance_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // run_time
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->run_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "run_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
