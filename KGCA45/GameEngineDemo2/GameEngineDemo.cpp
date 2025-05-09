#include <iostream>
#include "UInputComponent.h"
#include "UTimerComponent.h"
// 해당 프로젝트 속성->일반->
// 출력디렉토리(실행파일경로)           : ../../output/
// 중간디렉토리(목적파일/디버그정보파일): ../../output/해당프로젝트명(예:GameEngineDemo)

int main()
{
    // 한글 출력
    std::wcout.imbue(std::locale("kor"));

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    
    UActorComponent* comp[2];
    comp[0] = new UInputComponent(L"GameInput");
    comp[1] = new UTimerComponent(L"GameTimer");
 
    for (int i = 0; i < 2; i++)
    {
        comp[i]->Frame();
    } 

   /* while (timer->GetGameGlobalTimer() < 60.0f)
    {
        timer->Frame();
        std::wcout << timer->GetGameGlobalTimer() << std::endl;
    }
    std::wcout << timer->GetGameGlobalTimer() << std::endl;
    */
    for (int i = 0; i < 2; i++)
    {
        delete comp[i];
    }
    //delete timer;
    //delete input;
    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
