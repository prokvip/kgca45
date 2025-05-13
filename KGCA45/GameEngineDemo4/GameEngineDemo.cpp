#include "UWorld.h"
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
    UWorld world;
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"AActor";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        AActor* actor = new AActor(name);
        actor->SetRect({ 0.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.push_back(actor);
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"APawn";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto pawn = new APawn;
        pawn->SetName(name);
        pawn->SetRect({ 400.0f, 300.0f }, { 100.0f,100.0f });
        world.m_ActorList.push_back(pawn);
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"ACharacer";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto character = new ACharacter;
        character->SetName(name);
        character->SetRect({ 400.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.push_back(character);
    }
    for (int i = 0; i < world.m_ActorList.size(); i++)
    {
        AActor* actor = world.m_ActorList[i];// 인덱싱 지원
        actor->Show();
    }
    for (int i = 0; i < world.m_ActorList.size(); i++)
    {
        AActor* actor = world.m_ActorList[i];// 인덱싱 지원
        actor->Move(10.0f, 10.0f);
        actor->Show();
    }
    for (int i = 0; i < world.m_ActorList.size(); i++)
    {
        AActor* actor = world.m_ActorList[i];// 인덱싱 지원
       actor->Tick();
    }
    /*for (std::vector<AActor*>::iterator pNode =
        world.m_ActorList.begin();
        pNode != world.m_ActorList.end();
        pNode++)
    {
        std::wcout << (*pNode)->GetName() << std::endl;
    }*/

    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    
    // 게임생성
    std::list< UActorComponent*> compList;
    compList.push_back(new UTimerComponent(L"GameTimer"));
    UTimerComponent* timer = dynamic_cast<UTimerComponent*>(compList.back());
    compList.push_back(new UInputComponent(L"GameInput"));
    UInputComponent* input = dynamic_cast<UInputComponent*>(compList.back());
    compList.push_back(new USoundComponent(L"GameSound"));

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
    for (AActor* pActor : world.m_ActorList)
    {
        delete pActor;
    }
    for (UActorComponent* pNode : compList)
    {
        delete pNode;
    }
    compList.clear();
    world.m_ActorList.clear();

    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
