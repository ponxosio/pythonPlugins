#include "odsensorpythonproduct.h"

using namespace boost::python;

OdSensorPythonProduct::OdSensorPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

OdSensorPythonProduct::~OdSensorPythonProduct() {

}

void OdSensorPythonProduct::startMeasureOd(units::Frequency measurementFrequency, units::Length waveLength) {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startMeasuring")(
                        boost::ref(*communications.get()),
                        measurementFrequency.to(units::Hz),
                        waveLength.to(units::nm));

        PythonEnvironment::GetInstance()->releaseGIL();
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("OdSensorPythonProduct::startMeasureOd. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("OdSensorPythonProduct::startMeasureOd. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

double OdSensorPythonProduct::getOdMeasurement() {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        double fluorescenceValue = extract<double>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getMeasurement")(boost::ref(*communications.get())));

        PythonEnvironment::GetInstance()->releaseGIL();

        return fluorescenceValue;
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("OdSensorPythonProduct::getOdMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    } catch (std::invalid_argument & e) {
        throw(std::runtime_error("OdSensorPythonProduct::getOdMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
