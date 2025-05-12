#include <iostream>
#include "UInputComponent.h"
#include "UTimerComponent.h"
// 해당 프로젝트 속성->일반->
// 출력디렉토리(실행파일경로)           : ../../output/
// 중간디렉토리(목적파일/디버그정보파일): ../../output/해당프로젝트명(예:GameEngineDemo)

bool  GameLoop(UInputComponent* input)
{
    if (input->GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        std::wcout << L"VK_LBUTTON key" << std::endl;
    }
    if (input->GetKey(VK_MBUTTON) == KEY_PUSH)
    {
        std::wcout << L"VK_MBUTTON key" << std::endl;
    }
    if (input->GetKey(VK_RBUTTON) == KEY_PUSH)
    {
        std::wcout << L"VK_RBUTTON key" << std::endl;
    }
    if (input->GetKey('W') == KEY_PUSH)
    {
        std::wcout << L"W key" << std::endl;
    }
    if (input->GetKey('S') == KEY_PUSH)
    {
        std::wcout << L"S key" << std::endl;
    }
    if (input->GetKey('A') == KEY_PUSH)
    {
        std::wcout << L"A key" << std::endl;
    }
    if (input->GetKey('D') == KEY_PUSH)
    {
        std::wcout << L"D key" << std::endl;
    }
    if (input->GetKey(VK_SPACE) == KEY_PUSH)
    {
        std::wcout << L"VK_SPACE key" << std::endl;
    }
    if (input->GetKey(VK_RETURN) == KEY_PUSH)
    {
        std::wcout << L"VK_RETURN key" << std::endl;
    }

    if (input->GetKey('X') == KEY_UP)
    {
        return true;
    }
    return false;
}
int main()
{
    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    
    // 동적할당에서 사용
    //int* pArray = new int[3];
    //int isize = _msize(pArray);// 전체 할당 메모리 
    //int i = sizeof(pArray);
    //int j = sizeof(pArray[0]);
    //int isize2 = _msize(pArray) / sizeof(pArray[0]);

    // 게임생성
    UActorComponent* comp[2];
    comp[0] = new UTimerComponent(L"GameTimer");
    comp[1] = new UInputComponent(L"GameInput"); 
   
    // 정적배열만 가능
    int isize = _countof(comp);
    UTimerComponent* timer =  dynamic_cast<UTimerComponent*>(comp[0]);
    UInputComponent* input =  dynamic_cast<UInputComponent*>(comp[1]);
    /*UTimerComponent* timer =  static_cast<UTimerComponent*>(comp0]);*/
    if (timer == nullptr)
    {
        for (int i = 0; i < isize; i++)
        {
            delete comp[i];
        }
        return 1;
    }
    // 게임로직
    while (timer->GetGameGlobalTimer() < 60.0f)
    {
        for (int i = 0; i < isize; i++)
        {
            comp[i]->TickComponent();
        }
        if (GameLoop(input))
        {
            break;
        }
        //std::wcout << timer->GetGameGlobalTimer() << std::endl;
    }
    std::wcout << timer->GetGameGlobalTimer() << std::endl;
    
    // 게임 종료
    for (int i = 0; i < isize; i++)
    {
        delete comp[i];
    }
    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
