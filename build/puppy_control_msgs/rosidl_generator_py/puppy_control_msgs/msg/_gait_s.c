// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from puppy_control_msgs:msg/Gait.idl
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
#include "puppy_control_msgs/msg/detail/gait__struct.h"
#include "puppy_control_msgs/msg/detail/gait__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool puppy_control_msgs__msg__gait__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("puppy_control_msgs.msg._gait.Gait", full_classname_dest, 33) == 0);
  }
  puppy_control_msgs__msg__Gait * ros_message = _ros_message;
  {  // overlap_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "overlap_time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->overlap_time = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // swing_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "swing_time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->swing_time = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // clearance_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "clearance_time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->clearance_time = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // z_clearance
    PyObject * field = PyObject_GetAttrString(_pymsg, "z_clearance");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->z_clearance = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * puppy_control_msgs__msg__gait__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Gait */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("puppy_control_msgs.msg._gait");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Gait");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  puppy_control_msgs__msg__Gait * ros_message = (puppy_control_msgs__msg__Gait *)raw_ros_message;
  {  // overlap_time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->overlap_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "overlap_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // swing_time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->swing_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "swing_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // clearance_time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->clearance_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "clearance_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // z_clearance
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->z_clearance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "z_clearance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
