//#pragma optimize("", on))
///Zc:nrvo- 
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

/// <summary>
/// https://devblogs.microsoft.com/cppblog/improving-copy-and-move-elision/
/// visual studio 2022 버전 17.4 이후 부터 적용 복사/이동 생략 기능이 추가되어 있음
/// /Zc:nrvo는 명명된 반환 값 최적화(NRVO, Named Return Value Optimization)를  제어하는 Visual Studio 컴파일러 옵션이다. 
/// NRVO는 C++에서 반환되는 객체의 불필요한 복사 및 이동을 제거하여 성능을 최적화하는 기술임.
/// 해제 : /Zc:nrvo-
/// </summary>
/// <returns></returns>
class AObject {
public:
    AObject() {
        this->name = L"Default";
        pData = new int;
        *pData = 3;
        std::wcout << L"This is " << name << L" constructor." << std::endl;
    }
    AObject(const std::wstring& name) {
        this->name = name;        
        pData = new int;
        *pData = 3;
        std::wcout << L"This is " << name << L" constructor." << std::endl;
    }
    ~AObject() {
        delete pData;
        pData = nullptr;
        std::wcout << L"This is " << this->name << " desstructor." << std::endl;
    }
    // lhs(Left Hand Side) / rhs(Right Hand Side) 
    //AObject(const AObject& rhs) //= delete;
    //{
    //    this->name = rhs.name;
    //    if (pData != nullptr)
    //    {
    //        delete pData;
    //        pData = nullptr;
    //    }
    //    pData = new int;
    //    *pData = *rhs.pData;
    //    std::wcout << L"This is " << rhs.name << L" copy constructor." << std::endl;
    //}
    //AObject& operator=(const AObject& rhs)// = delete;
    //{
    //    this->name = rhs.name;
    //    if (pData != nullptr)
    //    {
    //        delete pData;
    //        pData = nullptr;
    //    }
    //    pData = new int;
    //    *pData = *rhs.pData;
    //    std::wcout << L"This is " << this->name << L" copy operator." << std::endl;
    //    return *this;
    //}
    //noexcept : 예외를 던지지 않는다.
    AObject( AObject&& rhs) noexcept : name(rhs.name), pData(rhs.pData)
    {        
        //this->name = rhs.name;       
        pData = rhs.pData;
        rhs.pData = nullptr;
        std::wcout << L"This is " << rhs.name << L" move constructor." << std::endl;
    }
    AObject& operator=( AObject&& rhs) noexcept
    {
        if (this != &rhs)
        {
            this->name = rhs.name;
            if (pData != nullptr)
            {
                delete pData;
                this->pData = rhs.pData;
                rhs.pData = nullptr;
            }
            pData = new int;
            *pData = *rhs.pData;            
        }
        std::wcout << L"This is " << this->name << L" move = operator." << std::endl;
        return *this;
    }
    std::wstring name;
    int* pData = nullptr;
};
//NRVO
AObject NewObject()
{
    AObject aa(L"aa1");
    return aa;
}
AObject&& NewObjectRVOMove()
{    
    return std::move(AObject());
}
AObject&& NewObjectNRVOMove()
{
    AObject aa;
    return std::move(aa);
}
//NRVO에 대한 제한 사항(반환 슬롯)
//복사 생략은 반환 슬롯에 반환될 객체를 생성한다. 
//하지만 WhichShouldIReturn함수는 두 경로 모두에 대해 복사 생략을 수행할 방법은 없다.
AObject WhichShouldIReturn(bool condition)
{
    AObject resultA(L"aa4");
    if (condition) {
        AObject resultB(L"bb4");
        return resultB;
    }
    return resultA;
}
//NRVO
AObject MakeObjectNRVO(const std::wstring& name) 
{
    AObject obj(name);
    return obj;
}

//RVO
AObject MakeObjectRVO(const std::wstring& name) 
{
    return AObject(name);
}

struct Copyable
{
    int val;
};
struct NotCopyable
{
    NotCopyable(const NotCopyable&) = delete;
    int val;
};

