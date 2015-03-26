//==============================================================================
// File		DebugModule.cpp
// Comment	デバッグ用プログラム
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

void MSGBOX(TCHAR *Text, ...){
	static TCHAR TEXTRESULT[1024];
	va_list ap;
	va_start(ap, Text);
	_vstprintf_s(TEXTRESULT, Text, ap);
	MessageBox(NULL, TEXTRESULT, _T("MESSAGE"), MB_OK);
	va_end(ap);
}

int YESNO(TCHAR *Text, ...)
{
	int result = 0;
	static TCHAR TEXTRESULT[1024];
	va_list ap;
	va_start(ap, Text);
	_vstprintf_s(TEXTRESULT, Text, ap);
	result = MessageBox(NULL, TEXTRESULT, _T("YES OR NO"), MB_YESNO);
	va_end(ap);

	return result;
}

void WARRNING(TCHAR *Text, ...){
	static TCHAR TEXTRESULT[1024];
	va_list ap;
	va_start(ap, Text);
	_vstprintf_s(TEXTRESULT, Text, ap);
	MessageBox(NULL, TEXTRESULT, _T("WARRNING"), MB_ICONWARNING);
	va_end(ap);
}

void OUTPUT(TCHAR *Text, ...){
	static TCHAR TEXTRESULT[1024];
	va_list ap;
	va_start(ap, Text);
	_vstprintf_s(TEXTRESULT, Text, ap);
	OutputDebugString(TEXTRESULT);
	va_end(ap);
}

bool FILECHECK(TCHAR *FilePath)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA findData;

	hFindFile = ::FindFirstFile(FilePath, &findData);
	//ファイルある
	if (hFindFile != INVALID_HANDLE_VALUE)
	{
		::FindClose(hFindFile);
		return true;
	}
	else
	{
		//エラーレベルに応じ、結果を出力
		OUTPUT(_T("\n\nFILE %s is Not Found!\n\n"), FilePath);

		//ASSERTチェック始めるか聞く
		#ifdef _DEBUG
		if (YESNO(_T("FILE %s is Not Found! IsAssertCheck?"), FilePath) == IDYES)
		{	
			MYASSERT(false, "FILE %s is Not Found!", FilePath)
		}
		#else
		WARRNING(_T("NOFILE %s"), FilePath);
		#endif
	}
	return false;
}

bool FILECHECK(TString FilePath)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA findData;

	hFindFile = ::FindFirstFile(FilePath.c_str(), &findData);
	//ファイルある
	if (hFindFile != INVALID_HANDLE_VALUE)
	{
		::FindClose(hFindFile);
		return true;
	}
	else
	{
		//エラーレベルに応じ、結果を出力
		OUTPUT(_T("\n\nFILE %s is Not Found!\n\n"), FilePath.c_str());

		//ASSERTチェック始めるか聞く
#ifdef _DEBUG
		if (YESNO(_T("FILE %s is Not Found! IsAssertCheck?"), FilePath.c_str()) == IDYES)
		{
			MYASSERT(false, "FILE %s is Not Found!", FilePath.c_str())
		}
#else
		WARRNING(_T("NOFILE %s"), FilePath.c_str());
#endif
	}
	return false;
}