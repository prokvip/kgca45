#pragma once
#include "UWorld.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TTimerEffect.h"

//1)DirectXTK �ٿ�ε� �� ������
//2)bin->������� DirectXTK.lib
//3)inc-> ��ü�� �����ؼ� 
//4)����������Ʈ�� ../../DirectXTK ���� ����, ���ο� lib���� ���� �� �����Ѵ�.
//5)���� ���丮�� inc���� ���� �� �����ؼ� �ִ´�.
//6)�ش� ������Ʈ�� �Ӽ�->C++->�߰����Ե��丮(../../DirectXTK/Inc;)
//7)�ش� ������Ʈ�� �Ӽ�->��Ŀ>�߰����̺귯�����丮(../../DirectXTK/lib;)
class Sample :  public TWindow
{
	TDevice m_dxDevice;
	using CompPtr = std::shared_ptr<UActorComponent>;
	UWorld								m_World;
	std::list< CompPtr>					m_CompList;
	std::shared_ptr<UTimerComponent>	m_Timer = nullptr;
	std::shared_ptr<UInputComponent>	m_Input = nullptr;
	std::shared_ptr<UBackground>		m_Player = nullptr;
	std::shared_ptr<UBackground>		m_MapObj = nullptr;
	TTimerEffect						m_TimerObj;
	UBackground							m_EffectObj;
public:
	void InitGame();
	void ReleaseGame();
	bool GameLoop();
public:
	virtual void GameRun() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

