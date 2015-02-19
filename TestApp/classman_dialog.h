#pragma once
#include "base_dialog_wnd.h"
#include "classman.h"
#include "main_wnd.h"

namespace test_app{

	class classman_dialog : public base_dialog_wnd
	{
	public:
		classman_dialog(HWND hwnd, main_wnd* main);
		virtual ~classman_dialog();

		virtual INT_PTR wnd_proc(UINT message, WPARAM wParam, LPARAM lParam);

	private:
		char classman_ok();
		main_wnd* m_main;
	};
}

