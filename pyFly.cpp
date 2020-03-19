#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"
#include "bfly.h"

unsigned char *image;

static PyObject *initCamera(PyObject *self, PyObject *args)
{
		int iMode;
		if(!PyArg_ParseTuple(args, "i", &iMode)) {
				return NULL;
		}

		PyObject *return_value;
		bool result;
		result = initCamera(iMode);
		return_value = Py_BuildValue("i", result);
		return return_value;
}


static PyObject *closeCamera(PyObject *self, PyObject *args)
{
		PyObject *return_value;
		bool result;
		result = closeCamera();
		return_value = Py_BuildValue("i", result);
		return return_value;
}


static PyObject *isCameraOpen(PyObject *self, PyObject *args)
{
		PyObject *return_value;
		bool result;
		result = isCameraOpen();
		return_value = Py_BuildValue("i", result);
		return return_value;
}


static PyObject *getWidth(PyObject *self, PyObject *args)
{
		PyObject *return_value;
		return_value = Py_BuildValue("i", getWidth());
		return return_value;
}

static PyObject *getHeight(PyObject *self, PyObject *args)
{
		PyObject *return_value;
		return_value = Py_BuildValue("i", getHeight());
		return return_value;
}


static PyObject *getImage(PyObject *self, PyObject *args)
{
		image = getImage();
		int nd = 3;
		npy_intp m[] = {getHeight(),getWidth(),3};
		PyObject *array = PyArray_SimpleNewFromData(nd, m, NPY_UINT8, image);
		return array;
}


static PyMethodDef pyFlyMethods[] = {
		{"initCamera", initCamera, METH_VARARGS, "camera initialize"},
		{"closeCamera", closeCamera, METH_VARARGS, "close camera"},
		{"isCameraOpen", isCameraOpen, METH_VARARGS, "check camera status"},
		{"getWidth", getWidth, METH_VARARGS, "get image width"},
		{"getHeight", getHeight, METH_VARARGS, "get image height"},
		{"getImage", getImage, METH_VARARGS, "get image data"},
		{NULL, NULL, 0, NULL}
};

static PyModuleDef pyFlyModule = {
		PyModuleDef_HEAD_INIT,
		"pyFly",
		NULL,
		-1,
		pyFlyMethods
};

PyMODINIT_FUNC PyInit_pyFly(void)
{
		import_array();
		return PyModule_Create(&pyFlyModule);
}
