/* Created by minseoi */

#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class CommandRegistry
{
public:
    using CommandCallback = std::function<void(const std::vector<std::string>&)>;

private:
    struct CommandInfo
    {
        std::string Description;
        CommandCallback Callback;
    };

    std::unordered_map<std::string, CommandInfo> m_commandMap;

public:
    void RegisterCommand(const std::string& Command, const std::string& Description,
                         CommandCallback Callback);
    void Tick();
    void ExecuteCommand(const std::string& Input);
};

extern CommandRegistry GCommandRegistry;
