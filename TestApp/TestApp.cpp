// TestApp.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "TestApp.h"

#include "teacher.h"
#include "classman.h"
#include "base_wnd.h"
#include "main_wnd.h"
#include "base_dialog_wnd.h"

#pragma comment(lib, "user32.lib")

using namespace test_app;



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: разместите код здесь.
	MSG msg;
	InitCommonControls();
	// Инициализация глобальных строк
	// Выполнить инициализацию приложения:

	
	base_wnd::ms_this_inst = hInstance;
	base_dialog_wnd::ms_this_inst = hInstance;
	HWND hMainWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG3), nullptr, (DLGPROC)base_wnd::s_static_wnd_proc);
	main_wnd main(hMainWnd);

	if (!hMainWnd) return FALSE;
	
	// Цикл основного сообщения:
	while (GetMessage(&msg,nullptr,0,0)) {
		if (!IsDialogMessage(hMainWnd,&msg)) {
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	return (int) msg.wParam;
}


//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
