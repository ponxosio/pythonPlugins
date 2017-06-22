#include "electrophoresispythonproduct.h"

using namespace boost::python;

ElectrophoresisPythonProduct::ElectrophoresisPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

ElectrophoresisPythonProduct::~ElectrophoresisPythonProduct() {

}

void ElectrophoresisPythonProduct::startElectrophoresis(units::ElectricField fieldStrenght) {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startElectrophoresis")(boost::ref(*communications.get()), fieldStrenght.to(units::V / units::m));
    }
    catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("ElectrophoresisPythonProduct::startElectrophoresis. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("ElectrophoresisPythonProduct::startElectrophoresis. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

std::shared_ptr<ElectrophoresisResult> ElectrophoresisPythonProduct::stopElectrophpresis() {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getResults")(boost::ref(*communications.get()));
        return NULL; //TODO:
    }
    catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("ElectrophoresisPythonProduct::stopElectrophpresis. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("ElectrophoresisPythonProduct::stopElectrophpresis. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
