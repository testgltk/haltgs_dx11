//==============================================================================
// File		SystemManager.cpp
// Comment	�����V�X�e���Ǘ��N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��15��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
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

	//����Ȃ��̂����O�ɓo�^����
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
	
	pString->printfString(XMFLOAT2(90, 90), L"DX11�`��������� %.3f", ft);
	pString->SetColor(XMFLOAT4(0,0, 1, 1));
	pString->printfString(XMFLOAT2(230, 190), L"���s��\n�e�X�g�ł�\n���m�ɕ\������Ă܂����H");
	pString->SetColor(XMFLOAT4(1, 1, 0, 1));
	pString->printfString(XMFLOAT2(230, 390), L"�����\�����\�ɂȂ����玟�̂��Ƃ����߂��Ă��������B");
	pString->printfString(XMFLOAT2(230, 440), L"[1]:���������[�N�̗L���m�F");
	pString->printfString(XMFLOAT2(230, 480), L"[2]:��ʂ̍ő剻�����x����������A�ŏ��������x���������肷��");
	pString->printfString(XMFLOAT2(230, 520), L"(������ł��̓���ɂ�蕶���񂪉��錻�ۂ��m�F�ł��Ă܂��B");
	pString->printfString(XMFLOAT2(230, 560), L"�����͖���قȂ�܂�");
	pString->printfString(XMFLOAT2(230, 600), L"������ł����l�̌��ۂ��������邩�����Ă��������B");
	pString->printfString(XMFLOAT2(230, 640), L"��ʂɑ΂��Ă��̂悤�ȑ�������Ȃ�����A���Ȃ����Ƃ��m�F���Ă܂��B");
	pString->printfString(XMFLOAT2(230, 680), L"�����͕s���ł�)");
}

void CSystemManager::Draw(void)
{	
	m_pRenderer->Clear();
	//Rendering...

	g_pSprite2->Draw();
	g_pSprite->Draw();

	m_pSceneManager->Draw();

	//const auto startTime = std::chrono::system_clock::now();
	////// TODO: �����Ɍv���������������L�q
	//pString->Draw(); // �����낵�����Ƃ�12-19mlsec! ���P�̕K�v����
	//const auto endTime = std::chrono::system_clock::now();
	//const auto timeSpan = endTime - startTime;
	//OUTPUT(L"��������:%d", std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count());
	//std::cout << "��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
	
	pString->Draw();
	m_pRenderer->Present();
}

void CSystemManager::Finalize(void)
{
	//�o�^�Ƌt���ɔj��
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