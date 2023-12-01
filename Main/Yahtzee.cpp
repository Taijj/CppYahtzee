#include "Model/Model.h"
//#include "View/View.h"

#include <iostream>

int main()
{	
	auto check = [](Score::Kind k, std::uint32_t expected)
		{
			const auto is = Model::COMBOS.at(k - 1)->MaxPossibleScore();

			std::cout << is << '\n';
		};

	check(Score::Aces, 5);
	check(Score::Twos, 10);
	check(Score::Threes, 15);
	check(Score::Fours, 20);
	check(Score::Fives, 25);
	check(Score::Sixes, 30);

	check(Score::OfKind3, 30);
	check(Score::OfKind4, 30);
	check(Score::FullHouse, 25);
	check(Score::StraightSmall, 30);
	check(Score::StraightLarge, 40);
	check(Score::Yahtzee, 50);
	check(Score::Chance, 30);



	return 0;
}



//#include <iostream>
//#include <format>
//#include <exception>
//#include <vector>
//#include <string>
//
//#include "../Headers/Config.h"
//#include "../Headers/Turn.h"
//#include "../Headers/Renderer.h"
//#include "../Headers/Player.h"
//#include "../Headers/Input.h"
//
//
//
//void TestScoring(GameDice& dice, std::uint32_t sampleCount)
//{
//    for (const Combo* combo : COMBOS)
//    {
//        for (std::uint32_t i = 0; i < sampleCount; ++i)
//        {
//            std::string rolls = "";
//            for (Die& d : dice)
//            {
//                d.Roll();
//                rolls += std::format("{}, ", d.GetValue());
//            }
//
//            Utils::Log(std::format("{} : {} -- {} --Max: {}",
//                combo->Name(), combo->Score(dice), rolls, combo->MaxPossibleScore()));
//        }
//    }
//}
//
//int main()
//{
//    GameDice dice = GameDice{};
//    for (std::uint32_t i = 0; i < Rules::DICE; ++i)
//        dice[i].Initialize(i+1);
//
//    //Uncomment for testing
//    /*TestScoring(dice, 100);
//    return 0;*/   
//
//    Renderer renderer = Renderer{ dice };
//    Turn turn = Turn{ dice, renderer };    
//    
//
//    renderer.RenderPlayers();
//    const std::uint32_t playerCount = Input::GetPlayers();
//    std::vector<Player> players = {};
//    for (std::uint32_t i = 0; i < playerCount; ++i)
//    {
//        Player player = Player(i+1);
//        player.Reset();
//        players.push_back(player);
//    }
//
//
//
//    bool isCanceled = false;
//    bool isSkipped = false;
//    std::uint32_t currentRound = 0;
//    while(true) // round loop
//    {
//        for (std::uint32_t i = 0; i < playerCount; ++i)
//        {
//            turn.Start(players[i]);
//            renderer.UpdateRound(currentRound, players[i].GetId());
//
//            while (true) // turn loop
//            {
//                Turn::State state = turn.Run();
//                isCanceled = state == Turn::State::Canceled;
//
//                if (isCanceled || state == Turn::State::Completed)
//                    break;
//            }
//
//            if (currentRound == Rules::ROUNDS-1 && playerCount > 1)
//            {
//                for (std::uint32_t j = i+1; j < playerCount; ++j)
//                {
//                    if (players[j].GetPotential() > players[i].GetTotal())
//                        break;
//
//                    isSkipped = true;
//                }
//            }
//
//            if (isCanceled || isSkipped)
//                break;
//        }   
//
//        ++currentRound;
//        if (isCanceled || currentRound >= Rules::ROUNDS)
//            break;
//    }        
//    
//    const std::uint32_t width = 20;
//
//    // Headline    
//    std::cout << "== Game Over == " << std::endl;
//    std::cout << std::endl;
//
//    // Player Labels
//    for (Player& player : players)
//        std::cout << std::setw(width) << std::left << std::format("Player #{}:", player.GetId());
//    std::cout << std::endl;
//
//    // Combos
//    for (const Combo* c : COMBOS)
//    {
//        for (Player& player : players)
//        {
//            std::cout << std::setw(width) << std::left
//                << std::format("{}: {}", c->Name(), player.GetScore(c->Kind()));
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//
//    // Player Bonus
//    for (Player& player : players)
//    {
//        std::cout << std::setw(width) << std::left
//            << std::format("Bonus: {}", player.HasReachedBonus() ? std::to_string(Rules::BONUS_SCORE) : "0");
//    }
//    std::cout << std::endl;
//
//    // Totals
//    for (Player& player : players)
//    {
//        std::cout << std::setw(width) << std::left
//            << std::format("Total: {}", player.GetTotal());
//    }
//    std::cout << std::endl;
//    
//    // Winner
//    Player winner = *std::max_element(players.begin(), players.end(),
//        [](const Player& p1, const Player& p2) { return p1.GetTotal() < p2.GetTotal(); });
//
//    std::cout << std::endl;
//    std::cout << "Player #" << winner.GetId() << " won!";
//
//    Input::WaitForAnyKey();
//
//    Utils::Log("\n- Thanks for playing! -\n");
//    return 0;
//}