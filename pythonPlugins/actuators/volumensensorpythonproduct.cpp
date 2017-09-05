#include "volumensensorpythonproduct.h"

using namespace boost::python;

VolumenSensorPythonProduct::VolumenSensorPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

VolumenSensorPythonProduct::~VolumenSensorPythonProduct() {

}

void VolumenSensorPythonProduct::startMeasureVolume(units::Frequency measurementFrequency) {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startMeasuring")(
                        boost::ref(*communications.get()),
                        measurementFrequency.to(units::Hz));

        PythonEnvironment::GetInstance()->releaseGIL();
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("VolumenSensorPythonProduct::startMeasureVolume. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("VolumenSensorPythonProduct::startMeasureVolume. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

units::Volume VolumenSensorPythonProduct::getVolumeMeasurement() {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        double temperatureValue = extract<double>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getMeasurement")(boost::ref(*communications.get())));

        PythonEnvironment::GetInstance()->releaseGIL();

        return temperatureValue * units::l;
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("VolumenSensorPythonProduct::getVolumeMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("VolumenSensorPythonProduct::getVolumeMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
