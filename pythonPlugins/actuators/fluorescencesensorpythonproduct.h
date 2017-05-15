#ifndef FLUORESCENCESENSORPYTHONPRODUCT_H
#define FLUORESCENCESENSORPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/fluorescencesensorproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class FluorescenceSensorPythonProduct : public FluorescenceSensorProduct
{
public:
    FluorescenceSensorPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~FluorescenceSensorPythonProduct();

    virtual void startMeasureFluorescence(units::Frequency measurementFrequency, units::Length excitation, units::Length emission);
    virtual units::LuminousIntensity getFluorescenceMeasurement();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};
#endif // FLUORESCENCESENSORPYTHONPRODUCT_H
