#include "fluorescencesensorpythonproduct.h"

using namespace boost::python;

FluorescenceSensorPythonProduct::FluorescenceSensorPythonProduct(
        std::shared_ptr<PluginConfiguration> configurationObj,
        std::shared_ptr<CommandSender> communications)
{
    this->configurationObj = configurationObj;
    this->communications = communications;
    this->referenceName = "";
}

FluorescenceSensorPythonProduct::~FluorescenceSensorPythonProduct() {

}

void FluorescenceSensorPythonProduct::startMeasureFluorescence(
        units::Frequency measurementFrequency,
        units::Length excitation,
        units::Length emission)
{
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getName(), configurationObj->getParams());
        }

        PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("startMeasuring")(
                        boost::ref(*communications.get()),
                        measurementFrequency.to(units::Hz),
                        excitation.to(units::nm),
                        emission.to(units::nm));

        PythonEnvironment::GetInstance()->releaseGIL();
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("FluorescenceSensorPythonProduct::startMeasureFluorescence. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("FluorescenceSensorPythonProduct::startMeasureFluorescence. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}

units::LuminousIntensity FluorescenceSensorPythonProduct::getFluorescenceMeasurement() {
    try {
        PythonEnvironment::GetInstance()->acquireGIL();

        if (referenceName.empty()) {
            referenceName = PythonEnvironment::GetInstance()->makeInstance(configurationObj->getPluginType(), configurationObj->getParams());
        }

        double fluorescenceValue = extract<double>(PythonEnvironment::GetInstance()->getVarInstance(referenceName).attr("getMeasurement")(boost::ref(*communications.get())));

        PythonEnvironment::GetInstance()->releaseGIL();

        return fluorescenceValue * units::cd;
    } catch (error_already_set) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);

        std::string error = "";
        char* c_str = PyString_AsString(pvalue);
        if (c_str) {
            error = std::string(c_str);
        }
        throw(std::runtime_error("FluorescenceSensorPythonProduct::getFluorescenceMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "error at python environment " + error));
    }
    catch (std::invalid_argument & e)
    {
        throw(std::runtime_error("FluorescenceSensorPythonProduct::getFluorescenceMeasurement. Plugin " + configurationObj->getPluginType() + ": " + "internal error" + std::string(e.what())));
    }
}
