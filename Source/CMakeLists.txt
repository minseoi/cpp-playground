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
)