int main()
{     
    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    std::cout << "is_copy_constructible<Copyable> == " << std::boolalpha     << std::is_copy_constructible<Copyable>::value << std::endl;
    std::cout << "is_copy_constructible<NotCopyable> == " << std::boolalpha  << std::is_copy_constructible<NotCopyable>::value << std::endl;

    // 복사생성자의 생성이 불가능하면 어설션이 발생한다.
    static_assert(!std::is_copy_constructible<AObject>::value, "is not copy constructible");
    static_assert(!std::is_copy_assignable<AObject>::value, "is not copy assignable");
    static_assert(std::is_move_constructible<AObject>::value, "is move constructible");
    static_assert(std::is_move_assignable<AObject>::value, "is move assignable");

    AObject moveable{};
    AObject moved{ std::move(moveable) };
    AObject moved_again{ std::move(moved) };
    //AObject moved_againFun = NewObjectRVOMove(); // 해제자 호출. 주의

    {
        auto nrvo = MakeObjectNRVO(L"NRVO");
        auto rvo = MakeObjectRVO(L"RVO");
        std::wcout << nrvo.name << std::endl;
        std::wcout << rvo.name << std::endl;
    }

    {
        AActor a;       // 기본생성자 호출    
        AActor b = a;   // 복사생성자 호출
        AActor c;       // 기본생성자 호출
        c = a;          // 대입연산자 호출      
    }
    std::wcout << std::endl;
    // 임시 객체는 이동 생성자로 newObj에서 사용되고 NewObject()함수의 aa 지역객체는 소멸한다.
    std::wcout << L"newobj0 " << std::endl;
    AObject     newobj0     = NewObject(); std::wcout << newobj0.name << std::endl;
   
    std::wcout << L"newobj1 " << std::endl;
    AObject&&   newobj1     = NewObject(); std::wcout << newobj1.name << std::endl;
    
    std::wcout << L"newobj2 " << std::endl;
    AObject&&    newobj2     = NewObjectRVOMove();  std::wcout << newobj2.name << std::endl;
    
    std::wcout << L"newobj3 " << std::endl;
    AObject     newobj3     = NewObjectNRVOMove(); std::wcout << newobj3.name << std::endl;
    
    std::wcout << L"newobj4 " << std::endl;
    AObject&&   newobj4     = NewObjectNRVOMove(); std::wcout << newobj4.name << std::endl;
    newobj2.name = L"aaa1"; // empty
    newobj3.name = L"aaa2"; // empty
    //newobj4.name = L"aa"; // error

    std::wcout << L"newobj5 " << std::endl;
    AObject     newobj5     = WhichShouldIReturn(true);
    std::wcout << newobj5.name << std::endl;

    
    ///////////////////////////////////////////////////////////////////////////////
    // 개체 수명 및 리소스 관리 자동화, 누수방지, 안전성 확보를 RAII라 한다.
    // RAII패턴은 다음 기능을 가져야 한다.  1, 생성자, 소멸자, 필요한 메서드    
    // RAII(Resource acquisition is initialization) : 리소스 획득은 초기화이다.
    // 
    // 최신 C++는 스택에 개체를 선언하여 힙 메모리를 최대한 사용하지 않도록 방지합니다.
    // 리소스가 스택에 비해 너무 크면 개체가 소유해야 합니다.개체가 초기화되면 소유하는 리소스를 획득합니다.
    // 그런 다음, 개체는 소멸자에서 리소스를 해제합니다.소유 개체 자체는 스택에 선언됩니다.
    // 개체가 리소스를 소유한다는 원칙을 "리소스 획득은 초기화입니다" 또는 RAII라고도 합니다.
    // 리소스 소유 스택 개체가 범위를 벗어나면 소멸자가 자동으로 호출됩니다.
    // 이러한 방식으로 C++의 가비지 수집은 개체 수명과 밀접한 관련이 있으며 리소스는 안전하게 해제된다.


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
        auto actor = world.m_ActorList[i];// 인덱싱 지원
        actor->Tick();
        actor->Move(10.0f, 10.0f);
        actor->Show();
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
