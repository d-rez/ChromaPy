#include "Keyboard.h"
#include "Mouse.h"
#include "Mousepad.h"
#include "Keypad.h"
#include "Headset.h"
using namespace std;

Chroma_Implementation Chroma;


PyObject* set_all(PyObject* self, PyObject* args)
{
	
	PyObject *Color;
	if(!PyArg_ParseTuple(args,"O",&Color))
	{
		PyErr_SetString(SyntaxError, "Invalid Arguments! Usage: setColor(color) | setColor( (R, G, B))");
		return nullptr;
	}
	
	COLORREF color;
	
	if(!Chroma.Colortest(Color,color)){ return PyUnicode_FromString("Error"); }
	
	Chroma.set_all(color);
	return PyUnicode_FromString("Success");
}







PyObject* getconnected(PyObject* self, PyObject* args)
{
	vector<char*> devices;
	Chroma.ConnectedDevices(devices);

		PyObject *lst = PyList_New(devices.size());

		for(size_t i = 0; i < devices.size(); i++)
		{
			PyObject *str = PyUnicode_FromString(devices[i]);
			PyList_SET_ITEM(lst, i, str);
		}
		return lst;
	
}

PyObject* applyEffect(PyObject* self, PyObject* args){


	Chroma.applyKeyboardEffect();
	Chroma.applyMouseEffect();
	Chroma.applyMousepadEffect();
	Chroma.applyKeypadEffect();
	Chroma.applyHeadsetEffect();


	return PyUnicode_FromString("Success");
}

PyObject* ResetEffect(PyObject* self, PyObject* args) {
	
	Chroma.ResetEffects(KEYBOARD_DEVICES);
	Chroma.ResetEffects(MOUSE_DEVICES);
	Chroma.ResetEffects(MOUSEMAT_DEVICES);
	Chroma.ResetEffects(KEYPAD_DEVICES); 
	Chroma.ResetEffects(HEADSET_DEVICES);
	
	return PyUnicode_FromString("Success");

}

PyMethodDef ChromaPyMethods[] = { 
	
	{"setColor", static_cast<PyCFunction>(set_all), METH_VARARGS, docGlobalsetColor },
	{ "getConnectedDevices", static_cast<PyCFunction>(getconnected), METH_NOARGS, docGlobalgetConnectedDevices },
	{ "applyEffect", static_cast<PyCFunction>(applyEffect), METH_NOARGS, docGlobalapplyEffect },
	{"resetEffect",static_cast<PyCFunction>(ResetEffect), METH_NOARGS, docGlobalresetEffect },
	{nullptr,nullptr,0,nullptr}

};


static struct PyModuleDef ChromaPy = {
	PyModuleDef_HEAD_INIT,
	"ChromaPy",   /* name of module */
	docGlobal, /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
			  or -1 if the module keeps state in global variables. */
	ChromaPyMethods
};

PyMODINIT_FUNC
PyInit_ChromaPy()
{
	PyObject* m;
	Chroma.Initialize();
	Keyboard_Type.tp_new = PyType_GenericNew;
	
	if (PyType_Ready(&Keyboard_Type) < 0) {
		return nullptr;
	}
	Mouse_Type.tp_new = PyType_GenericNew;
	if(PyType_Ready(&Mouse_Type) < 0)
	{
		return nullptr;
	}
	Mousepad_Type.tp_new = PyType_GenericNew;
	if(PyType_Ready(&Mousepad_Type) < 0)
	{
		return nullptr;
	}

	Keypad_Type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&Keypad_Type) < 0)
	{
		return nullptr;
	}
	Headset_Type.tp_new = PyType_GenericNew;
	if (PyType_Ready(&Headset_Type)< 0)
	{
		return nullptr;
	}

	m = PyModule_Create(&ChromaPy);
	if (m == nullptr) {
		return nullptr;
	}

	SyntaxError = PyErr_NewException("ChromaPy.SyntaxError", NULL, NULL);
	Py_INCREF(SyntaxError);
	PyModule_AddObject(m, "SyntaxError", SyntaxError);


	Py_INCREF(&Keyboard_Type);
	Py_INCREF(&Mouse_Type);
	Py_INCREF(&Mousepad_Type);
	Py_INCREF(&Keypad_Type);
	Py_INCREF(&Headset_Type);

	PyModule_AddObject(m, "Keyboard", reinterpret_cast<PyObject *>(&Keyboard_Type));
	PyModule_AddObject(m, "Mouse", reinterpret_cast<PyObject *>(&Mouse_Type));
	PyModule_AddObject(m, "Mousepad", reinterpret_cast<PyObject *>(&Mousepad_Type));
	PyModule_AddObject(m, "Keypad", reinterpret_cast<PyObject *>(&Keypad_Type));
	PyModule_AddObject(m, "Headset", reinterpret_cast<PyObject *>(&Headset_Type));
	return m;
}

//Currently 2475 lines of Code