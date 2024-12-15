cmake_minimum_required(VERSION 3.29)
project(cpp-boilerplate)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp-boilerplate
        main.cpp
        Actor/Actor.cpp
        Actor/Actor.h
        Math/Vector.hpp
        Math/Math.cpp
        Math/Math.h
        Network/Packet/PacketBase.cpp
        Network/Packet/PacketBase.h
        Network/NetworkDefinition.h
        Network/SendFilter/Filter/PacketSendFilterBase.h
        Network/SendFilter/Filter/PacketSendFilter_DoOnce.cpp
        Network/SendFilter/Filter/PacketSendFilter_DoOnce.h
        Network/SendFilter/PakcetSendFilterManager.cpp
        Network/SendFilter/PakcetSendFilterManager.h
        Log/LogDefinition.h
)
