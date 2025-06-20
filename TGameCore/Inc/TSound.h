#pragma once
// ȯ�漳��: FMOD SDK�� ��ġ�� ��θ� �߰��ؾ� �մϴ�.
// Visual Studio���� ������Ʈ �Ӽ� -> C/C++ -> �Ϲ� -> �߰� ���� ���͸� �� FMOD SDK�� include ���� ��θ� �߰��մϴ�.
// ����, ��Ŀ �������� ���̺귯�� ���͸��� FMOD SDK�� lib ���� ��θ� �߰��ؾ� �մϴ�.	
#include "UObject.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib") // fmod.dll �ε��Ѵ�.
using namespace FMOD;

class TSound : public UObject
{
public:
	static FMOD::System*	m_pSystem;	// FMOD �ý��� ��ü
	static  void   UpdateSystem();
	static  void   ReleaseSystem();
	// ���� ���ϴ����� 1��	
	FMOD::Sound*	m_pSound	= nullptr;	// ���� ��ü
	// �÷��� ����(����Ǿ� ��ȯ��.)�� 1���� ��ȯ�ȴ�.
	FMOD::Channel*	m_pChannel	= nullptr; // ä�� ��ü
	float			m_fVolume = 0.5f; // ���� (0.0f ~ 1.0f)
	unsigned int	m_msSoundLength=0;
	unsigned int	m_msPosition = 0;
public:
	virtual void   Update();
	virtual bool   Load(TString filename);
	virtual bool   Play(bool loop = false); // ���� ���
	virtual bool   PlayEffect();
	virtual void   Stop(); // ���� ����
	virtual void   PauseToggle(); // ���� �Ͻ����� ��� (������̸� �Ͻ�����, �Ͻ����� ���¸� �簳)
	virtual void   Pause(); // ���� �Ͻ�����
	virtual void   Resume(); // ���� �簳
	virtual bool   IsPlaying(); // ���尡 ��������� Ȯ��
	virtual bool   IsPaused(); // ���尡 �Ͻ����� �������� Ȯ��
	virtual bool   IsStopped(); // ���尡 ���� �������� Ȯ��
	virtual bool   IsValid(); // ���尡 ��ȿ���� Ȯ��
	virtual void   SetVolume(float volume); // ���� ���� (0.0f ~ 1.0f)
	virtual float  GetVolume(); // ���� ���� ��ȯ (0.0f ~ 1.0f)
	virtual void   SetVolumeUp(); // ������ 0.1f ������Ŵ (�ִ� 1.0f)
	virtual void   SetVolumeDown(); // ������ 0.1f ���ҽ�Ŵ (�ּ� 0.0f)
	virtual void   Release();
public:
	TSound(TString path);
	TSound();
	~TSound();
};

