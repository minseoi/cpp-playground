/* Created by minseoi */

#include "GameInstance.h"

#include "Engine/Runtime/Engine/Engine.h"

void GameInstance::InitializeStandalone()
{
    WorldContextPtr = &GetEngine()->CreateNewWorldContext();
    WorldContextPtr->owningGameInstance = shared_from_this();

    Init();
}

void GameInstance::StartGameInstnace()
{
    BroadcastOnStart();
}

void GameInstance::BroadcastOnStart()
{
    OnStart();
}

void GameInstance::Init()
{
    //todo: 서브시스템
    //SubsystemCollection.Initialize(this);
}

void GameInstance::OnStart()
{
}

Engine* GameInstance::GetEngine()
{
    return GEngine;
}

std::shared_ptr<World> GameInstance::GetWorld() const
{
    return WorldContextPtr ? WorldContextPtr->World() : nullptr;
}

void GameInstance::OnConsoleInput(const std::string &Command)
{
}
