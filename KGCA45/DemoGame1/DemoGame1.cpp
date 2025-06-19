#include <iostream>
#include "TWindow.h"
int main()
{
    TWindow win;
    win.SetWindow(GetModuleHandle(nullptr));
    win.Run();    
}
