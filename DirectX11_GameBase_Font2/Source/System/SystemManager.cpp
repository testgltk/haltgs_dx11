//==============================================================================
// File		SystemManager.cpp
// Comment	内部システム管理クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SystemManager.h"
#include "Common/System.h"
#include "Renderer/Renderer.h"
#include "Sprite/Sprite.h"
#include "Scene/SceneManager.h"

#include "FontTexture/FontTexture.h"
#include "FontTexture/FontString.h"
using namespace ns_ConstantTable;

static const CSprite::PARAM param1 = { XMFLOAT2(0, 0), 0.0f,L"Resources/Texture/BlockTexture.png" };
static const CSprite::PARAM param2 = { XMFLOAT2(SCREEN_WIDTH  * 0.5f, SCREEN_HEIGHT* 0.5f), 0.0f,L"Resources/Texture/field001.jpg" };

CSprite* g_pSprite  = nullptr;
CSprite* g_pSprite2 = nullptr;
FontTexture* Font = nullptr;
CFontString* pString = nullptr;
CSystemManager* CSystemManager::m_pInstance = nullptr;

CSystemManager::CSystemManager(void)
	:SystemCount(0)
	, m_pSystems{}
{
	m_pInstance = this;

	//特殊なものを事前に登録する
	m_pKeyboard		= new CInputKeyboard();
	m_pMouse		= new CInputMouse();
	m_pRenderer		= new CRenderer();
	m_pSceneManager = new CSceneManager();
	g_pSprite		= new CSprite(param1);
	g_pSprite2		= new CSprite(param2);

	EntrySystem(m_pKeyboard);
	EntrySystem(m_pMouse);
	EntrySystem(m_pRenderer);
	EntrySystem(m_pSceneManager);

	m_pKeyboard->Initialize(GetHinstance(), GetHWnd());
	m_pMouse->Initialize(GetHinstance(), GetHWnd());
	

	Font = new FontTexture();
	Font->Create(TEXT("A"), 256);
	pString = new CFontString();

}

CSystemManager::~CSystemManager(void)
{
	SafeFinalize(g_pSprite);
	SafeFinalize(g_pSprite2);
	SafeDelete(Font);

	SafeDelete(pString);
}

void CSystemManager::EntrySystem(ISystem* pSystem)
{
	if (SystemCount >= MAX_SYSTEM)
	{
		//DBGMESSAGE
		MSGBOX(_T("SYSTEM COUNT OVER MAX => %d"), SystemCount);
		return;
	}

	m_pSystems[SystemCount] = pSystem;
	SystemCount++;
}

void CSystemManager::Update(void)
{
	for (int i = 0; i < SystemCount; i++)
	{
		m_pSystems[i]->Update();
	}

	//test Code
	CInputKeyboard* pKeyboard = GetKeyboard();
	static float fTest = g_pSprite->GetPosition().x;
	static float fTestY = g_pSprite->GetPosition().y;
	if (pKeyboard->IsKeyPress(DIK_A))
	{
		fTest -= 1.0f;
		g_pSprite->SetPosition(XMFLOAT2(fTest, fTestY));
	}
	else if (pKeyboard->IsKeyPress(DIK_D))
	{
		fTest += 1.0f;
		g_pSprite->SetPosition(XMFLOAT2(fTest, fTestY));
	}
	else if (pKeyboard->IsKeyPress(DIK_W))
	{
		fTestY -= 1.0f;
		g_pSprite->SetPosition(XMFLOAT2(fTest, fTestY));
	}
	else if (pKeyboard->IsKeyPress(DIK_S))
	{
		fTestY += 1.0f;
		g_pSprite->SetPosition(XMFLOAT2(fTest, fTestY));
	}
	else if (pKeyboard->IsKeyPress(DIK_C))
	{
		static float fRot = 0.0f;
		fRot += 0.01f;
		g_pSprite->SetRotation(fRot);
	}
	else if (pKeyboard->IsKeyTrigger(DIK_Z))
	{
		g_pSprite->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);
	}
	else if (pKeyboard->IsKeyTrigger(DIK_X))
	{
		g_pSprite->SetPolygonAlign(CSprite::ALIGN_CENTER);
	}
	else if (pKeyboard->IsKeyTrigger(DIK_8))
	{
		g_pSprite->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 0.5f));
	}
	else if (pKeyboard->IsKeyTrigger(DIK_9))
	{
		//g_pSprite->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 0.5f));
		//g_pSprite->SetTexture(*Font->GetTexture()->GetResourceView());
		//g_pSprite->SetTexture(Font->());


	}

	CInputMouse* pM = m_pMouse;
	POINT* p = pM->GetPosWorld();
	g_pSprite->SetPosition(XMFLOAT2(p->x, p->y));

	static float ft = 0.0f;
	ft += 0.1f;
	static int dNUM = 0;
	dNUM++;

	pString->Update();
	
	pString->printfString(XMFLOAT2(90, 90), L"DX11描画実験処理 %.3f", ft);
	pString->SetColor(XMFLOAT4(0,0, 1, 1));
	pString->printfString(XMFLOAT2(230, 190), L"改行の\nテストです\n正確に表示されてますか？");
	pString->SetColor(XMFLOAT4(1, 1, 0, 1));
	pString->printfString(XMFLOAT2(230, 390), L"もし表示が可能になったら次のことをためしてください。");
	pString->printfString(XMFLOAT2(230, 440), L"[1]:メモリリークの有無確認");
	pString->printfString(XMFLOAT2(230, 480), L"[2]:画面の最大化を何度も押したり、最小化を何度もおしたりする");
	pString->printfString(XMFLOAT2(230, 520), L"(こちらでその動作により文字列が壊れる現象が確認できてます。");
	pString->printfString(XMFLOAT2(230, 560), L"壊れ方は毎回異なります");
	pString->printfString(XMFLOAT2(230, 600), L"そちらでも同様の現象が発生するか教えてください。");
	pString->printfString(XMFLOAT2(230, 640), L"画面に対してそのような操作をしない限り、壊れないことを確認してます。");
	pString->printfString(XMFLOAT2(230, 680), L"原因は不明です)");
}

void CSystemManager::Draw(void)
{	
	m_pRenderer->Clear();
	//Rendering...

	//g_pSprite2->Draw();
	//g_pSprite->Draw();

	m_pSceneManager->Draw();

	//const auto startTime = std::chrono::system_clock::now();
	////// TODO: ここに計測したい処理を記述
	//pString->Draw(); // おそろしいことに12-19mlsec! 改善の必要あり
	//const auto endTime = std::chrono::system_clock::now();
	//const auto timeSpan = endTime - startTime;
	//OUTPUT(L"処理時間:%d", std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count());
	//std::cout << "処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
	
	pString->Draw();
	m_pRenderer->Present();


	// シーン遷移
	m_pSceneManager->Change();
}

void CSystemManager::Finalize(void)
{
	//登録と逆順に破棄
	for (int i = SystemCount; i >= 0; i--)
	{
		SafeFinalize(m_pSystems[i]);
	}
}

ID3D11Device* CSystemManager::GetDevice(void)
{
	return m_pRenderer->GetDevice();
}

ID3D11DeviceContext* CSystemManager::GetDeviceContext(void)
{
	return m_pRenderer->GetDeviceContext();
}

CSystemManager* CSystemManager::GetInstance(void)
{
	return m_pInstance;
}