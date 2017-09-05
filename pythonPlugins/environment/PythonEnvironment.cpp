#include "PythonEnvironment.h"

BOOST_PYTHON_MODULE(communicationsMod)
{
	boost::python::class_<CommandSenderWrap, boost::noncopyable>("CommandSender", boost::python::no_init)
		.def("sendString", boost::python::pure_virtual(&CommandSender::sendString))
		.def("receiveString", boost::python::pure_virtual(&CommandSender::receiveString))
		.def("readUntil", boost::python::pure_virtual(&CommandSender::readUntil))
        .def("synchronize", boost::python::pure_virtual(&CommandSender::synchronize))
		.def("connect", boost::python::pure_virtual(&CommandSender::connect))
		.def("disconnect", boost::python::pure_virtual(&CommandSender::disconnect))
		;

	boost::python::class_<SerialSender, boost::python::bases<CommandSender>, boost::noncopyable>("SerialSender", boost::python::no_init)
		.def("sendString", &SerialSender::sendString)
		.def("receiveString", &SerialSender::receiveString)
		.def("readUntil", &SerialSender::readUntil)
        .def("synchronize", &SerialSender::synchronize)
		.def("connect", &SerialSender::connect)
		.def("disconnect", &SerialSender::disconnect)
		;

	boost::python::class_<FileSender, boost::python::bases<CommandSender>, boost::noncopyable>("FileSender", boost::python::no_init)
		.def("sendString", &FileSender::sendString)
		.def("receiveString", &FileSender::receiveString)
		.def("readUntil", &FileSender::readUntil)
        .def("synchronize", &FileSender::synchronize)
		.def("connect", &FileSender::connect)
		.def("disconnect", &FileSender::disconnect)
		;
}

PythonEnvironment* PythonEnvironment::m_pInstance = NULL;

PythonEnvironment* PythonEnvironment::GetInstance() {
    if (!m_pInstance)
        m_pInstance = new PythonEnvironment();
    return m_pInstance;
}

 void PythonEnvironment::freeCommandInterface() {
    if (m_pInstance) {
        delete m_pInstance;
    }
}

namespace boost { template <> CommandSender const volatile * get_pointer(class CommandSender const volatile *c) { return c; } }

using namespace boost::python;

PythonEnvironment::PythonEnvironment()
{
}


PythonEnvironment::~PythonEnvironment()
{
}

void PythonEnvironment::addImportPath(const std::string & path)
{
	//Add plugins folder to the python path
    std::string wordPath = "path";
    boost::scoped_array<char> writable(new char[wordPath.size() + 1]);
    std::copy(wordPath.begin(), wordPath.end(), writable.get());
    writable[wordPath.size()] = '\0'; // don't forget the terminating 0

    PyObject* sysPath = PySys_GetObject(writable.get());
	PyList_Insert(sysPath, 0, PyString_FromString(path.c_str()));
}

std::string PythonEnvironment::makeInstance(const std::string & type, const std::unordered_map<std::string,std::string>& params) throw (std::invalid_argument)
{
	try {
		std::string path = PluginFileLoader::GetInstance()->getPath(type);
		std::string dir = getDirectoryPath(path);
		if (loadedFiles.find(dir) == loadedFiles.end()) {
			addImportPath(dir);
			loadedFiles.insert(dir);
		}

		object importObj;
		std::string importName = getPythonClassNAme(path);
		auto it = loadedClasses.find(importName);
		if (it == loadedClasses.end()) {
			importObj = import(str(importName));
			loadedClasses.insert(std::make_pair(importName, importObj));
		}
		else {
			importObj = it->second;
		}

        boost::python::dict d;
        for (auto it = params.begin(); it != params.end(); ++it) {
            d[it->first] = it->second;
        }

        std::string varName = "var" + std::to_string(this->autoEnum.getNextValue());
        this->main_namespace[varName] = importObj.attr(str(type))(d);
		availableInstances.insert(varName);

		return varName;
	}
	catch (std::invalid_argument & e) {
		throw(e);
	}
	catch (error_already_set) {
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);
		
		char * cs = PyString_AsString(pvalue);
		
		std::string msg = "unknow";
		if (cs) {
			msg = std::string(cs);
		}

		throw(std::invalid_argument("error at python environment " + msg));
	}
}

void PythonEnvironment::deleteInstance(const std::string & varName) {
	if (availableInstances.find(varName) != availableInstances.end()) {
		try {
			this->main_namespace[varName].del();
		}
		catch (error_already_set) {
			PyObject *ptype, *pvalue, *ptraceback;
			PyErr_Fetch(&ptype, &pvalue, &ptraceback);
			char * cs = PyString_AsString(pvalue);

			std::string msg = "unknow";
			if (cs) {
				msg = std::string(cs);
			}

			throw(std::invalid_argument("error at python environment " + msg));
		}
    }
}

