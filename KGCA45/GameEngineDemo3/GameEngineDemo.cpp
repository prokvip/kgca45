
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
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
    // 복사생성자, 대입연산자 오버로딩
    UTimerComponent time0(L"test");
    UTimerComponent time1 = time0;
    UTimerComponent time2;
    time2 = time0;


    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    
      // 게임생성
    std::list< UActorComponent*> compList;
    compList.push_back(new UTimerComponent(L"GameTimer"));
    compList.push_back(new UInputComponent(L"GameInput"));
    compList.push_back(new USoundComponent(L"GameSound"));
    //UActorComponent* compList[3];
    //compList[0] = new UTimerComponent(L"GameTimer");
    //compList[1] = new UInputComponent(L"GameInput"); 
    //compList[2] = new USoundComponent(L"GameSound");
   
    // 정적배열만 가능
    int isize = compList.size();
    UTimerComponent* timer =  dynamic_cast<UTimerComponent*>(compList[0]);
    UInputComponent* input =  dynamic_cast<UInputComponent*>(compList[1]);
    /*UTimerComponent* timer =  static_cast<UTimerComponent*>(comp0]);*/
    if (timer == nullptr)
    {
        for (std::list<UActorComponent*>::iterator pNode =
            compList.begin();
            pNode != compList.end();
            pNode++)
        {
            delete *pNode;
        }
        compList.clear();

        /*for (TNode* pNode = list.Head();
            pNode != list.Tail();
            pNode = pNode->pNext)
        {

        }*/       
        return 1;
    }
    // 게임로직
    while (timer->GetGameGlobalTimer() < 60.0f)
    {
        for (auto pNode = compList.begin();
             pNode != compList.end();
             pNode++)
        {
            //UActorComponent* actorComp = *pNode;
            (*pNode)->TickComponent();
        }       
        if (GameLoop(input))
        {
            break;
        }
        //std::wcout << timer->GetGameGlobalTimer() << std::endl;
    }
    std::wcout << timer->GetGameGlobalTimer() << std::endl;
    
    // 게임 종료
    for (auto pNode : compList)
    {
        delete pNode;
    }
    compList.clear();
    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
