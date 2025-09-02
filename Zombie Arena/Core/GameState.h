#pragma once
namespace zombieArena 
{
    enum class ZombieGameState
    {
        Invalid = -1,
        StartMenu,
        Paused,
        Level,
        Upgrading,
        GameOver,
    };
}
