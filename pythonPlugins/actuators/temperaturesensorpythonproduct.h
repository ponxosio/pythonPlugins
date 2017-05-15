#ifndef TEMPERATURESENSORPYTHONPRODUCT_H
#define TEMPERATURESENSORPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/temperaturesensorproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class TemperatureSensorPythonProduct : public TemperatureSensorProduct
{
public:
    TemperatureSensorPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~TemperatureSensorPythonProduct();

    virtual void startMeasureTemperature(units::Frequency measurementFrequency);
    virtual units::Temperature getTemperatureMeasurement();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // TEMPERATURESENSORPYTHONPRODUCT_H
