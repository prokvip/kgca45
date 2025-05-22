#include <iostream>
#include "Sample.h"

int main()
{
    Sample game;
    game.InitGame();    
    game.SetWindow(GetModuleHandle(nullptr));
    game.Run();
    game.ReleaseGame();
    _getch();
}
