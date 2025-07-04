#pragma once
#include "AActor.h"
#include "TAssetManager.h"
#include "TTexture.h"
#include "TShader.h"
#include "TSprite.h"
#include "TSound.h"

class UActorComponent;
class UInputComponent;
class UTimerComponent;
class USoundComponent;

using RECT_ARRAY = std::vector<RECT>;
struct TSpriteInfo
{
	enum { UV_Animation = 0, TEX_Animation };
	TString 	m_Name;
	UINT		m_iNumFrame;
	int			m_iType = UV_Animation;
	TString     m_szTextureFilePath;
	TString     m_szMaskTextureFilePath;
	TString     m_szShaderFilePath;
	std::vector<RECT>			m_uvArray;
	std::vector<TString>		m_texArray;	
};

class TEngine
{
public:
	using CompPtr = std::shared_ptr<UActorComponent>;
	std::list< CompPtr>					m_CompList;
public:
	static TAssetManager<TTexture>			gTexManager;
	static TAssetManager<TShader>			gShaderManager;	
	static TAssetManager<ASprite>			gSpriteManager;
	static TAssetManager<TSound>			gSoundManager;
	static std::shared_ptr<UTimerComponent>	gTimer;
	static std::shared_ptr<UInputComponent>	gInput;
	static std::vector<TSpriteInfo>			g_Sprite;

	static ComPtr<ID3D11BlendState> m_AlphaBlendState;
	static ComPtr<ID3D11BlendState> m_AddBlendState;
	static ComPtr<ID3D11BlendState> m_SubtrackBlendState;
	static ComPtr<ID3D11BlendState> m_RevSubtrackBlendState;
	static ComPtr<ID3D11BlendState> m_MultiplyBlendState;
	static ComPtr<ID3D11BlendState> m_DualSourceBlendState;
public:
	bool  CreateBlendState();
	void  Init();
	void  Tick();
	void  Release();
	bool  GameDataLoad(TString path);
	TEngine() {};
	virtual ~TEngine();
};

