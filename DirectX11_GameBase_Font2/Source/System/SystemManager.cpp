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

FontTexture* Font = nullptr;
CSystemManager* CSystemManager::m_pInstance = nullptr;

// �ÓI�����o�ϐ�
int CSystemManager::m_snScore = 0;

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

	EntrySystem(m_pKeyboard);
	EntrySystem(m_pMouse);
	EntrySystem(m_pRenderer);
	EntrySystem(m_pSceneManager);

	m_pKeyboard->Initialize(GetHinstance(), GetHWnd());
	m_pMouse->Initialize(GetHinstance(), GetHWnd());


	Font = new FontTexture();
	Font->Create(TEXT("A"), 256);
	m_pString = new CFontString();
	
}

CSystemManager::~CSystemManager(void)
{
	SafeDelete(Font);

	SafeDelete(m_pString);
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
	m_pString->Update();

	for (int i = 0; i < SystemCount; i++)
	{
		m_pSystems[i]->Update();
	}

	//test Code

	static float ft = 0.0f;
	ft += 0.1f;
	static int dNUM = 0;
	dNUM++;

	/*
	m_pString->printfString(XMFLOAT2(90, 90), L"DX11�`��������� %.3f", ft);
	m_pString->SetColor(XMFLOAT4(0,0, 1, 1));
	m_pString->printfString(XMFLOAT2(230, 190), L"���s��\n�e�X�g�ł�\n���m�ɕ\������Ă܂����H");
	m_pString->SetColor(XMFLOAT4(1, 1, 0, 1));
	m_pString->printfString(XMFLOAT2(230, 390), L"�����\�����\�ɂȂ����玟�̂��Ƃ����߂��Ă��������B");
	m_pString->printfString(XMFLOAT2(230, 440), L"[1]:���������[�N�̗L���m�F");
	m_pString->printfString(XMFLOAT2(230, 480), L"[2]:��ʂ̍ő剻�����x����������A�ŏ��������x���������肷��");
	m_pString->printfString(XMFLOAT2(230, 520), L"(������ł��̓���ɂ�蕶���񂪉��錻�ۂ��m�F�ł��Ă܂��B");
	m_pString->printfString(XMFLOAT2(230, 560), L"�����͖���قȂ�܂�");
	m_pString->printfString(XMFLOAT2(230, 600), L"������ł����l�̌��ۂ��������邩�����Ă��������B");
	m_pString->printfString(XMFLOAT2(230, 640), L"��ʂɑ΂��Ă��̂悤�ȑ�������Ȃ�����A���Ȃ����Ƃ��m�F���Ă܂��B");
	m_pString->printfString(XMFLOAT2(230, 680), L"�����͕s���ł�)");
	*/
}

void CSystemManager::Draw(void)
{	
	m_pRenderer->Clear();
	//Rendering...

	m_pSceneManager->Draw();

	//const auto startTime = std::chrono::system_clock::now();
	////// TODO: �����Ɍv���������������L�q
	//m_pString->Draw(); // �����낵�����Ƃ�12-19mlsec! ���P�̕K�v����
	//const auto endTime = std::chrono::system_clock::now();
	//const auto timeSpan = endTime - startTime;
	//OUTPUT(L"��������:%d", std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count());
	//std::cout << "��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
	
	m_pString->Draw();
	m_pRenderer->Present();

	m_pSceneManager->Change();
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