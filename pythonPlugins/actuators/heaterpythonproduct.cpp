#include "heaterpythonproduct.h"

using namespace boost::python;

HeaterPythonProduct::HeaterPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

HeaterPythonProduct::~HeaterPythonProduct() {

}

void HeaterPythonProduct::changeTemperature(units::Temperature value) {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("applyTemperature")(boost::ref(*communications.get()), value.to(units::C));

        PythonEnvironment::GetInstance()->releaseGIL();
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("HeaterPythonProduct::changeTemperature. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("HeaterPythonProduct::changeTemperature. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

void HeaterPythonProduct::turnOff() {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("turnOff")(boost::ref(*communications.get()));

        PythonEnvironment::GetInstance()->releaseGIL();
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("HeaterPythonProduct::turnOff. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("HeaterPythonProduct::turnOff. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
