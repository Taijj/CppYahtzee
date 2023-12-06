#include "View/View.h"
#include "Model/Model.h"
#include "Controller/Game.h"

int main()
{       
    Game game = {};
    std::uint32_t playerCount = game.ShowWelcome();
    
    View::Wake();
    Model::Wake(playerCount);
    game.Run();

    return 0;
}