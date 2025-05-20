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

void TestStlMap()
{
    // stl::map 자료구조 : 이진탐색트리(BST) : 추가된 순서로 저장되지 않는다.
    // 사용처 : 대용량 데이터 빠른 검색이 요구되는 경우.
    std::map<int, int> list;
    list[0] = 1000;//std::pair<int, int> first=0, second=1000
    list[3] = 1003;
    list[2] = 1002;
    list[1] = 1001;
    for (int i = 0; i < 4; i++)
    {
        // 키가 인덱싱이 지원된다.
        std::wcout << list[i] << std::endl;
    }
    for (std::map<int,int>::iterator iter = list.begin();
         iter != list.end();
         iter++)
    {
        std::pair<int, int> p = *iter;
        std::wcout << p.first << L":" << p.second << std::endl;
        p.second = 8888;
    }
    for (std::pair<const int,int>& p : list)
    {        
        std::wcout << p.first << L":" << p.second << std::endl;
        p.second = 9999;
    }
    for (auto& p : list)
    {
        std::wcout << p.first << L":" << p.second << std::endl;
        p.second = 1111;
    }
    auto iter = list.find(6);
    if (iter != list.end())
    {
        std::wcout << iter->second;
    }
    //list2[] 인덱싱으로 추가하면 안된다.
    std::map<std::wstring, int> list2;
    list2[L"a"] = 1000;
    list2[L"b"] = 1003;
    list2[L"c"] = 1002;
    list2[L"a"] = 1001;// 겹침
    for (auto p : list2)
    {
        std::wcout << p.second << std::endl;
    }

    std::map<std::wstring, int> list3;    
    list3.insert(std::make_pair(L"a", 1000));
    list3.insert(std::make_pair(L"b", 1001));
    list3.insert(std::make_pair(L"c", 1002));
    list3.insert(std::make_pair(L"a", 1006));
    for (auto p : list3)
    {
        std::wcout << p.second << std::endl;
    }
}
int main()
{      
    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    TestStlMap();

    UWorld world;
    for (int i = 0; i < 3; i++)
    {
        std::wstring name = L"AActor";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto actor = std::make_shared<AActor>(name);
        actor->SetRect({ 0.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.insert(
            std::make_pair(name, actor));
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"APawn";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto pawn = std::make_shared<APawn>(name);
        pawn->SetName(name);
        pawn->SetRect({ 400.0f, 300.0f }, { 100.0f,100.0f });
        world.m_ActorList.insert(
            std::make_pair(name, pawn));
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"ACharacer";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto character = std::make_shared<ACharacter>(name);
        character->SetName(name);
        character->SetRect({ 400.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.insert(
            std::make_pair(name, character));
    }
    for (auto& p :  world.m_ActorList)
    {
        p.second->Tick();
        p.second->Move(10.0f, 10.0f);
        p.second->Show();
    }   

    std::wcout << UActorComponent::GetNumInstance() << std::endl;    
    // 게임생성
    using CompPtr = std::shared_ptr<UActorComponent>;
    std::list< CompPtr> compList;
    compList.push_back(std::make_shared<UTimerComponent>(L"GameTimer"));
    auto timer = std::dynamic_pointer_cast<UTimerComponent>(compList.back());
    
    compList.push_back(std::make_shared<UInputComponent>(L"GameInput"));    
    auto input = std::dynamic_pointer_cast<UInputComponent>(compList.back());

    compList.push_back(std::make_shared <USoundComponent>(L"GameSound"));

    if (timer == nullptr)
    {        
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
            (*pNode)->TickComponent();
        }       
        if (GameLoop(input.get()))
        {
            break;
        }        
    }
    std::wcout << timer->GetGameGlobalTimer() << std::endl;
   
    compList.clear();
    world.m_ActorList.clear();

    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
