#include "Game.h"

#include "../Global/Rules.h"
#include "../View/View.h"

std::uint32_t Game::ShowWelcome()
{    
    View::RenderWelcome();

    std::uint32_t count = 0;
    while (count == 0)
    {
        count = Input::ForPlayerCount();

        if (count == 0)
            View::RenderInvalidInput();
    }
    return count;
}

void Game::Run()
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
                return;

            if (IsRoundCutShort())
                break;
        }        

        ++_currentRound;
    }
    
    ShowScoreBoard();
}

void Game::RunTurn()
{
    _turn->Start(_currentRound, _currentPlayerId);
        
    while (_turn->IsRunning())
        _turn->Run();
}

bool Game::IsRoundCutShort()
{
    const auto& players = Model::GetPlayers();
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

void Game::ShowScoreBoard()
{
    const auto& players = Model::GetPlayers();
    const auto& winner = Model::GetCurrentLeader();
    
    std::vector<View::Player> viewPlayers;
    for (const auto& player : players)
    {
        std::vector<View::ComboData> combos;
        for (const auto& c : Model::COMBOS)
        {
            std::int32_t score;
            player->TryGetScore(c->Kind(), score);

            std::string command = Input::SCORE_COMMANDS.at(c->Kind() - 1).first;

            combos.push_back({ c->Name(), command, score });
        }

        viewPlayers.push_back({
                combos,
                player->TotalScore(),
                player->HasBonus() ? Rules::BONUS_SCORE : 0,
                player->Id() == winner.Id()
            });
    }

    View::Clear();
    View::RenderScoreBoard(viewPlayers);

    View::RenderGoodBye();
    Input::WaitForEnter();
}