#include "SimpleECSModule.h"
#include "SimpleECSPCH.h"

class FSimpleECSModule : public ISimpleECSModule
{
public:
    virtual void StartupModule() override {}
    virtual void ShutdownModule() override {}
};

IMPLEMENT_MODULE( FSimpleECSModule, SimpleECS );
