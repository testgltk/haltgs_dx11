#include "Common/Common.h"

HINSTANCE g_Hinstance;
HWND	  g_Hwnd;

HINSTANCE GetHinstance(void)
{
	return g_Hinstance;
}
HWND GetHWnd(void)
{
	return g_Hwnd;
}
void SetHinstance(HINSTANCE hInstance)
{
	g_Hinstance = hInstance;
}
void SetHWnd(HWND hWnd)
{
	g_Hwnd = hWnd;
}
