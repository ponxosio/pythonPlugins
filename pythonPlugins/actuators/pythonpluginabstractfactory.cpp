#include "pythonpluginabstractfactory.h"

PythonPluginAbstractFactory::PythonPluginAbstractFactory(std::shared_ptr<CommandSender> communications) {
    this->communications = communications;
}

PythonPluginAbstractFactory::~PythonPluginAbstractFactory() {

}

std::shared_ptr<HeaterPluginProduct> PythonPluginAbstractFactory::makeHeater(std::shared_ptr<PluginConfiguration> configuration) {
    return std::make_shared<HeaterPythonProduct>(configuration, communications);
}

std::shared_ptr<LightPluginProduct> PythonPluginAbstractFactory::makeLight(std::shared_ptr<PluginConfiguration> configuration) {
    return std::make_shared<LigthPythonProduct>(configuration, communications);
}

std::shared_ptr<StirerPluginProduct> PythonPluginAbstractFactory::makeStirer(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<StirerPythonProduct>(configuration, communications);
}

std::shared_ptr<ShakePluginProduct> PythonPluginAbstractFactory::makeShaker(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<ShakePythonProduct>(configuration, communications);
}

std::shared_ptr<CentrifugatePluginProduct> PythonPluginAbstractFactory::makeCentrifugate(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<CentrifugationPythonProduct>(configuration, communications);
}

std::shared_ptr<ElectrophoresisPluginProduct> PythonPluginAbstractFactory::makeElectrophorer(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<ElectrophoresisPythonProduct>(configuration, communications);
}

std::shared_ptr<OdSensorPluginProduct> PythonPluginAbstractFactory::makeOdSensor(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<OdSensorPythonProduct>(configuration, communications);
}

std::shared_ptr<TemperatureSensorProduct> PythonPluginAbstractFactory::makeTemperatureSensor(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<TemperatureSensorPythonProduct>(configuration, communications);
}

std::shared_ptr<LuminiscenceSensorProduct> PythonPluginAbstractFactory::makeLuminiscenseSensor(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<LuminiscenceSensorPythonProduct>(configuration, communications);
}

std::shared_ptr<FluorescenceSensorProduct> PythonPluginAbstractFactory::makeFluorescenceSensor(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<FluorescenceSensorPythonProduct>(configuration, communications);
}

std::shared_ptr<VolumeSensorProduct> PythonPluginAbstractFactory::makeVolumeSensor(std::shared_ptr<PluginConfiguration> configuration) {
    return std::make_shared<VolumenSensorPythonProduct>(configuration, communications);
}

std::shared_ptr<PumpPluginProduct> PythonPluginAbstractFactory::makePump(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<PumpPythonProduct>(configuration, communications);
}

std::shared_ptr<ValvePluginProduct> PythonPluginAbstractFactory::makeValve(std::shared_ptr<PluginConfiguration> configuration)  {
    return std::make_shared<ValvePythonProduct>(configuration, communications);
}
