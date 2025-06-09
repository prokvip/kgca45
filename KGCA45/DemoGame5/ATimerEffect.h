#pragma once
#include "AActor.h"

class ATimerEffect :  public AActor
{
public:
	float					m_fStep = 1.0f;
	std::vector<TTexture>	m_texlist;
	UINT					m_iCurrentIndex=0;
	float					m_Timer= 0.0f;
	UINT				    m_iSecond =0;
	TVector2					m_pInitPos;
	TVector2					m_pInitSize;
	std::vector<std::shared_ptr<URenderComponent>> m_SecondObj;
public:
	void    SetTextureList(std::vector< TTexture>& list);
	virtual	bool     Create(
		TVector2 pos,
		TVector2 size,
		TString texfilepath,
		TString shaderfilepath) override;
	virtual void   Tick()override;
	virtual void   Render() override;
public:
	ATimerEffect(std::wstring name) : AActor(name) {}
	ATimerEffect() {};
	~ATimerEffect() {};
};

class AEffect : public ATimerEffect
{
public:
	virtual void   Tick()override;
	virtual void   Render() override;
};