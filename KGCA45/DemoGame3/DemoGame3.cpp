#include <iostream>
#include "Sample.h"


int main()
{
    Sample game;   
    game.SetWindow(GetModuleHandle(nullptr));      
    game.InitGame();
    game.Run();
    game.ReleaseGame();   
}
