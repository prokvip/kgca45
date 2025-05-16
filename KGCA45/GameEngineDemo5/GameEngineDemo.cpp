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

void Fun(std::shared_ptr<AActor> cpy)
{
    std::wcout << cpy->GetName();
}

void FunRef(std::shared_ptr<AActor>& cpy)
{
    std::wcout << cpy->GetName();
}

void SmartPoint_sharedptr_Test()
{
    // SmartPoint
    {
        std::shared_ptr<AActor> data1 = std::make_shared<AActor>();
        data1->SetName(L"aa"); // _Ptr->SetName(..);
        {
            std::shared_ptr<AActor> data2 = data1;
            data2->SetName(L"bb");
        }
    }
    {
        std::shared_ptr<AActor> data1 = std::make_shared<AActor>();
        data1->SetName(L"aa"); // _Ptr->SetName(..);
        Fun(data1);
        FunRef(data1);
        {
            std::shared_ptr<AActor> data2 = data1;
            data2->SetName(L"bb");
        }
    }
    {
        std::shared_ptr<AActor> data1{ new AActor() };
        AActor* newdata1 = new AActor();
        std::shared_ptr<AActor> data3{ newdata1 };
        {
            // (주의1)한개의 포인터가 삭제되면 나머지는 에러가 발생한다.
            //std::shared_ptr<AActor> data4(newdata1);
        }

        std::shared_ptr<AActor> data5;
        AActor* newdata2 = new AActor();
        data5.reset(newdata2);
        AActor* newdata3 = new AActor();
        data5.reset(newdata3);
    }
    {
        std::shared_ptr<AActor> data1 = std::make_shared<AActor>();
        data1->SetName(L"aa"); // _Ptr->SetName(..);
        AActor* pData1 = data1.get();
        // (주의2)
        //delete pData1; // data1 소멸시 에러발생한다.
        std::wcout << data1->GetName(); // 연산자 재정의 ->
        std::wcout << pData1->GetName();// 직접포인터 호출
    }
    {
        using SharedActor = std::shared_ptr<AActor>;
        SharedActor data1 = std::make_shared<AActor>();
        data1->SetName(L"aa");
        auto data2 = std::make_shared<AActor>();
        data2->SetName(L"bb");
    }
}

void FunUniquePtr(std::unique_ptr<AActor> cpy)
{
    std::wcout << cpy->GetName();
}

