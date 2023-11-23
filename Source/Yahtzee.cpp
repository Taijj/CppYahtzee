#include <iostream>
#include <format>
#include <exception>

#include "../Headers/Utils.h"
#include "../Headers/Round.h"
#include "../Headers/Renderer.h"

int main()
{
    GameDice dice = GameDice{};
    for (std::uint32_t i = 0; i < Rules::DICE; ++i)
        dice[i].Initialize(i+1);
        
    Renderer renderer = Renderer{ dice };
    Round round = Round{ dice, renderer };
    
    std::uint32_t currentRound = 0;
    while(currentRound < Rules::ROUNDS)
    {
        try
        {
            renderer.UpdateRound(currentRound+1);

            bool isCanceled = round.Execute();
            if (!isCanceled)
                ++currentRound;
            else
                break;
        }
        catch (std::exception e)
        {
            Utils::Log(e.what());
            break;
        }
    } 

    return 0;
}