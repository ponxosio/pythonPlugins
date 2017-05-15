#ifndef PYTHONPLUGINABSTRACTFACTORY_H
#define PYTHONPLUGINABSTRACTFACTORY_H

#include <memory>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/pluginabstractfactory.h>

#include "pythonPlugins/actuators/centrifugationpythonproduct.h"
#include "pythonPlugins/actuators/electrophoresispythonproduct.h"
#include "pythonPlugins/actuators/fluorescencesensorpythonproduct.h"
#include "pythonPlugins/actuators/heaterpythonproduct.h"
#include "pythonPlugins/actuators/ligthpythonproduct.h"
#include "pythonPlugins/actuators/luminiscencesensorpythonproduct.h"
#include "pythonPlugins/actuators/odsensorpythonproduct.h"
#include "pythonPlugins/actuators/pumppythonproduct.h"
#include "pythonPlugins/actuators/shakepythonproduct.h"
#include "pythonPlugins/actuators/stirerpythonproduct.h"
#include "pythonPlugins/actuators/temperaturesensorpythonproduct.h"
#include "pythonPlugins/actuators/valvepythonproduct.h"
#include "pythonPlugins/actuators/volumensensorpythonproduct.h"

class PythonPluginAbstractFactory : public PluginAbstractFactory
{
public:
    PythonPluginAbstractFactory(std::shared_ptr<CommandSender> communications);
    virtual ~PythonPluginAbstractFactory();

    virtual std::shared_ptr<HeaterPluginProduct> makeHeater(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<LightPluginProduct> makeLight(std::shared_ptr<PluginConfiguration> configuration);

    virtual std::shared_ptr<StirerPluginProduct> makeStirer(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<ShakePluginProduct> makeShaker(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<CentrifugatePluginProduct> makeCentrifugate(std::shared_ptr<PluginConfiguration> configuration);

    virtual std::shared_ptr<ElectrophoresisPluginProduct> makeElectrophorer(std::shared_ptr<PluginConfiguration> configuration);

    virtual std::shared_ptr<OdSensorPluginProduct> makeOdSensor(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<TemperatureSensorProduct> makeTemperatureSensor(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<LuminiscenceSensorProduct> makeLuminiscenseSensor(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<FluorescenceSensorProduct> makeFluorescenceSensor(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<VolumeSensorProduct> makeVolumeSensor(std::shared_ptr<PluginConfiguration> configuration);

    virtual std::shared_ptr<PumpPluginProduct> makePump(std::shared_ptr<PluginConfiguration> configuration);
    virtual std::shared_ptr<ValvePluginProduct> makeValve(std::shared_ptr<PluginConfiguration> configuration);

protected:
    std::shared_ptr<CommandSender> communications;
};

#endif // PYTHONPLUGINABSTRACTFACTORY_H
