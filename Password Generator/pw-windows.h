#pragma once
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include "password.h"

#define PW_WINDOW_TITLE "Password Generator | Halaszka#4143"

#define sizeX 500
#define sizeY 300

#define GENERATE 1
#define COPY 2
#define GENERATOR_PASSWORD 6969


#define VERSION "V 1.0 Banana"

using namespace Gdiplus;


namespace gen {
	//This is the Window Proc for the Generator Button-Window
	LRESULT CALLBACK genEditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

		static RECT rect;

		static int rc;

		static std::string password = "";

		switch (msg) {

		case WM_SIZE: {
			GetWindowRect(hwnd, &rect);

			return 0;
		}

		case WM_PAINT: {

			HDC hdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(hwnd, &ps);

			Graphics graphics(hdc);
			Pen pen(Color(255, 160, 206, 217));


			graphics.DrawRectangle(&pen, 0, 0, rect.right - rect.left - 5, rect.bottom - rect.top - 5);

			SolidBrush color(Color(255, 74, 78, 89));
			graphics.FillRectangle(&color, 1, 1, rect.right - rect.left - 6, rect.bottom - rect.top - 6);

			if (password != "") {
				StringFormat stringFormat;
				stringFormat.SetLineAlignment(StringAlignmentCenter);

				FontFamily fontFamily(L"Arial");
				Font font(&fontFamily, 18, FontStyleRegular, UnitPixel);


				std::wstring wstr_password(password.begin(), password.end());


				SolidBrush solidBrush(Color(255, 255, 244, 234));

				const wchar_t* szPassword = wstr_password.c_str();

				RectF rectF(0, 0, 400, 50);

				graphics.DrawString(wstr_password.c_str(), -1, &font, rectF, &stringFormat, &solidBrush);

				SetWindowTextA(hwnd, password.c_str());
			}

			EndPaint(hwnd, &ps);

			return 0;

		}

		case GENERATOR_PASSWORD: {


			password = (const char*) lParam;

			InvalidateRect(hwnd, NULL, TRUE);

			return 0;
		}



		}


		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	//This function "createGenEditBox" creates the EditBox where the Password is stored in
	int createGenEditBox(HWND* hwnd, HWND ownerHwnd, HINSTANCE hInstance) {

		const wchar_t szGenEditBox[] = L"Password Generator EditBox";

		WNDCLASS wc = {};

		wc.lpszClassName = szGenEditBox;
		wc.lpfnWndProc = genEditProc;
		wc.hInstance = hInstance;

		RegisterClass(&wc);

		*hwnd = CreateWindow(szGenEditBox, NULL, WS_CHILD | WS_VISIBLE , 43, 20, 400, 50, ownerHwnd, NULL, hInstance, NULL);

		if (*hwnd == NULL) {
			return -1;
		}
		else {
			return 0;
		}



	}




	//This is the Window Proc for the Generator Button-Window
	LRESULT CALLBACK genBtnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		static RECT rect;
		int id = GetWindowLongPtrA(hwnd, GWL_ID);

		switch (msg) {

		case WM_SIZE:
			GetWindowRect(hwnd, &rect);
		case WM_PAINT: {

			HDC hdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(hwnd, &ps);
			//Generate Button
			Graphics graphics(hdc);
			LinearGradientBrush gradient(Point(0, 0), Point(444, 0), Color(255, 43, 122, 120), Color(255, 58, 175, 169));
			FontFamily fontFamily(L"Arial");
			Font font(&fontFamily, 24, FontStyleBold, UnitPixel);
			SolidBrush text_color(Color(255, 255, 244, 234));

			graphics.FillRectangle(&gradient, 0, 0, 500, 50);

			StringFormat stringFormat;

			stringFormat.SetAlignment(StringAlignmentCenter);
			stringFormat.SetLineAlignment(StringAlignmentCenter);

			if (id == GENERATE) {

				RectF rectF(0, 0, 300, 50);
				graphics.DrawString(L"Generate", -1, &font, rectF, &stringFormat, &text_color);
			}

			if (id == COPY) {
				RectF rectF(0, 0, 98, 50);
				graphics.DrawString(L"Copy", -1, &font, rectF, &stringFormat, &text_color);
			}

			EndPaint(hwnd, &ps);

			return 0;
		}


		case WM_LBUTTONUP: {

			if (id == GENERATE) {
				SendMessageA(GetParent(hwnd), WM_COMMAND, GENERATE, 0);
			}
			else if (id == COPY) {
				SendMessageA(GetParent(hwnd), WM_COMMAND, COPY, 0);
			}

			return 0;
		}
			

			

		}


		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	//The "createGenBtn" function is used to create the Main-Window
	int createGenBtn(HWND* hwnd, HWND* hwnd2, HWND ownerHwnd, HINSTANCE hInstance) {
		const wchar_t szGenBtn[] = L"Password Generator GenButton";

		WNDCLASS wc = {};

		wc.lpszClassName = szGenBtn;
		wc.lpfnWndProc = genBtnProc;
		wc.hInstance = hInstance;

		RegisterClass(&wc);


		*hwnd = CreateWindow(szGenBtn, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 43, 200, 300, 50, ownerHwnd, (HMENU) GENERATE, hInstance, NULL);
		*hwnd2 = CreateWindow(szGenBtn, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 345, 200, 98, 50, ownerHwnd, (HMENU) COPY, hInstance, NULL);


		if (*hwnd == NULL) {
			return -1;
		}

		return 0;
	}
}


