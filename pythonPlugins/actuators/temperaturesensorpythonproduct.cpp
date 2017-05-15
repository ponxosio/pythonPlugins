#include "temperaturesensorpythonproduct.h"

using namespace boost::python;

TemperatureSensorPythonProduct::TemperatureSensorPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

TemperatureSensorPythonProduct::~TemperatureSensorPythonProduct() {

}

void TemperatureSensorPythonProduct::startMeasureTemperature(units::Frequency measurementFrequency) {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startMeasuring")(
                        boost::ref(*communications.get()),
                        measurementFrequency.to(units::Hz));

    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("TemperatureSensorPythonProduct::startMeasureTemperature. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("TemperatureSensorPythonProduct::startMeasureTemperature. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

units::Temperature TemperatureSensorPythonProduct::getTemperatureMeasurement() {
    try {
        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        double temperatureValue = extract<double>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getMeasurement")(boost::ref(*communications.get())));
        return temperatureValue * units::K;

    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("TemperatureSensorPythonProduct::getTemperatureMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("TemperatureSensorPythonProduct::getTemperatureMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
