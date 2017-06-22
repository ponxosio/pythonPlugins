#include "ligthpythonproduct.h"

using namespace boost::python;

LigthPythonProduct::LigthPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

LigthPythonProduct::~LigthPythonProduct() {

}

void LigthPythonProduct::applyLight(units::LuminousIntensity intensity, units::Length wavelenght) {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("applyLigth")(
                    boost::ref(*communications.get()),
                    intensity.to(units::cd),
                    wavelenght.to(units::nm));
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("LigthPythonProduct::applyLight. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("LigthPythonProduct::applyLight. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

void LigthPythonProduct::turnOffLight() {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("turnOff")(boost::ref(*communications.get()));
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("LigthPythonProduct::turnOffLight. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("LigthPythonProduct::turnOffLight. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
