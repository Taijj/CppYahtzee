#include <iostream>
#include <format>
#include <exception>

#include "../Headers/Config.h"
#include "../Headers/Turn.h"
#include "../Headers/Renderer.h"

int main()
{
    GameDice dice = GameDice{};
    for (std::uint32_t i = 0; i < Rules::DICE; ++i)
        dice[i].Initialize(i+1);
        
    Renderer renderer = Renderer{ dice };
    Turn turn = Turn{ dice, renderer };
    
    std::uint32_t currentRound = 0;
    while(currentRound < Rules::ROUNDS)
    {        
        renderer.UpdateRound(currentRound+1);

        turn.Execute();
            
        if(turn.IsCompleted())
            ++currentRound;
        else if(turn.IsExited())
            break;
    } 

    return 0;
}