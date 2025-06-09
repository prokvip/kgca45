#pragma once
#include "ATimerEffect.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
using sharedActor	= std::shared_ptr<AActor>;
using TArray		= std::vector<sharedActor>;
using TMap			= std::map<std::wstring, sharedActor>;

class ANpcCharacter;
class APlayerCharacter;

using RECT_ARRAY = std::vector<RECT>;
struct TSprite
{
	enum { UV_Animation=0, TEX_Animation};
	TString 	m_Name;
	UINT		m_iNumFrame;
	int			m_iType = UV_Animation; 	
	TString     m_szTextureFilePath; 
	TString     m_szMaskTextureFilePath; 
	TString     m_szShaderFilePath; 
	std::vector<RECT>			m_uvArray;
	std::vector<TString>		m_texArray;

};
class UWorld : public UObject
{
public:
	using CompPtr = std::shared_ptr<UActorComponent>;
	std::list< CompPtr>					m_CompList;
	static std::shared_ptr<UTimerComponent>	m_Timer;
	static std::shared_ptr<UInputComponent>	m_Input;
	static std::vector<TSprite>  g_Sprite; 
	static std::vector<TTexture> g_listA;
	static std::vector<TTexture> g_listB;
	std::shared_ptr<APlayerCharacter> m_pPlayer = nullptr;
	TMap			m_ActorList;
	TArray			m_EffectList;
public:
	bool			GameDataLoad(TString path);
	void			Init();
	void			Tick();
	void			AddEffect(TVector2 pos);
	void			Render();
};

