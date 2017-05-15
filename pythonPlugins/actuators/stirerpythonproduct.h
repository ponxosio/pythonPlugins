#ifndef STIRERPYTHONPRODUCT_H
#define STIRERPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/stirerpluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class StirerPythonProduct : public StirerPluginProduct
{
public:
    StirerPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~StirerPythonProduct();

    virtual void stir(units::Frequency intensity);
    virtual void turnOff();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // STIRERPYTHONPRODUCT_H
