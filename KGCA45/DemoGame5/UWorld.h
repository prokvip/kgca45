#pragma once
#include "ATimerEffect.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
using sharedActor	= std::shared_ptr<AActor>;
using TArray		= std::vector<sharedActor>;
// stl::map<key, value> list;
using TMap			= std::map<std::wstring, sharedActor>;

class ANpcCharacter;
class APlayerCharacter;

class UWorld : public UObject
{
public:
	using CompPtr = std::shared_ptr<UActorComponent>;
	std::list< CompPtr>					m_CompList;
	static std::shared_ptr<UTimerComponent>	m_Timer;
	static std::shared_ptr<UInputComponent>	m_Input;

	static std::vector<TTexture> g_listA;
	static std::vector<TTexture> g_listB;
	std::shared_ptr<APlayerCharacter> m_pPlayer = nullptr;
	TMap			m_ActorList;
	TArray			m_EffectList;
	void			Tick();
	void			AddEffect(TVector2 pos);
	void			Render();
};

