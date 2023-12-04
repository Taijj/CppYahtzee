#pragma once

#include <memory>

#include "../Model/Model.h"
#include "Turn.h"



class Game
{

public:

    enum ExitCode
    {
        Completed = 0,
        Canceled = 1
    };

    Game() : _currentRound(0), _currentPlayerId(0), _isExited(false)
    {
        _turn = std::make_unique<Turn>();
    }

    ~Game() = default;

    ExitCode Run();

private:
    std::unique_ptr<Turn> _turn;

    std::uint32_t _currentPlayerId;
    std::uint32_t _currentRound;

    bool _isExited;

    void RunTurn();
    bool IsRoundCutShort();
};
