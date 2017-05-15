#ifndef ELECTROPHORESISPYTHONPRODUCT_H
#define ELECTROPHORESISPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/electrophoresispluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class ElectrophoresisPythonProduct : public ElectrophoresisPluginProduct
{
public:
    ElectrophoresisPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~ElectrophoresisPythonProduct();

    virtual void startElectrophoresis(units::ElectricField fieldStrenght);
    virtual std::shared_ptr<ElectrophoresisResult> stopElectrophpresis();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // ELECTROPHORESISPYTHONPRODUCT_H
