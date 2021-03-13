#include <Windows.h>
#include <gdiplus.h>

#include "pw-windows.h"
#include "password.h"

#pragma comment(lib, "gdiplus.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

	HWND hwnd;
	const wchar_t szMain[] = L"Password Generator";

	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	Gdiplus::GdiplusStartup(&gdiToken, &gdiplusStartupInput, NULL);

	pw::createMain(&hwnd, hInstance, iCmdShow, szMain);


	MSG msg;


	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiToken);

	return 0;


}