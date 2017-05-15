#ifndef SHAKEPYTHONPRODUCT_H
#define SHAKEPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/shakepluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class ShakePythonProduct : public ShakePluginProduct
{
public:
    ShakePythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~ShakePythonProduct();

    virtual void startShake(units::Frequency intensity);
    virtual void stopShake();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // SHAKEPYTHONPRODUCT_H
