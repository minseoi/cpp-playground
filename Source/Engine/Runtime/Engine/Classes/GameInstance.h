/* Created by minseoi */

#pragma once
#include <string>


class Engine;
struct WorldContext;
class World;

class GameInstance : public std::enable_shared_from_this<GameInstance>
{
protected:
    WorldContext* WorldContextPtr {};

public:
    explicit GameInstance() = default;
    virtual ~GameInstance() = default;

    void InitializeStandalone();
    void StartGameInstnace();
    void BroadcastOnStart();

    virtual void Init();
    virtual void OnStart();

    Engine* GetEngine();
    [[nodiscard]] std::shared_ptr<World> GetWorld() const;

protected:
    void OnConsoleInput(const std::string& Command);
};
