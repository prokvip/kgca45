#include "TEngine.h"
#include "TDevice.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
#include "UInputComponent.h"
TAssetManager<TTexture> TEngine::gTexManager;
TAssetManager<TShader>  TEngine::gShaderManager;
TAssetManager<ASprite>	TEngine::gSpriteManager;
std::shared_ptr<UTimerComponent>	 TEngine::gTimer = nullptr;
std::shared_ptr<UInputComponent>	 TEngine::gInput = nullptr;
std::vector<TSpriteInfo>  TEngine::g_Sprite;

bool    TEngine::GameDataLoad(TString path)
{
	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };
	TCHAR pTexturePath[256] = { 0 };
	TCHAR pMaskTexturePath[256] = { 0 };
	TCHAR pShaderPath[256] = { 0 };
	int iIsTexAnimation = 0;
	int iNumSprite = 0;

	FILE* fp_src;
	_wfopen_s(&fp_src, path.c_str(), L"rt");
	if (fp_src == NULL) return false;

	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%s"), pTemp, (unsigned int)_countof(pTemp));
	for (;;)
	{

		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d%d %s%s%s"),
			pTemp, (unsigned int)_countof(pTemp), &iNumFrame,
			&iIsTexAnimation,  // UV_Animation=0, TEX_CHANGE_Animation
			pTexturePath, (unsigned int)_countof(pTexturePath),
			pMaskTexturePath, (unsigned int)_countof(pMaskTexturePath),
			pShaderPath, (unsigned int)_countof(pShaderPath));

		TSpriteInfo sprite;
		sprite.m_Name = pTemp;
		sprite.m_iNumFrame = iNumFrame;
		sprite.m_iType = iIsTexAnimation;
		sprite.m_szTextureFilePath = pTexturePath;
		sprite.m_szMaskTextureFilePath = pMaskTexturePath;
		sprite.m_szShaderFilePath = pShaderPath;

		int iReadFrame = 0;
		if (iIsTexAnimation == TSpriteInfo::TEX_Animation)
		{
			sprite.m_texArray.resize(iNumFrame);
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp_src);
				_stscanf_s(pBuffer, _T("%d %s"),
					&iReadFrame,
					pTexturePath, (unsigned int)_countof(pTexturePath));
				sprite.m_texArray[iFrame] = pTexturePath;
			}
		}
		else //TSpriteInfo::UV_Animation
		{
			sprite.m_uvArray.resize(iNumFrame);
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp_src);
				_stscanf_s(pBuffer, _T("%d %d %d %d %d"),
					&iReadFrame,
					&sprite.m_uvArray[iFrame].left, &sprite.m_uvArray[iFrame].top,
					&sprite.m_uvArray[iFrame].right, &sprite.m_uvArray[iFrame].bottom);
			}
		}

		TString name = pTemp;
		if (name == L"#END")
		{
			break;
		}

		g_Sprite.emplace_back(sprite);
	}
	fclose(fp_src);
	return true;
}
void	TEngine::Init()
{
	GameDataLoad(L"../../data/script/SpriteInfo.txt");
	// 
	for (auto sprite : g_Sprite)
	{
		if (sprite.m_iType == TSpriteInfo::UV_Animation)
		{			
			TVector2 pos = { 0.0f, 0.0f };
			std::unique_ptr<ASprite> asset = std::make_unique<AEffectUV>();
			asset->SetName(sprite.m_Name);
			if (asset->Create(pos, { 50.0f,50.0f },
				sprite.m_szTextureFilePath,
				sprite.m_szShaderFilePath))
			{
				asset->m_fStep = 0.1f;
			}
			//auto texInfo = asset->m_pRenderComponent->m_TexDesc;
			for (auto& data : sprite.m_uvArray)
			{
				TVector4 uv;
				// p
				uv.x = (float)data.left ;	uv.y = (float)data.top;
				// s
				uv.z = (float)data.right;	uv.w = (float)data.bottom;
				asset->m_uvlist.emplace_back(uv);
			}
			gSpriteManager.AddAsset(sprite.m_Name, std::move(asset));
		}
		else if (sprite.m_iType == TSpriteInfo::TEX_Animation)
		{
			TVector2 pos = { 0.0f, 0.0f };
			std::unique_ptr<ASprite> asset = std::make_unique<AEffectTex>();
			asset->SetName(sprite.m_Name);
			asset->m_texlist.reserve(sprite.m_texArray.size());
			for (auto& tex : sprite.m_texArray)
			{
				asset->m_texlist.emplace_back(tex);
			}
			if (asset->Create(pos, { 50.0f,50.0f },
				sprite.m_szTextureFilePath,
				sprite.m_szShaderFilePath))
			{
				asset->m_fStep = 0.1f;				
			}			
			gSpriteManager.AddAsset(sprite.m_Name, std::move(asset));
		}
	}
	// 게임생성
	using CompPtr = std::shared_ptr<UActorComponent>;
	m_CompList.push_back(std::make_shared<UTimerComponent>(L"GameTimer"));
	gTimer = std::dynamic_pointer_cast<UTimerComponent>(m_CompList.back());

	m_CompList.push_back(std::make_shared<UInputComponent>(L"GameInput"));
	gInput = std::dynamic_pointer_cast<UInputComponent>(m_CompList.back());

	m_CompList.push_back(std::make_shared <USoundComponent>(L"GameSound"));

	if (gTimer == nullptr)
	{
		m_CompList.clear();
		return;
	}
}