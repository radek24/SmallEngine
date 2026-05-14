#include "Engine/App.h"
#include "EntryPoint.h"
#include "Levels/MainMenuLevel.h"
#include "Levels/SimpleTestSaveLevel.h"

class Sandbox final : public App
{
public:
    explicit Sandbox(const Specifications& AppSpec): App()
    {
        Init(AppSpec);
        QueueLevelTransition<MainMenuLevel>();
    }
    ~Sandbox() override{}
};

App* CreateApplication()
{
    int* p = new int[5];                                                                                                                                                                                                                                                                                                p[10] = 42; // heap buffer overflow
    delete[] p;

    Specifications AppSpec;
    AppSpec.AppName = "Sandbox";
    AppSpec.WindowSpecs.Size = Vector2i(900,900);
    AppSpec.WindowSpecs.Name = "Sandbox Window";
    AppSpec.WindowSpecs.IsResizable = true;

    return new Sandbox(AppSpec);
}