#include "vk_app_info.h"
#include "log.h"

PyMemberDef vk_app_info_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_app_info, p_next), 0, "TODO: Pass None for now"},
    {"app_name", T_STRING, offsetof(vk_app_info, app_name), 0, "The application name (str)"},
    {"app_ver", T_OBJECT_EX, offsetof(vk_app_info, app_ver), 0, "A tuple of (variant, major, minor, patch) versions"},
    {"engine_name", T_STRING, offsetof(vk_app_info, engine_name), 0, "Name of the engine (str)"},
    {"engine_ver", T_OBJECT_EX, offsetof(vk_app_info, engine_ver), 0, "A tuple of (variant, major, minor, patch) versions"},
    {"api_ver", T_OBJECT_EX, offsetof(vk_app_info, api_ver), 0, "A tuple of (variant, major, minor, patch) versions"},
    {NULL},
};

void vk_app_info_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_app_info_dealloc\n");

    vk_app_info *self = (vk_app_info *)self_obj;

    if (self->app_info.pApplicationName)
    {
        if (strcmp(self->app_info.pApplicationName, "") != 0)
        {
            free(self->app_info.pApplicationName);
        }
    }

    if (self->app_info.pEngineName)
    {
        if (strcmp(self->app_info.pEngineName, "") != 0)
        {
            free(self->app_info.pEngineName);
        }
    }

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    if (self->app_ver != Py_None)
    {
        Py_XDECREF(self->app_ver);
    }

    if (self->engine_ver != Py_None)
    {
        Py_XDECREF(self->engine_ver);
    }

    if (self->api_ver != Py_None)
    {
        Py_XDECREF(self->api_ver);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

char *get_string_from_obj(PyObject *obj)
{
    PyObject *ascii = PyUnicode_AsASCIIString(obj);

    uint32_t bytes_count = 0;
    char *bytes = NULL;
    PyBytes_AsStringAndSize(ascii, &bytes, (Py_ssize_t *)&bytes_count);

    char *str = (char *)malloc(sizeof(char) * (bytes_count + 1));
    memcpy(str, bytes, sizeof(char) * (bytes_count + 1));

    Py_XDECREF(ascii);

    return str;
}

void init_app_info_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_app_info_from_obj\n");

    vk_app_info *obj = (vk_app_info *)obj_obj;

    obj->app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    obj->app_info.pNext = NULL;

    uint32_t variant = PyLong_AsLong(PyTuple_GetItem(obj->app_ver, 0));
    uint32_t major = PyLong_AsLong(PyTuple_GetItem(obj->app_ver, 1));
    uint32_t minor = PyLong_AsLong(PyTuple_GetItem(obj->app_ver, 2));
    uint32_t patch = PyLong_AsLong(PyTuple_GetItem(obj->app_ver, 3));
    obj->app_info.applicationVersion = VK_MAKE_API_VERSION(variant, major, minor, patch);

    variant = PyLong_AsLong(PyTuple_GetItem(obj->engine_ver, 0));
    major = PyLong_AsLong(PyTuple_GetItem(obj->engine_ver, 1));
    minor = PyLong_AsLong(PyTuple_GetItem(obj->engine_ver, 2));
    patch = PyLong_AsLong(PyTuple_GetItem(obj->engine_ver, 3));
    obj->app_info.engineVersion = VK_MAKE_API_VERSION(variant, major, minor, patch);

    variant = PyLong_AsLong(PyTuple_GetItem(obj->api_ver, 0));
    major = PyLong_AsLong(PyTuple_GetItem(obj->api_ver, 1));
    minor = PyLong_AsLong(PyTuple_GetItem(obj->api_ver, 2));
    patch = PyLong_AsLong(PyTuple_GetItem(obj->api_ver, 3));
    obj->app_info.apiVersion = VK_MAKE_API_VERSION(variant, major, minor, patch);
}

int vk_app_info_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_app_info_init\n");

    vk_app_info *self = (vk_app_info *)self_obj;

    PyObject *p_next = NULL;
    PyObject *app_ver = NULL;
    PyObject *engine_ver = NULL;
    PyObject *api_ver = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = { "p_next", "app_name", "app_ver", "engine_name", "engine_ver", "api_ver", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OsOsOO", kwlist, &p_next, &self->app_name, &app_ver, &self->engine_name, &engine_ver, &api_ver);
    if (PyErr_Occurred())
    {
        return -1;
    }

    if (p_next)
    {
        tmp = self->p_next;
        Py_INCREF(p_next);
        self->p_next = p_next;
        Py_XDECREF(tmp);
    }
    else
    {
        self->p_next = Py_None;
    }
    DEBUG_LOG("app_info parsed p_next\n");

    if (app_ver)
    {
        tmp = self->app_ver;
        Py_INCREF(app_ver);
        self->app_ver = app_ver;
        Py_XDECREF(tmp);
    }
    else
    {
        self->app_ver = Py_None;
    }
    DEBUG_LOG("app_info parsed app_ver\n");

    if (engine_ver)
    {
        tmp = self->engine_ver;
        Py_INCREF(engine_ver);
        self->engine_ver = engine_ver;
        Py_XDECREF(tmp);
    }
    else
    {
        self->engine_ver = Py_None;
    }
    DEBUG_LOG("app_info parsed engine_ver\n");

    if (api_ver)
    {
        tmp = self->api_ver;
        Py_INCREF(api_ver);
        self->api_ver = api_ver;
        Py_XDECREF(tmp);
    }
    else
    {
        self->api_ver = Py_None;
    }
    DEBUG_LOG("app_info parsed api_ver\n");

    init_app_info_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_app_info_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.application_info",
    .tp_basicsize = sizeof(vk_app_info),
    .tp_doc = PyDoc_STR("Vulkan Application Info Docs"),
    .tp_members = vk_app_info_members,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_app_info_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_app_info_init,
};

PyObject *add_vk_app_info_to_module(PyObject *mod)
{
    DEBUG_LOG("adding app_info object\n");

    if (PyType_Ready(&vk_app_info_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready app_info type");

        goto shutdown;
    }

    Py_INCREF(&vk_app_info_type);

    if (PyModule_AddObject(mod, "application_info", (PyObject *)&vk_app_info_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add app_info type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_app_info_type);

    return NULL;
}