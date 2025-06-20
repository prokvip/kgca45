#pragma once
// 환경설정: FMOD SDK가 설치된 경로를 추가해야 합니다.
// Visual Studio에서 프로젝트 속성 -> C/C++ -> 일반 -> 추가 포함 디렉터리 에 FMOD SDK의 include 폴더 경로를 추가합니다.
// 또한, 링커 설정에서 라이브러리 디렉터리도 FMOD SDK의 lib 폴더 경로를 추가해야 합니다.	
#include "UObject.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib") // fmod.dll 로딩한다.
using namespace FMOD;

class TSound : public UObject
{
public:
	static FMOD::System*	m_pSystem;	// FMOD 시스템 객체
	static  void   UpdateSystem();
	static  void   ReleaseSystem();
	// 사운드 파일단위로 1개	
	FMOD::Sound*	m_pSound	= nullptr;	// 사운드 객체
	// 플레이 단위(실행되야 반환됨.)로 1개가 반환된다.
	FMOD::Channel*	m_pChannel	= nullptr; // 채널 객체
	float			m_fVolume = 0.5f; // 볼륨 (0.0f ~ 1.0f)
	unsigned int	m_msSoundLength=0;
	unsigned int	m_msPosition = 0;
public:
	virtual void   Update();
	virtual bool   Load(TString filename);
	virtual bool   Play(bool loop = false); // 사운드 재생
	virtual bool   PlayEffect();
	virtual void   Stop(); // 사운드 정지
	virtual void   PauseToggle(); // 사운드 일시정지 토글 (재생중이면 일시정지, 일시정지 상태면 재개)
	virtual void   Pause(); // 사운드 일시정지
	virtual void   Resume(); // 사운드 재개
	virtual bool   IsPlaying(); // 사운드가 재생중인지 확인
	virtual bool   IsPaused(); // 사운드가 일시정지 상태인지 확인
	virtual bool   IsStopped(); // 사운드가 정지 상태인지 확인
	virtual bool   IsValid(); // 사운드가 유효한지 확인
	virtual void   SetVolume(float volume); // 볼륨 설정 (0.0f ~ 1.0f)
	virtual float  GetVolume(); // 현재 볼륨 반환 (0.0f ~ 1.0f)
	virtual void   SetVolumeUp(); // 볼륨을 0.1f 증가시킴 (최대 1.0f)
	virtual void   SetVolumeDown(); // 볼륨을 0.1f 감소시킴 (최소 0.0f)
	virtual void   Release();
public:
	TSound(TString path);
	TSound();
	~TSound();
};

