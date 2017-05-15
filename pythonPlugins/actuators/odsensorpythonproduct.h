#ifndef ODSENSORPYTHONPRODUCT_H
#define ODSENSORPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/odsensorpluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class OdSensorPythonProduct : public OdSensorPluginProduct
{
public:
    OdSensorPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~OdSensorPythonProduct();

    virtual void startMeasureOd(units::Frequency measurementFrequency, units::Length waveLength);
    virtual double getOdMeasurement();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // ODSENSORPYTHONPRODUCT_H
