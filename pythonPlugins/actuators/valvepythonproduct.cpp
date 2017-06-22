#include "valvepythonproduct.h"

using namespace boost::python;

ValvePythonProduct::ValvePythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

ValvePythonProduct::~ValvePythonProduct() {

}

void ValvePythonProduct::moveToPosition(int position) {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("moveToPosition")(boost::ref(*communications.get()), position);
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("ValvePythonProduct::moveToPosition. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("ValvePythonProduct::moveToPosition. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

void ValvePythonProduct::closeValve() {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("closeValve")(boost::ref(*communications.get()));
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("ValvePythonProduct::closeValve. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("ValvePythonProduct::closeValve. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
