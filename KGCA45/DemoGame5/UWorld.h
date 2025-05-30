#pragma once
#include "TTimerEffect.h"

using sharedActor	= std::shared_ptr<AActor>;
using TArray		= std::vector<sharedActor>;
// stl::map<key, value> list;
using TMap			= std::map<std::wstring, sharedActor>;

class UWorld : public UObject
{
public:
	static std::vector<TTexture> g_listA;
	static std::vector<TTexture> g_listB;
	std::shared_ptr<UPlayer> m_pPlayer = nullptr;
	TMap			m_ActorList;
	TArray			m_EffectList;
	void			Tick();
	void			AddEffect(TVector2 pos);
	void			Render();
};

