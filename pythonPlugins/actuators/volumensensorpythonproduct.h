#ifndef VOLUMENSENSORPYTHONPRODUCT_H
#define VOLUMENSENSORPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/volumesensorproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class VolumenSensorPythonProduct : public VolumeSensorProduct
{
public:
    VolumenSensorPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~VolumenSensorPythonProduct();

    virtual void startMeasureVolume(units::Frequency measurementFrequency);
    virtual units::Volume getVolumeMeasurement();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // VOLUMENSENSORPYTHONPRODUCT_H
