#include <iostream>
#include <format>
#include <exception>

#include "../Headers/Config.h"
#include "../Headers/Turn.h"
#include "../Headers/Renderer.h"
#include "../Headers/Player.h"

int main()
{
    GameDice dice = GameDice{};
    for (std::uint32_t i = 0; i < Rules::DICE; ++i)
        dice[i].Initialize(i+1);

    Player player = Player(1);
    player.Reset();
        
    Renderer renderer = Renderer{ dice };
    Turn turn = Turn{ dice, renderer };
        
    bool isCanceled = false;
    std::uint32_t currentRound = 0;
    while(true) // round loop
    {
        renderer.UpdateRound(currentRound);
        turn.Start(player);

        while (true) // turn loop
        {
            Turn::State state = turn.Run();
            isCanceled = state == Turn::State::Canceled;
                        
            if (isCanceled || state == Turn::State::Completed)
                break;
        }

        ++currentRound;
        if (isCanceled || currentRound >= Rules::ROUNDS)
            break;
    } 

    Utils::Log("\n- Thanks for playing! -\n");
    return 0;
}