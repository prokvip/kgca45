#include "APlayerCharacter.h"
#include "UWorld.h"
void APlayerCharacter::Tick()
{
    if (UWorld::m_Input->GetKey('W') == KEY_HOLD)
    {
        Move(0.0f, -1.0f);
    }
    if (UWorld::m_Input->GetKey('S') == KEY_HOLD)
    {
        Move(0.0f, 1.0f);
    }
    if (UWorld::m_Input->GetKey('A') == KEY_HOLD)
    {
        Move(-1.0f, 0.0f);
    }
    if (UWorld::m_Input->GetKey('D') == KEY_HOLD)
    {
        Move(1.0f, 0.0f);
    }   
}