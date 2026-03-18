#include "Engine/App.h"
#include "EntryPoint.h"
#include "Levels/TestLevel.h"

class Sandbox final : public App
{
public:
    explicit Sandbox(const Specifications &AppSpec): App(AppSpec)
    {
        QueueLevelTransition<TestLevel>();
    }

    ~Sandbox() override
    {

    }

};

App* CreateApplication()
{
    Specifications AppSpec;
    AppSpec.AppName = "Sandbox";
    AppSpec.WindowSpecs.Size = Vector2i(500,500);
    AppSpec.WindowSpecs.Name = "SandboxWindow";
    return new Sandbox(AppSpec);
}