//==============================================================================
// File		Main.h
// Comment	メインプログラム
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#include "Common/System.h"
#include "System/SystemManager.h"

//------------------------------------------------------------------------------
//	マクロ
//------------------------------------------------------------------------------
static const TString CLASS_NAME  = L"AppClass";				// ウインドウのクラス名
static const TString WINDOW_NAME = L"DirectX11 GameBase 2D";// ウインドウのキャプション名

const int	kGameFPS			= 60;						// 秒間フレーム数
const int	kFPSMeasuringSpan	= 500;						// FPS計測間隔(ミリ秒)
const int	kInMSecOneSec		= 1000;						// 1秒をミリ秒で表す
const float	kInMSecOneSecFloat	= 1000.0f;					// 上記実数版

CSystemManager* g_pGameSystem = nullptr;

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//------------------------------------------------------------------------------
//	メインプログラム実行
//------------------------------------------------------------------------------
//void main(void)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace ns_ConstantTable;

#ifdef _DEBUG
	// メモリリーク調査用関数
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//----------------------------------
	//簡単なモジュールの実行確認
	//----------------------------------

	//OutputDebugString(_T("=========================================\n"));
	//OutputDebugString(_T("=========================================\n"));
	//MessageBox(NULL, _T("a"), _T("c"), MB_OK);
	////FILECHECK(_T("test.txt"));
	//MSGBOX(_T("TEST IS = %s"), _T("124"));

	//const auto startTime = std::chrono::system_clock::now();
	//// TODO: ここに計測したい処理を記述
	//const auto endTime = std::chrono::system_clock::now();
	//const auto timeSpan = endTime - startTime;
	//std::cout << "処理時間:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;


	//CSystemManager* p_GameSystem = new CSystemManager();

	//p_GameSystem->Update(1.0f);

	//SafeFinalize(p_GameSystem);

	//----------------------------------
	//簡単なモジュールの実行確認 Fin
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

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
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

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetHinstance(hInstance);
	SetHWnd(hWnd);

	CSingleton<CSystemManager>::Create();

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// メッセージループ
	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			// Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
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

				// DirectXの処理
				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME.c_str(), wcex.hInstance);
	//SafeFinalize(g_pGameSystem);

	CSingleton<CSystemManager>::Instance()->Finalize();
	CSingleton<CSystemManager>::Destroy();

	// 終了処理
	Uninit();
	timeEndPeriod(1);				// 分解能を戻す
	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
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
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	using namespace ns_ConstantTable;

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{

}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void Draw(void)
{
	auto pSystem = CSingleton<CSystemManager>::Instance();
	pSystem->Draw();
}
