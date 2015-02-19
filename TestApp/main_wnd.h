#pragma once
#include "stdafx.h"
#include "base_wnd.h"
#include "teacher.h"
#include "classman.h"

namespace test_app
{

	class main_wnd : public base_wnd
	{
	public:
		main_wnd(HWND its);
		virtual ~main_wnd();

		virtual BOOL wnd_proc(UINT message, WPARAM wParam, LPARAM lParam);

		classman* m_active_classman;
		teacher* m_active_teacher;
		
	private:

		bool del_classman_from_teacher();
		bool view_classman_to_teacher();
		bool add_classman_to_teacher();
		bool del_teacher();
		bool edit_teacher();
		bool del_classman();
		bool edit_classman();
	};
}

