#pragma once
#include "stdafx.h"

namespace test_app
{

	class base_dialog_wnd
	{
	public:
		base_dialog_wnd(HWND its);
		virtual ~base_dialog_wnd();

		virtual INT_PTR wnd_proc(UINT message, WPARAM wParam, LPARAM lParam);

		static INT_PTR CALLBACK s_static_wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static HINSTANCE ms_this_inst;
		static base_dialog_wnd* ms_new_window;
		static int ms_select_pos;
		HWND m_my_hwnd;
	protected:
		static std::unordered_map<HWND, base_dialog_wnd*> ms_all_dialog_windows;
	};
}
