#pragma once
#include "stdafx.h"

//базовый класс окна
namespace test_app
{
	class base_wnd
	{
	public:
		base_wnd(HWND its);
		virtual ~base_wnd();

		virtual BOOL wnd_proc(UINT message, WPARAM wParam, LPARAM lParam);

		static BOOL s_static_wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static HINSTANCE ms_this_inst;
		static base_wnd* ms_new_window;
		HWND m_my_hwnd;
	private:
		static std::unordered_map<HWND, base_wnd*> ms_all_windows;


	};
}

