#include "Engine/App.h"
#include "EntryPoint.h"
#include "Levels/TestLevel.h"

class Sandbox final : public App
{
public:
    explicit Sandbox(const Specifications& AppSpec): App()
    {
        Init(AppSpec);
        QueueLevelTransition<TestLevel>();
    }
    ~Sandbox() override{}
};

App* CreateApplication()
{
    Specifications AppSpec;
    AppSpec.AppName = "Sandbox";
    AppSpec.WindowSpecs.Size = Vector2i(500,500);
    AppSpec.WindowSpecs.Name = "Sandbox Window";

    return new Sandbox(AppSpec);
}