#include "TEngine.h"
#include "TDevice.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
#include "UInputComponent.h"
TAssetManager<TTexture> TEngine::gTexManager;
TAssetManager<TShader>  TEngine::gShaderManager;
TAssetManager<ASprite>	TEngine::gSpriteManager;
TAssetManager<TSound>	TEngine::gSoundManager;

std::shared_ptr<UTimerComponent>	 TEngine::gTimer = nullptr;
std::shared_ptr<UInputComponent>	 TEngine::gInput = nullptr;
std::vector<TSpriteInfo>  TEngine::g_Sprite;

ComPtr<ID3D11BlendState> TEngine::m_AlphaBlendState;
ComPtr<ID3D11BlendState> TEngine::m_AddBlendState;
ComPtr<ID3D11BlendState> TEngine::m_SubtrackBlendState;
ComPtr<ID3D11BlendState> TEngine::m_RevSubtrackBlendState;
ComPtr<ID3D11BlendState> TEngine::m_MultiplyBlendState;
ComPtr<ID3D11BlendState> TEngine::m_DualSourceBlendState;

bool TEngine::CreateBlendState()
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.RenderTarget[0].BlendEnable = true;
	// RGB 혼합
	//RGB = SrcColor * SrcBlend OP DestColor * DestBlend;
	//RGB = SrcColor * D3D11_BLEND_SRC_ALPHA D3D11_BLEND_OP_ADD DestColor * D3D11_BLEND_INV_SRC_ALPHA;
	//RGB = SrcColor * arcalpha + DestColor * 1-arcalpha;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// alpha 혼합
	// A = SrcAlpha * 1 + DestAlpha * 0;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	// RGB 채널을 모두 사용
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_AlphaBlendState.GetAddressOf())))
	{
		return false;
	}
	// 가산블랜딩
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_AddBlendState.GetAddressOf())))
	{
		return false;
	}
	// 뺄셈블랜딩( 소스-대상 )
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
	if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_SubtrackBlendState.GetAddressOf())))
	{
		return false;
	}
	// 뺄셈블랜딩( 대상-소스 )
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_RevSubtrackBlendState.GetAddressOf())))
	{
		return false;
	}
	// 곱셈블랜딩
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_MultiplyBlendState.GetAddressOf())))
	{
		return false;
	}
	// 듀얼소스컬러 블랜딩
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_SRC1_COLOR;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_DualSourceBlendState.GetAddressOf())))
	{
		return false;
	}
	return true;
}
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
	if (CreateBlendState())
	{
		TDevice::m_pContext->OMSetBlendState(
			m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
	}

	GameDataLoad(L"../../data/script/SpriteInfo.txt");
	// 
	for (auto sprite : g_Sprite)
	{
		if (sprite.m_iType == TSpriteInfo::UV_Animation)
		{			
			TVector2 pos = { 0.0f, 0.0f };
			std::unique_ptr<ASprite> asset = std::make_unique<AEffectUV>();
			asset->SetName(sprite.m_Name);
			if (sprite.m_szMaskTextureFilePath == L"nullptr")
			{
				if (asset->Create(pos, { 50.0f,50.0f },
					sprite.m_szTextureFilePath,
					sprite.m_szShaderFilePath))
				{
					asset->m_fStep = 0.1f;
				}
			}
			else
			{
				if (asset->Create(pos, { 50.0f,50.0f },
					sprite.m_szTextureFilePath,
					sprite.m_szMaskTextureFilePath,
					sprite.m_szShaderFilePath))
				{
					asset->m_fStep = 0.1f;
				}
			}
			
			//auto texInfo = asset->m_pRenderComponent->m_TexDesc;
			for (auto& data : sprite.m_uvArray)
			{
				TVector4 uv;
				// p rt 영역 내부로 조정한다. +1 ~ -2 : 0~10->1~9 로 조정됨.
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
			if (sprite.m_szMaskTextureFilePath == L"nullptr")
			{
				if (asset->Create(pos, { 50.0f,50.0f },
					sprite.m_szTextureFilePath,
					sprite.m_szShaderFilePath))
				{
					asset->m_fStep = 0.1f;
				}
			}
			else
			{
				if (asset->Create(pos, { 50.0f,50.0f },
					sprite.m_szTextureFilePath,
					sprite.m_szMaskTextureFilePath,
					sprite.m_szShaderFilePath))
				{
					asset->m_fStep = 0.1f;
				}
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
void	TEngine::Release()
{
	m_CompList.clear();
	TEngine::gTexManager.Clear();
	TEngine::gShaderManager.Clear();
	TEngine::gSpriteManager.Clear();
	TEngine::gSoundManager.Clear();
}
TEngine::~TEngine()
{
	Release();
}