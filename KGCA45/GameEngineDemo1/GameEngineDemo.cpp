#include <iostream>
#include "UInputComponent.h"
#include "UTimerComponent.h"
// 해당 프로젝트 속성->일반->
// 출력디렉토리(실행파일경로)           : ../../output/
// 중간디렉토리(목적파일/디버그정보파일): ../../output/해당프로젝트명(예:GameEngineDemo)

void TestTimer()
{
    for (int i = 0; i < 10000000; i++)
    {
        sqrt(i);
    }
}
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

    while (timer.GetGameGlobalTimer() < 60.0f)
    {
        timer.Frame();
        std::wcout << timer.GetGameGlobalTimer() << std::endl;
    }
    std::wcout << timer.GetGameGlobalTimer() << std::endl;

    /*  테스트1
        *timer.m_Start = system_clock::now();
    {
        TestTimer();
    }
    timer.m_End   = system_clock::now();

    duration<float> sec = timer.m_End - timer.m_Start;
    float fTimer = sec.count(); */

    /* 테스트 2*/
    /*auto start = system_clock::now();
    system_clock::time_point end;
    float GameTimer =0.0f;
    while (GameTimer < 10.0f)
    {
        TestTimer();        
        end = system_clock::now();

        duration<float> sec = end - start;
        float fTimer = sec.count();
        GameTimer += fTimer;        
        start = end;
        std::wcout << GameTimer << std::endl;
    }

    std::wcout << GameTimer << std::endl;*/
    std::wcout << UActorComponent::GetNumInstance() << std::endl;

}
