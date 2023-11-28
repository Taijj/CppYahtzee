#include <iostream>
#include <format>
#include <exception>
#include <vector>

#include "../Headers/Config.h"
#include "../Headers/Turn.h"
#include "../Headers/Renderer.h"
#include "../Headers/Player.h"
#include "../Headers/Input.h"



void TestScoring(GameDice& dice, std::uint32_t sampleCount)
{
    for (const Combo* combo : COMBOS)
    {
        for (std::uint32_t i = 0; i < sampleCount; ++i)
        {
            std::string rolls = "";
            for (Die& d : dice)
            {
                d.Roll();
                rolls += std::format("{}, ", d.GetValue());
            }

            Utils::Log(std::format("{} : {} -- {}", combo->Name(), combo->Score(dice), rolls));
        }
    }
}

int main()
{
    GameDice dice = GameDice{};
    for (std::uint32_t i = 0; i < Rules::DICE; ++i)
        dice[i].Initialize(i+1);

    //Uncomment for testing
    //TestScoring(dice, 100);
    //return 0;

    Renderer renderer = Renderer{ dice };
    Turn turn = Turn{ dice, renderer };    
    

    renderer.RenderPlayers();
    const std::uint32_t playerCount = Input::GetPlayers();
    std::vector<Player> players = {};
    for (std::uint32_t i = 0; i < playerCount; ++i)
    {
        Player player = Player(i+1);
        player.Reset();
        players.push_back(player);
    }



    bool isCanceled = false;
    std::uint32_t currentRound = 0;
    while(true) // round loop
    {
        for (std::uint32_t i = 0; i < playerCount; ++i)
        {
            turn.Start(players[i]);
            renderer.UpdateRound(currentRound, players[i].GetId());

            while (true) // turn loop
            {
                Turn::State state = turn.Run();
                isCanceled = state == Turn::State::Canceled;

                if (isCanceled || state == Turn::State::Completed)
                    break;
            }

            if (isCanceled)
                break;
        }   

        ++currentRound;
        if (isCanceled || currentRound >= Rules::ROUNDS)
            break;
    } 

    Utils::Log("\n- Thanks for playing! -\n");
    return 0;
}