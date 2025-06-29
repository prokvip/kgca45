#pragma once
#include "APawn.h"
class ASprite : public APawn
{
public:
	float					m_fStep = 1.0f;
	std::vector<TTexture>	m_texlist;
	std::vector<TVector4>	m_uvlist;
	UINT					m_iCurrentIndex = 0;
	float					m_fTimer = 0.0f;
	UINT				    m_iSecond = 0;
public:
	void    SetTextureList(std::vector<TTexture>& list);
	virtual	bool     Create(
		TVector2 pos,
		TVector2 size,
		TString texfilepath,  // alpha 포함 텍스처
		TString shaderfilepath) override;
	virtual bool    Create(
		TVector2 pos,
		TVector2 size,
		TString texfilepath,    
		TString texMaskfilepath, // mask 사용
		TString shaderfilepath);
	virtual void   Tick()override;
	virtual void   Render() override;
public:
	ASprite(std::wstring name) : APawn(name) {}
	ASprite() {};
	virtual ~ASprite() {
		m_texlist.clear();
		m_uvlist.clear();
	};
};


class AEffectTex : public ASprite
{
public:
	virtual void   Render() override;
};

class AEffectUV : public ASprite
{
public:
	virtual void   Render() override;
};

class ATimerEffect : public APawn
{
public:
	float					m_fStep = 1.0f;
	UINT					m_iCurrentIndex = 0;
	float					m_fTimer = 0.0f;
	UINT				    m_iSecond = 0;	
	ASprite*				m_pSprite = nullptr;
public:
	virtual void   Tick()override;
	virtual void   Render() override;
	virtual void   SetSprite(ASprite* sprite) { m_pSprite = sprite; }
public:
	ATimerEffect(std::wstring name) : APawn(name) {}
	ATimerEffect() {};
	virtual ~ATimerEffect() {};
};