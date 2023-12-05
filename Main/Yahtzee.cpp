#include "Model/Model.h"
#include "View/View.h"

#include "Controller/Game.h"
#include "Controller/Input.h"

int main()
{
    View::Wake();
    Model::Wake(1);

    std::vector<View::ComboData> comb;
    for (const auto& c : Model::COMBOS)
        comb.push_back({ c->Name(), 12 });

    View::RenderTable({
        View::DieData{0, 3, true},
        View::DieData{1, 5, false},
        View::DieData{2, 6, false},
        View::DieData{3, 1, false},
        View::DieData{4, 3, true},
        },
        comb);

    return 0 ;


    View::RenderWelcome();
    
    std::uint32_t count = 0;
    while (count == 0)
    {
         count = Input::ForPlayerCount();

         if (count == 0)
             View::RenderInvalidInput();
    }   
        
    Model::Wake(count);

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