void FunUniquePtrRef(std::unique_ptr<AActor>& cpy)
{
    std::wcout << cpy->GetName();
}
void SmartPoint_uniqueptr_Test()
{
    //unique_ptr(const unique_ptr&) = delete;
    //unique_ptr& operator=(const unique_ptr&) = delete;
    // SmartPoint
    {
        std::unique_ptr<AActor> data1 = std::make_unique<AActor>();
        data1->SetName(L"aa"); // _Ptr->SetName(..);
        {
            //std::unique_ptr<AActor> data2 = data1;// 에러
            //data2->SetName(L"bb");
        }
    }
    {
        std::unique_ptr<AActor> data1 = std::make_unique<AActor>();
        data1->SetName(L"aa"); // _Ptr->SetName(..);
        //FunUniquePtr(data1); 복사생성자 삭제되어 에러발생
        FunUniquePtrRef(data1);
        {
            //std::unique_ptr<AActor> data2 = data1; // 에러
            //data2->SetName(L"bb");
        }
    }
    {
        std::unique_ptr<AActor> data1{ new AActor() };
        AActor* newdata1 = new AActor();
        std::unique_ptr<AActor> data3{ newdata1 };
        {
            // (주의1)한개의 포인터가 삭제되면 나머지는 에러가 발생한다.
            //std::unique_ptr<AActor> data4(newdata1);
        }

        std::unique_ptr<AActor> data5;
        AActor* newdata2 = new AActor();
        data5.reset(newdata2);
        AActor* newdata3 = new AActor();
        data5.reset(newdata3);
    }
    {
        std::unique_ptr<AActor> data1 = std::make_unique<AActor>();
        data1->SetName(L"aa"); // _Ptr->SetName(..);
        AActor* pData1 = data1.get();
        // (주의2)
        //delete pData1; // data1 소멸시 에러발생한다.
        std::wcout << data1->GetName(); // 연산자 재정의 ->
        std::wcout << pData1->GetName();// 직접포인터 호출
    }
    {
        using UniqueActor = std::unique_ptr<AActor>;
        UniqueActor data1 = std::make_unique<AActor>();
        data1->SetName(L"aa");
        auto data2 = std::make_shared<AActor>();
        data2->SetName(L"bb");
    }

    // 소유권 이전
    std::unique_ptr<AActor> data1 = std::make_unique<AActor>();
    data1->SetName(L"aa"); // _Ptr->SetName(..);
    if (data1 != nullptr)
    {
        std::wcout << data1->GetName();
    }
    std::unique_ptr<AActor> data2 = std::move(data1);
    if (data1 != nullptr)
    {
        std::wcout << data1->GetName();
    }
    if (data2 != nullptr)
    {
        std::wcout << data2->GetName();
    }
}
void SmartPoint_weakptr_Test()
{
    // 1)weak_ptr 직접접근 불가능하기 때문에 멤버변수, 멤버함수의 사용이 불가능하다.
    // 2)유일한 사용방법은 lock()를 통하여 shared_ptr반환 받아 사용한다.
    // 3)사용이유
    //   -shared_ptr 순환참조(사이클)발생하면  
    //    참조카운터가 0이 되지 못하여 객체가 소멸되지 않는다.
    //    이를 보완하기 위해서 등장했다.    
    class B;
    class A
    {
    public:
        //std::shared_ptr<B> data1;
        std::weak_ptr<B> data1;
        ~A() {
            // 순환참조가 발생하면 호출되지 않는다.
            std::wcout << std::endl;
            if (!data1.expired())// 존재유무 점검
            {
                try
                {
                    auto p = data1.lock(); //shared_ptr
                    if (p != nullptr)
                    {
                        std::wcout << p.use_count() << std::endl;
                    }
                }
                catch (std::bad_weak_ptr b)
                {
                    std::wcout << L"nullptr" << std::endl;
                }
                
            }
        }
    };
    class B
    {
    public:
        std::shared_ptr<A> data1;
        ~B() {
            // 순환참조가 발생하면 호출되지 않는다.
            std::wcout << std::endl;
            std::wcout << data1.use_count() << std::endl;
        }
    };

    
    {        
        std::shared_ptr<A> a;
        std::shared_ptr<B> b;
        a = std::make_shared<A>();        
        b = std::make_shared<B>();
        a->data1 = b;
        b->data1 = a; // 순환참조(사이클) 발생                
        std::wcout << std::endl;
        std::wcout << a.use_count() << std::endl;
        std::wcout << b.use_count() << std::endl;
    }

    {
        //std::weak_ptr<int> weak1 = 
            
    }
}
int main()
{    
    SmartPoint_sharedptr_Test();
    SmartPoint_uniqueptr_Test();
    SmartPoint_weakptr_Test();

    UWorld world;
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"AActor";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto actor = std::make_shared<AActor>(name);
        actor->SetRect({ 0.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.push_back(actor);
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"APawn";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto pawn = std::make_shared<APawn>(name);
        pawn->SetName(name);
        pawn->SetRect({ 400.0f, 300.0f }, { 100.0f,100.0f });
        //auto actor = dynamic_cast<AActor*>(pawn.get());
        //auto actor = std::dynamic_pointer_cast<AActor>(pawn);
        world.m_ActorList.push_back(pawn);
    }
    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"ACharacer";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto character = std::make_shared<ACharacter>(name);
        character->SetName(name);
        character->SetRect({ 400.0f, 0.0f }, { 100.0f,100.0f });
        world.m_ActorList.push_back(character);
    }
    for (int i = 0; i < world.m_ActorList.size(); i++)
    {
        AActor* actor = world.m_ActorList[i].get();// 인덱싱 지원
        actor->Show();
    }
    for (int i = 0; i < world.m_ActorList.size(); i++)
    {
        auto actor = world.m_ActorList[i];// 인덱싱 지원
        actor->Move(10.0f, 10.0f);
        actor->Show();
    }
    for (int i = 0; i < world.m_ActorList.size(); i++)
    {
        auto actor = world.m_ActorList[i];// 인덱싱 지원
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
    using CompPtr = std::shared_ptr<UActorComponent>;
    std::list< CompPtr> compList;
    compList.push_back(std::make_shared<UTimerComponent>(L"GameTimer"));
    //UTimerComponent* timer = dynamic_cast<UTimerComponent*>(compList.back().get());
    auto timer = std::dynamic_pointer_cast<UTimerComponent>(compList.back());
    
    compList.push_back(std::make_shared<UInputComponent>(L"GameInput"));    
    //UInputComponent* input = dynamic_cast<UInputComponent*>(compList.back());
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
            //UActorComponent* actorComp = *pNode;
            (*pNode)->TickComponent();
        }       
        if (GameLoop(input.get()))
        {
            break;
        }
        //std::wcout << timer->GetGameGlobalTimer() << std::endl;
    }
    std::wcout << timer->GetGameGlobalTimer() << std::endl;
    
    // 게임 종료
   /* for (auto pActor : world.m_ActorList)
    {
        delete pActor;
    }*/
    //for (UActorComponent* pNode : compList)
    //{
    //    delete pNode;
    //}
    compList.clear();
    world.m_ActorList.clear();

    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
