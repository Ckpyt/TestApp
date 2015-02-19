#include "stdafx.h"
#include "base_dialog_wnd.h"

namespace test_app
{

	std::unordered_map<HWND, base_dialog_wnd*> base_dialog_wnd::ms_all_dialog_windows;
	HINSTANCE base_dialog_wnd::ms_this_inst;
	base_dialog_wnd* base_dialog_wnd::ms_new_window = nullptr;
	int base_dialog_wnd::ms_select_pos;

	base_dialog_wnd::base_dialog_wnd(HWND its) : m_my_hwnd(its)
	{
		ms_all_dialog_windows[its] = this;
	}


	base_dialog_wnd::~base_dialog_wnd()
	{
	}

	INT_PTR base_dialog_wnd::wnd_proc(UINT message, WPARAM wParam, LPARAM lParam){ return false; }

	INT_PTR base_dialog_wnd::s_static_wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (ms_all_dialog_windows[hWnd] == nullptr)
		{
			if (ms_new_window == nullptr)
				return false;
			ms_all_dialog_windows[hWnd] = ms_new_window;
			ms_new_window->m_my_hwnd = hWnd;
			ms_new_window = nullptr;
		}

		return ms_all_dialog_windows[hWnd]->wnd_proc(message, wParam, lParam);
	}

}