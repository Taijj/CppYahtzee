#include "Game.h"

#include "../Global/Rules.h"

Game::ExitCode Game::Run()
{    
    _isExited = false;
    _currentRound = 0;

    while (_currentRound < Rules::ROUND_COUNT)
    {
        for (std::uint32_t i = 0; i < Model::GetPlayers().size(); ++i)
        {
            _currentPlayerId = i;
            RunTurn();
                       
            if (_turn->WasCanceled())
                return Canceled;

            if (IsRoundCutShort())
                break;
        }        

        ++_currentRound;
    }

    return Completed;
}

void Game::RunTurn()
{
    _turn->Start(_currentPlayerId);
    //renderer.UpdateRound(currentRound, players[i].GetId());
        
    while (_turn->IsRunning())
        _turn->Run();
}

bool Game::IsRoundCutShort()
{
    const auto &players = Model::GetPlayers();
    std::uint32_t playerCount = static_cast<std::uint32_t>(players.size());
    if (playerCount <= 1)
        return false;

    if (_currentRound < Rules::ROUND_COUNT - 1)
        return false;

    std::uint32_t currentScore = players.at(_currentPlayerId)->TotalScore();
    for (std::uint32_t j = _currentPlayerId+1; j < playerCount; ++j)
    {
        if (players[j]->PotentialScore() > currentScore)
            return false;
    }

    return true;
}