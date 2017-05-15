#ifndef PUMPPYTHONPRODUCT_H
#define PUMPPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/pumppluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class PumpPythonProduct : public PumpPluginProduct
{
public:
    PumpPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~PumpPythonProduct();

    virtual void setPumpState(int dir, units::Volumetric_Flow rate);
    virtual void stopPump();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // PUMPPYTHONPRODUCT_H
