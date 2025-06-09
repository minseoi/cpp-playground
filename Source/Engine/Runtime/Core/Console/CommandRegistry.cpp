/* Created by minseoi */

#include "CommandRegistry.h"
#include <iostream>
#include <sstream>

CommandRegistry GCommandRegistry;

void CommandRegistry::RegisterCommand(const std::string& Command, const std::string& Description,
                                      CommandCallback Callback)
{
    m_commandMap[Command] = {Description, std::move(Callback)};
}

void CommandRegistry::ExecuteCommand(const std::string& Input)
{
    std::istringstream iss(Input);
    std::string cmd;
    iss >> cmd;
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg)
    {
        args.push_back(arg);
    }

    if (cmd == "help")
    {
        for (const auto& pair : m_commandMap)
        {
            std::cout << pair.first << " - " << pair.second.Description << std::endl;
        }
        return;
    }

    auto it = m_commandMap.find(cmd);
    if (it != m_commandMap.end())
    {
        if (it->second.Callback)
        {
            it->second.Callback(args);
        }
    }
}

void CommandRegistry::Tick()
{
    if (std::cin.rdbuf()->in_avail() > 0)
    {
        std::string input;
        std::getline(std::cin, input);
        ExecuteCommand(input);
    }
}
