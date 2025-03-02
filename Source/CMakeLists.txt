cmake_minimum_required(VERSION 3.29)
project(cpp-playground)

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
        Network/SendFilter/PakcetSendFilterManager.cpp
        Network/SendFilter/PakcetSendFilterManager.h
        Log/LogDefinition.h
        Network/Packet/PacketDefinition.h

        Engine/Definition/TypeDefinition.h
        Engine/Runtime/Core/CoreGlobals.cpp
        Engine/Runtime/Core/CoreGlobals.h
        Engine/Runtime/Launch/EngineLoop.cpp
        Engine/Runtime/Launch/EngineLoop.h
        Engine/Runtime/Launch/Launch.cpp
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
)
