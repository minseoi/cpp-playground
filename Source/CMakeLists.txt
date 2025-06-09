cmake_minimum_required(VERSION 3.29)
project(cpp-playground)

include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp-playground
        main.cpp
        Actor/Actor.cpp
        Actor/Actor.h
        Math/Vector.hpp
        Math/Math.cpp
        Math/Math.h
        Network/Packet/PacketBase.hpp
        Network/NetworkDefinition.h
        Network/SendFilter/Filter/PacketSendFilterBase.h
        Network/SendFilter/Filter/PacketSendFilterDoOnce.cpp
        Network/SendFilter/Filter/PacketSendFilterDoOnce.h
        Network/SendFilter/Filter/PacketSendFilterCooldown.cpp
        Network/SendFilter/Filter/PacketSendFilterCooldown.h
        Network/SendFilter/PacketSendFilterManager.cpp
        Network/SendFilter/PacketSendFilterManager.h
        Log/LogDefinition.h
        Network/Packet/PacketDefinition.h

        Engine/Definition/TypeDefinition.h
        Engine/Runtime/Core/CoreGlobals.cpp
        Engine/Runtime/Core/CoreGlobals.h
        Engine/Runtime/Launch/EngineLoop.cpp
        Engine/Runtime/Launch/EngineLoop.h
        Engine/Runtime/Launch/Launch.cpp
        Engine/Runtime/Core/Console/CommandRegistry.cpp
        Engine/Runtime/Core/Console/CommandRegistry.h
        Engine/Runtime/Engine/Engine.cpp
        Engine/Runtime/Engine/Engine.h
        Engine/Runtime/Core/Logging/LogMacros.h
        Engine/Runtime/Engine/Classes/World/World.cpp
        Engine/Runtime/Engine/Classes/World/World.h
        Engine/Runtime/Core/GenericPlatform/GenericPlatformTime.cpp
        Engine/Runtime/Core/GenericPlatform/GenericPlatformTime.h
        Engine/Runtime/Core/Misc/App.cpp
        Engine/Runtime/Core/Misc/App.h
        Engine/Runtime/Launch/Launch.h
        Engine/Runtime/Engine/Classes/GameInstance.cpp
        Engine/Runtime/Engine/Classes/GameInstance.h
        Engine/Runtime/Core/Misc/Path.cpp
        Engine/Runtime/Core/Misc/Path.h
        Engine/Runtime/Engine/Subsystem/Base/SubsystemBase.cpp
        Engine/Runtime/Engine/Subsystem/Base/SubsystemBase.h
        Engine/Runtime/Engine/Subsystem/Base/SubsystemCollection.hpp
        Engine/Runtime/Engine/Subsystem/EngineSubsystemCollection.hpp
        Engine/Runtime/Engine/Subsystem/Engine/EngineConfigSubsystem.cpp
        Engine/Runtime/Engine/Subsystem/Engine/EngineConfigSubsystem.h
        Engine/Runtime/Engine/Subsystem/Base/ISubsystemCollection.hpp
)

target_link_libraries(cpp-playground PRIVATE nlohmann_json::nlohmann_json)

# tests
enable_testing()
add_executable(
        math_tests
        ../tests/test_math.cpp
        Math/Math.cpp
)
add_test(NAME math_tests COMMAND math_tests)
