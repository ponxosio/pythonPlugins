#ifndef LIGTHPYTHONPRODUCT_H
#define LIGTHPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/lightpluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class LigthPythonProduct : public LightPluginProduct
{
public:
    LigthPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~LigthPythonProduct();

    virtual void applyLight(units::LuminousIntensity intensity, units::Length wavelenght);
    virtual void turnOffLight();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};


#endif // LIGTHPYTHONPRODUCT_H
