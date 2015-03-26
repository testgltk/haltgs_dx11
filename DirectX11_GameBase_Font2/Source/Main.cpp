//==============================================================================
// File		Main.h
// Comment	���C���v���O����
// Author	TOMOHIRO KOUNO
// Create	2014�N6��15��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#include "Common/System.h"
#include "System/SystemManager.h"

//------------------------------------------------------------------------------
//	�}�N��
//------------------------------------------------------------------------------
static const TString CLASS_NAME  = L"AppClass";				// �E�C���h�E�̃N���X��
static const TString WINDOW_NAME = L"DirectX11 GameBase 2D";// �E�C���h�E�̃L���v�V������

const int	kGameFPS			= 60;						// �b�ԃt���[����
const int	kFPSMeasuringSpan	= 500;						// FPS�v���Ԋu(�~���b)
const int	kInMSecOneSec		= 1000;						// 1�b���~���b�ŕ\��
const float	kInMSecOneSecFloat	= 1000.0f;					// ��L������

CSystemManager* g_pGameSystem = nullptr;

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//------------------------------------------------------------------------------
//	���C���v���O�������s
//------------------------------------------------------------------------------
//void main(void)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace ns_ConstantTable;

#ifdef _DEBUG
	// ���������[�N�����p�֐�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//----------------------------------
	//�ȒP�ȃ��W���[���̎��s�m�F
	//----------------------------------

	//OutputDebugString(_T("=========================================\n"));
	//OutputDebugString(_T("=========================================\n"));
	//MessageBox(NULL, _T("a"), _T("c"), MB_OK);
	////FILECHECK(_T("test.txt"));
	//MSGBOX(_T("TEST IS = %s"), _T("124"));

	//const auto startTime = std::chrono::system_clock::now();
	//// TODO: �����Ɍv���������������L�q
	//const auto endTime = std::chrono::system_clock::now();
	//const auto timeSpan = endTime - startTime;
	//std::cout << "��������:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;


	//CSystemManager* p_GameSystem = new CSystemManager();

	//p_GameSystem->Update(1.0f);

	//SafeFinalize(p_GameSystem);

	//----------------------------------
	//�ȒP�ȃ��W���[���̎��s�m�F Fin
	//----------------------------------

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME.c_str() ,
		NULL
	};
	HWND hWnd;
	MSG msg;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
		CLASS_NAME.c_str(),
		WINDOW_NAME.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetHinstance(hInstance);
	SetHWnd(hWnd);

	CSingleton<CSystemManager>::Create();

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ���b�Z�[�W���[�v
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			// Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				//g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// DirectX�̏���
				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME.c_str(), wcex.hInstance);
	//SafeFinalize(g_pGameSystem);

	CSingleton<CSystemManager>::Instance()->Finalize();
	CSingleton<CSystemManager>::Destroy();

	// �I������
	Uninit();
	timeEndPeriod(1);				// ����\��߂�
	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=============================================================================
// ����������
// hInstance : �C���X�^���X�̃n���h��
// hWnd      : �E�C���h�E�̃n���h��
// bWindow   : �E�C���h�E���[�h�ɂ��邩�ǂ���
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	using namespace ns_ConstantTable;

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	auto pSystem = CSingleton<CSystemManager>::Instance();
	pSystem->Update();

	//test Code
	CInputKeyboard* pKeyboard = pSystem->GetKeyboard();

	if (pKeyboard->IsKeyTrigger(DIK_F))
	{
		MSGBOX(L"FKeyTRIGGER!");
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	auto pSystem = CSingleton<CSystemManager>::Instance();
	pSystem->Draw();
}