//==> Create a Namespace with the Name "pw"
namespace pw {

	HWND genBtn;
	HWND genCopyBtn;
	HWND genEdit;

	//This is the Window Proc for the Main-Window
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

		static HINSTANCE hInstance = GetModuleHandle(NULL);
		int rc = 100;

		switch (msg) {
		
		case WM_CREATE: {
			rc = gen::createGenBtn(&genBtn, &genCopyBtn, hwnd, hInstance);

			if (rc == -1) {
				MessageBoxA(hwnd, "The program could not be created correctly!", "Error", MB_OK | MB_ICONERROR);
			}

			rc = gen::createGenEditBox(&genEdit, hwnd, hInstance);

			if (rc == -1) {
				MessageBoxA(hwnd, "The program could not be created correctly!", "Error", MB_OK | MB_ICONERROR);
			}

			return 0;
		}


		case WM_COMMAND: {

			//Click on Generate
			if (LOWORD(wParam) == GENERATE) {
				std::string temp_pw = alaska_pass(32);


				SendMessage(genEdit, GENERATOR_PASSWORD, 0, (LPARAM) temp_pw.c_str());
			}
			
			//Click on Copy
			if (LOWORD(wParam) == COPY) {
				int len = GetWindowTextLengthA(genEdit);

				char buffer[33];

				GetWindowTextA(genEdit, buffer, len + 1);

				OpenClipboard(0);
				EmptyClipboard();
				HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, len + 1);
				memcpy(GlobalLock(hg), buffer, len + 1);
				GlobalUnlock(hg);
				SetClipboardData(CF_TEXT, hg);
				CloseClipboard();
				GlobalFree(hg);
			}
			return 0;

		}


		case WM_PAINT: {

			HDC hdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(hwnd, &ps);

			Graphics graphics(hdc);
			
			FontFamily fontFamily(L"Arial");
			Font font(&fontFamily, 10, FontStyleRegular, UnitPixel);

			SolidBrush text(Color(255, 255, 255, 255));

			graphics.DrawString(TEXT(VERSION), -1, &font, PointF(0, 0), &text);

			EndPaint(hwnd, &ps);

			return 0;
		}
		case WM_CLOSE: {
			DestroyWindow(hwnd);
			return 0;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}


		}


		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	//The "createMain" function is used to create the Main-Window
	int createMain(HWND* hwnd, HINSTANCE hInstance, int iCmdShow, const wchar_t szMain[]) {
		HBRUSH background_color = CreateSolidBrush(RGB(51, 51, 60));

		WNDCLASS wc = {};

		wc.lpszClassName = szMain;
		wc.hInstance = hInstance;
		wc.lpfnWndProc = WndProc;
		wc.hbrBackground = background_color;

		RegisterClass(&wc);
		//Define the Flags for the Window
		DWORD flags = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MINIMIZE;
		//Create the Window
		*hwnd = CreateWindow(szMain, TEXT(PW_WINDOW_TITLE), flags, CW_USEDEFAULT, CW_USEDEFAULT, sizeX, sizeY, NULL, NULL, hInstance, NULL);

		//Check if the Window was created
		if (*hwnd == NULL) {
			return -1;
		}

		//Show the Window with the function ShowWindow
		ShowWindow(*hwnd, iCmdShow);

		return 0;

	}




}