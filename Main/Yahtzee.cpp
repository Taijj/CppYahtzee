#include "Model/Model.h"
#include "Controller/Game.h"
//#include "View/View.h"





int main()
{
    // TODO: Input
    Model::Wake(3);

    Game game = {};
    Game::ExitCode code = game.Run();
    
    //const std::uint32_t width = 20;

    //// Headline    
    //std::cout << "== Game Over == " << std::endl;
    //std::cout << std::endl;

    //// Player Labels
    //for (Player& player : players)
    //    std::cout << std::setw(width) << std::left << std::format("Player #{}:", player.GetId());
    //std::cout << std::endl;

    //// Combos
    //for (const Combo* c : COMBOS)
    //{
    //    for (Player& player : players)
    //    {
    //        std::cout << std::setw(width) << std::left
    //            << std::format("{}: {}", c->Name(), player.GetScore(c->Kind()));
    //    }
    //    std::cout << std::endl;
    //}
    //std::cout << std::endl;

    //// Player Bonus
    //for (Player& player : players)
    //{
    //    std::cout << std::setw(width) << std::left
    //        << std::format("Bonus: {}", player.HasReachedBonus() ? std::to_string(Rules::BONUS_SCORE) : "0");
    //}
    //std::cout << std::endl;

    //// Totals
    //for (Player& player : players)
    //{
    //    std::cout << std::setw(width) << std::left
    //        << std::format("Total: {}", player.GetTotal());
    //}
    //std::cout << std::endl;
    //
    //// Winner
    //Player winner = *std::max_element(players.begin(), players.end(),
    //    [](const Player& p1, const Player& p2) { return p1.GetTotal() < p2.GetTotal(); });

    //std::cout << std::endl;
    //std::cout << "Player #" << winner.GetId() << " won!";

    //Input::WaitForAnyKey();

    //Utils::Log("\n- Thanks for playing! -\n");
    return 0;
}