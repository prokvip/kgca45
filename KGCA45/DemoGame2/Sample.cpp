#include "Sample.h"
void Sample::GameRun()
{
    //TWindow::GameRun();
    // 게임로직
    //while (timer->GetGameGlobalTimer() < 60.0f)
    {
        for (auto pNode = compList.begin();
            pNode != compList.end();
            pNode++)
        {
            (*pNode)->TickComponent();
        }
        if (GameLoop(input.get()))
        {  
        }
    }
	
}
void Sample::InitGame()
{
    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    for (int i = 0; i < 3; i++)
    {
        std::wstring name = L"AActor";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto actor = std::make_shared<AActor>(name);
        actor->SetRect({ 0.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.insert(std::make_pair(name, actor));
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"APawn";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto pawn = std::make_shared<APawn>(name);
        pawn->SetName(name);
        pawn->SetRect({ 400.0f, 300.0f }, { 100.0f,100.0f });
        world.m_ActorList.insert(std::make_pair(name, pawn));
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"ACharacer";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto character = std::make_shared<ACharacter>(name);
        character->SetName(name);
        character->SetRect({ 400.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.insert( std::make_pair(name, character));
    }
    for (auto& p : world.m_ActorList)
    {
        p.second->Tick();
        p.second->Move(10.0f, 10.0f);
        p.second->Show();
    }

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    // 게임생성
    using CompPtr = std::shared_ptr<UActorComponent>;
    compList.push_back(std::make_shared<UTimerComponent>(L"GameTimer"));
    timer = std::dynamic_pointer_cast<UTimerComponent>(compList.back());

    compList.push_back(std::make_shared<UInputComponent>(L"GameInput"));
    input = std::dynamic_pointer_cast<UInputComponent>(compList.back());

    compList.push_back(std::make_shared <USoundComponent>(L"GameSound"));

    if (timer == nullptr)
    {
        compList.clear();
        return;
    }
}
bool Sample::GameLoop(UInputComponent* input)
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
void Sample::ReleaseGame()
{
    std::wcout << timer->GetGameGlobalTimer() << std::endl;

    compList.clear();
    world.m_ActorList.clear();

    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}