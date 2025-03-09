/* Created by minseoi */

#include "EngineConfigSubsystem.h"

#include <fstream>
#include "nlohmann/json.hpp"

#include "Engine/Runtime/Core/Logging/LogMacros.h"
#include "Engine/Runtime/Core/Misc/Path.h"
#include "Log/LogDefinition.h"

void EngineConfigSubsystem::Initialize(ISubsystemCollection &_subsystemCollection)
{
    SubsystemBase::Initialize(_subsystemCollection);

    std::ifstream configFile(Path::ProjectDir("Config/Engine.json"));
    if (!configFile.is_open())
    {
        LOG_E("Failed to open Config/Engine.json");
        return;
    }

    try
    {
        nlohmann::json configJson;
        configFile >> configJson;

        LOG_I("Engine.json contents: %s", configJson.dump(4).c_str());
    }
    catch (const std::exception& ex)
    {
        LOG_E("Error parsing Engine.json: %s", ex.what());
    }

    LOG_D("ConfigSubsystem initialized");
}
