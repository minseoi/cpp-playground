/* Created by minseoi */

#include "EngineLoop.h"
#include "Engine/Runtime/Engine/Engine.h"
#include "Engine/Runtime/Core/Console/CommandRegistry.h"
#include "Engine/Runtime/Core/Misc/App.h"
#include "Engine/Runtime/Core/CoreGlobals.h"
#include <iostream>

int32 EngineLoop::Init()
{
    GEngine = new Engine();
    if (!GEngine)
    {
        return -1;
    }

    GEngine->Init(this);

    GEngine->Start();

    LOG_I("Engine is initialized.");

    // Register example console commands
    GCommandRegistry.RegisterCommand(
        "quit",
        "Exit the engine",
        [](const std::vector<std::string>&) { GIsRequestingExit = true; });

    GCommandRegistry.RegisterCommand(
        "echo",
        "Print all provided arguments",
        [](const std::vector<std::string>& Args) {
            for (size_t i = 0; i < Args.size(); ++i)
            {
                std::cout << Args[i] << (i + 1 < Args.size() ? " " : "\n");
            }
            if (Args.empty())
            {
                std::cout << std::endl;
            }
        });

    GCommandRegistry.RegisterCommand(
        "time",
        "Print current engine time",
        [](const std::vector<std::string>&) {
            std::cout << "Current Time: " << App::GetCurrentTime() << std::endl;
        });

    GCommandRegistry.RegisterCommand(
        "sum",
        "Sum integer arguments",
        [](const std::vector<std::string>& Args) {
            long long Sum = 0;
            for (const std::string& Str : Args)
            {
                Sum += std::stoll(Str);
            }
            std::cout << "Sum: " << Sum << std::endl;
        });

    return 0;
}

void EngineLoop::Tick()
{
    GEngine->UpdateTimeAndHandleMaxTickRate();

    {
        bool bIdleMode = false;
        // main game engine tick
        GEngine->Tick(App::GetDeltaTime(), bIdleMode);
    }

    GCommandRegistry.Tick();
}

void EngineLoop::Exit()
{
}
