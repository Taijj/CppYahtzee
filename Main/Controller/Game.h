#pragma once

#include <memory>

#include "../Model/Model.h"
#include "Turn.h"

/// <summary>
/// Organizes the flow of a whole game including intro/outro
/// and all of the game's turns for each player.
/// </summary>
class Game
{

public:
    
    Game() : _currentRound(0), _currentPlayerId(0), _isExited(false)
    {
        _turn = std::make_unique<Turn>();
    }

    ~Game() = default;

    /// <summary>
    /// Shows a welcome message and prompts the user to input the
    /// number of players.
    /// </summary>
    /// <returns>The count of players.</returns>
    std::uint32_t ShowWelcome();

    /// <summary>
    /// Loops over all turns for each player.
    /// </summary>
    void RunTurns();    
    

private:
    std::unique_ptr<Turn> _turn;

    std::uint32_t _currentPlayerId;
    std::uint32_t _currentRound;

    bool _isExited;

    void RunTurn();
    bool IsRoundCutShort();

    void ShowScoreBoard();
};
