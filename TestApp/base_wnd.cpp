#include "stdafx.h"
#include "base_wnd.h"

namespace test_app
{

	std::unordered_map<HWND, base_wnd*> base_wnd::ms_all_windows;
	HINSTANCE base_wnd::ms_this_inst;
	base_wnd* base_wnd::ms_new_window = nullptr;

	base_wnd::base_wnd(HWND its) :m_my_hwnd(its)
	{
		ms_all_windows[its] = this;
	}

	base_wnd::~base_wnd()
	{
		ms_all_windows[m_my_hwnd] = nullptr;
	}

	BOOL base_wnd::wnd_proc(UINT message, WPARAM wParam, LPARAM lParam){ return false; }

	BOOL base_wnd::s_static_wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (ms_all_windows[hWnd] == nullptr)
		{
			if (ms_new_window == nullptr)
				return false;

			ms_all_windows[hWnd] = ms_new_window;
			ms_new_window->m_my_hwnd = hWnd;
			ms_new_window = nullptr;
		}

		return ms_all_windows[hWnd]->wnd_proc(message, wParam, lParam);
	}


}
