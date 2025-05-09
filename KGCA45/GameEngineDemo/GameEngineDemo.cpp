#include <iostream>
#include "UInputComponent.h"
#include "UTimerComponent.h"
// 해당 프로젝트 속성->일반->
// 출력디렉토리(실행파일경로)           : ../../output/
// 중간디렉토리(목적파일/디버그정보파일): ../../output/해당프로젝트명(예:GameEngineDemo)
int main()
{
    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    {
        UInputComponent input(L"GameInput");
        input.SetName(L"DemoInput");
        std::wcout << input.GetNumInstance() << std::endl;
        std::wcout << input.GetName() << std::endl;
    }
    std::wcout << UActorComponent::GetNumInstance() << std::endl;

    UTimerComponent timer(L"GameTimer");
    timer.SetName(L"DemoTimer");
    std::wcout << timer.GetNumInstance() << std::endl;
    std::wcout << timer.GetName() << std::endl;

    std::wcout << UActorComponent::GetNumInstance() << std::endl;

}
