#ifndef LUMINISCENCESENSORPYTHONPRODUCT_H
#define LUMINISCENCESENSORPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/luminiscencesensorproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class LuminiscenceSensorPythonProduct : public LuminiscenceSensorProduct
{
public:
    LuminiscenceSensorPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~LuminiscenceSensorPythonProduct();

    virtual void startMeasureLuminiscence(units::Frequency measurementFrequency);
    virtual units::LuminousIntensity getLuminiscenceMeasurement();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // LUMINISCENCESENSORPYTHONPRODUCT_H
