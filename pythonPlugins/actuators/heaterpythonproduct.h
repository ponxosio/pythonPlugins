#ifndef HEATERPYTHONPRODUCT_H
#define HEATERPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/heaterpluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class HeaterPythonProduct : public HeaterPluginProduct
{
public:
    HeaterPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~HeaterPythonProduct();

    virtual void changeTemperature(units::Temperature value);
    virtual void turnOff();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // HEATERPYTHONPRODUCT_H
