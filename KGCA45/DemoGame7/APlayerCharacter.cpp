#include "APlayerCharacter.h"
#include "TEngine.h"
#include "UInputComponent.h"

void APlayerCharacter::Tick()
{
    if (TEngine::gInput->GetKey('W') == KEY_HOLD)
    {
        Move(0.0f, -1.0f);
    }
    if (TEngine::gInput->GetKey('S') == KEY_HOLD)
    {
        Move(0.0f, 1.0f);
    }
    if (TEngine::gInput->GetKey('A') == KEY_HOLD)
    {
        Move(-1.0f, 0.0f);
    }
    if (TEngine::gInput->GetKey('D') == KEY_HOLD)
    {
        Move(1.0f, 0.0f);
    }   
}