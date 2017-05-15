#include "pumppythonproduct.h"

using namespace boost::python;

PumpPythonProduct::PumpPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

PumpPythonProduct::~PumpPythonProduct() {

}

void PumpPythonProduct::setPumpState(int dir, units::Volumetric_Flow rate) {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startPumping")(
                    boost::ref(*communications.get()),
                    dir,
                    rate.to(units::l / units::s));

    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("PumpPythonProduct::setPumpState. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("PumpPythonProduct::setPumpState. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

void PumpPythonProduct::stopPump() {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("stopPump")(boost::ref(*communications.get()));
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("PumpPythonProduct::setPumpState. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("PumpPythonProduct::setPumpState. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
