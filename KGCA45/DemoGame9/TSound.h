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
	static  void   Update();
	// 사운드 파일단위로 1개	
	FMOD::Sound*	m_pSound	= nullptr;	// 사운드 객체
	// 플레이 단위(실행되야 반환됨.)로 1개가 반환된다.
	FMOD::Channel*	m_pChannel	= nullptr; // 채널 객체
	
	virtual bool   Load(TString filename);
	virtual bool   Play(bool loop = false); // 사운드 재생
	virtual bool   PlayEffect(bool loop = false);
	virtual void   Release();
public:
	TSound(TString path);
	TSound();
	~TSound();
};

