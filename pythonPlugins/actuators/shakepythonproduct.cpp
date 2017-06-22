#include "shakepythonproduct.h"

using namespace boost::python;

ShakePythonProduct::ShakePythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

ShakePythonProduct::~ShakePythonProduct() {

}

void ShakePythonProduct::startShake(units::Frequency intensity) {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startShaking")(boost::ref(*communications.get()), intensity.to(units::Hz));
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("ShakePythonProduct::startShake. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("ShakePythonProduct::startShake. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

void ShakePythonProduct::stopShake() {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("stopShaking")(boost::ref(*communications.get()));
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("ShakePythonProduct::stopShake. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("ShakePythonProduct::stopShake. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
