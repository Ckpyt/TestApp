#pragma once
#include "stdafx.h"
#include "base_dialog_wnd.h"
#include "teacher.h"
#include "main_wnd.h"

namespace test_app
{

	class teacher_dialog:base_dialog_wnd
	{
	public:
		teacher_dialog(HWND hwnd, main_wnd* main);
		virtual ~teacher_dialog();

		virtual INT_PTR wnd_proc(UINT message, WPARAM wParam, LPARAM lParam);

	private:
		void teacher_ok();
		main_wnd* main;
	};
}

