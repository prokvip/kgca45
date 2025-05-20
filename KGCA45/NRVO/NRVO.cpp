#include <iostream>
/// <summary>
/// "/Zc:nrvo-" 속성->c++->명령줄에 추가
/// </summary>
class AObject
{
    // 멤버변수가 없으면 작동 불가
    // 단, 복사생성자 있으면 가능.(복사할당연산자는 제외)
    // 단, 이동생성자 있으면 가능.(이동할당연산자는 제외)
    
public:
    std::wstring name;
    int* pData = nullptr;
    void operator= ( AObject&& src)
    {
        if (this != &src)
        {
            name = src.name;
            pData = src.pData;

            src.name.clear();
            src.pData = nullptr;
        }
        std::wcout << L"Move = Constructor!" << std::endl;
    }
    // 이동생성자
    // lhs(left hand side)
    // rhs(right hand side)
    AObject(AObject&& rhs)
    {
        name = rhs.name;
        pData = rhs.pData;

        rhs.name.clear();
        rhs.pData = nullptr;
        std::wcout << L"Move Constructor!" << std::endl;
    }
    // 복사할당연산자
   /* void operator= (const AObject& rhs)
    {
        std::wcout << L"Default Copy Constructor!" << std::endl;
    }  */  
    // 복사생성자
    /*AObject(const AObject& rhs)
    {
        name = src.name;
        std::wcout << L"Default Copy Constructor!" << std::endl;
    }  */  
    AObject() { 
        name = L"kgca";
        pData = new int;
        *pData = 3;
        std::wcout << L"Default Constructor!" << std::endl; }
    ~AObject() {
        delete pData;
        pData = nullptr;
        std::wcout << L"Default desstructor!" << std::endl;
    }
};
AObject MakeObjectMRVO()
{
    AObject obj;
    return obj;
}
AObject MakeObjectRVO()
{
    return AObject();
}
// 주의 : 복사 전에 삭제가 발생한다.
AObject&& MakeObjectMRVOMove()
{
    AObject obj;
    return std::move(obj);
}
// 주의 : 복사 전에 삭제가 발생한다.
AObject&& MakeObjectRVOMove()
{
    return std::move(AObject());
}
int main()
{
    AObject a1;
    a1.name = L"game";
    //a1 = std::move(a1);
    AObject a2{ std::move(a1) };    
    {
        AObject a3{};
        a1 = std::move(a3);        
    }

    std::cout << "MakeObjectMRVO!\n";
    auto objMRVO = MakeObjectMRVO();
    std::cout << "MakeObjectRVO!\n";
    auto objRVO  = MakeObjectRVO();
   

    auto objMove1 = MakeObjectMRVOMove();
    auto objMove2 = MakeObjectRVOMove();
    std::wcout << L"Default desstru";
}
