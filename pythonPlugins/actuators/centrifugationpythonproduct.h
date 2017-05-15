#ifndef CENTRIFUGATIONPYTHONPRODUCT_H
#define CENTRIFUGATIONPYTHONPRODUCT_H

#include <memory>
#include <string>

#include <communications/CommandSender.h>
#include <commonmodel/plugininterface/centrifugatepluginproduct.h>
#include <commonmodel/plugininterface/pluginconfiguration.h>

#include "pythonPlugins/environment/PythonEnvironment.h"

class CentrifugationPythonProduct : public CentrifugatePluginProduct
{
public:
    CentrifugationPythonProduct(std::shared_ptr<PluginConfiguration> configurationObj, std::shared_ptr<CommandSender> communications);
    virtual ~CentrifugationPythonProduct();

    virtual void startCentrifugate(units::Frequency intensity);
    virtual void turnOff();

protected:
    std::string referenceName;
    std::shared_ptr<PluginConfiguration> configurationObj;
    std::shared_ptr<CommandSender> communications;
};

#endif // CENTRIFUGATIONPYTHONPRODUCT_H
