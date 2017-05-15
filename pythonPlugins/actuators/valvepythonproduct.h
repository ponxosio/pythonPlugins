#ifndef VALVEPYTHONPRODUCT_H
#define VALVEPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/valvepluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class ValvePythonProduct : public ValvePluginProduct
{
public:
    ValvePythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~ValvePythonProduct();

    virtual void moveToPosition(int position);
    virtual void closeValve();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // VALVEPYTHONPRODUCT_H
