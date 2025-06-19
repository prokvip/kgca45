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
	static  void   Update();
	// ���� ���ϴ����� 1��	
	FMOD::Sound*	m_pSound	= nullptr;	// ���� ��ü
	// �÷��� ����(����Ǿ� ��ȯ��.)�� 1���� ��ȯ�ȴ�.
	FMOD::Channel*	m_pChannel	= nullptr; // ä�� ��ü
	
	virtual bool   Load(TString filename);
	virtual bool   Play(bool loop = false); // ���� ���
	virtual bool   PlayEffect(bool loop = false);
	virtual void   Release();
public:
	TSound(TString path);
	TSound();
	~TSound();
};