boost::python::api::object PythonEnvironment::getVarInstance(const std::string & varName) throw (std::invalid_argument)
{
	if (availableInstances.find(varName) != availableInstances.end()) {
		try {
			return this->main_namespace[varName];
		}
		catch (error_already_set) {
			PyObject *ptype, *pvalue, *ptraceback;
			PyErr_Fetch(&ptype, &pvalue, &ptraceback);

			char * cs = PyString_AsString(pvalue);

			std::string msg = "unknow";
			if (cs) {
				msg = std::string(cs);
			}

			throw(std::invalid_argument("error at python environment " + msg));
		}
    }
}

void PythonEnvironment::initEnvironment(const std::string & basePluginsPath)
{
	Py_Initialize();
    PyEval_InitThreads();

	initcommunicationsMod();

	object main_module = import("__main__");
	this->main_namespace = main_module.attr("__dict__");

	//create types used in the execution
	class_<std::vector<std::string>>("ParamsList")
		.def(vector_indexing_suite<std::vector<std::string>>());

    addImportPath(basePluginsPath);

    releaseGIL();
}

void PythonEnvironment::finishEnvironment()
{
	Py_Finalize();
}

void PythonEnvironment::acquireGIL() {
    PyEval_RestoreThread(state);
}

void PythonEnvironment::releaseGIL() {
    state = PyEval_SaveThread();
}

std::string PythonEnvironment::getPythonClassNAme(const std::string & path) throw (std::invalid_argument) {
	size_t init = path.find_last_of("\\");
    if (init == string::npos) {
        init = path.find_last_of("/");
    }
	size_t end = path.find_last_of(".py");

	if (end > init) {
		std::string sub = path.substr(init + 1, (end - 3) - init);
		return sub;
	}
	else {
		throw(std::invalid_argument("incorrect path, \\ or .py missing"));
	}
}

std::string PythonEnvironment::getDirectoryPath(const std::string & path) throw (std::invalid_argument) {
	size_t init = path.find_last_of("\\");
    if (init == string::npos) {
        init = path.find_last_of("/");
    }

    if (init != string::npos) {
        std::string sub = path.substr(0, init);
        return sub;
    } else {
        throw(std::invalid_argument("incorrect path, \\ or .py missing"));
    }
}

object PythonEnvironment::executeStaticMethod(const std::string & type, const std::string & method) {
    try {
        std::string path = PluginFileLoader::GetInstance()->getPath(type);
        std::string dir = getDirectoryPath(path);
        if (loadedFiles.find(dir) == loadedFiles.end()) {
            addImportPath(dir);
            loadedFiles.insert(dir);
        }

        object importObj;
        std::string importName = getPythonClassNAme(path);
        auto it = loadedClasses.find(importName);
        if (it == loadedClasses.end()) {
            importObj = import(str(importName));
            loadedClasses.insert(std::make_pair(importName, importObj));
        }
        else {
            importObj = it->second;
        }

        auto temp = importObj.attr(str(type));
        return temp.attr(str(method))();
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        char * cs = PyString_AsString(pvalue);

        std::string msg = "unknow";
        if (cs) {
            msg = std::string(cs);
        }
        throw(std::invalid_argument("error at python environment " + msg));
    }
}

std::vector<std::pair<std::string,std::string>> PythonEnvironment::getParamsType(const std::string & pluginType) throw (std::runtime_error) {
    try {
        std::vector<std::pair<std::string,std::string>> params;
        dict dictionary = extract<dict>(executeStaticMethod(pluginType, "getParamsType"));

        boost::python::list lista = dictionary.keys();
        int size = len(lista);

        for (int i = 0; i < size; i++) {
            boost::python::extract<boost::python::object> key_extract(lista[i]);
            if (key_extract.check()) {
                boost::python::object u = key_extract();
                const char* cKey = extract<const char*>(str(u).encode("utf-8"));
                std::string keyStr(cKey);

                boost::python::extract<boost::python::object> value_extract(dictionary[keyStr]);
                if (value_extract.check()) {
                    u = value_extract();
                    const char* cValue = extract<const char*>(str(u).encode("utf-8"));
                    std::string valueStr(cValue);

                    params.push_back(make_pair(keyStr, valueStr));
                } else {
                    throw(std::runtime_error("bad value at position " + std::to_string(i)));
                }
            } else {
                throw(std::runtime_error("bad value at position " + std::to_string(i)));
            }
        }
        return params;
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("addConnection(), " + pluginType + ": " + "error at python environment " + error));
    }  catch (std::invalid_argument & e) {
        throw(std::runtime_error("addConnection(), " + pluginType + ": " + "internal error" + std::string(e.what())));
    }
}
