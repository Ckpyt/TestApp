#include "stdafx.h"
#include "classman_dialog.h"

namespace test_app
{
	classman_dialog::classman_dialog(HWND hwnd, main_wnd* mn) :base_dialog_wnd(hwnd), m_main(mn)
	{
	}


	classman_dialog::~classman_dialog()
	{
	}

	INT_PTR classman_dialog::wnd_proc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		wchar_t *a[2] = {L"Да", L"Нет" };

		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			for (int i = 0; i<2; i++) 
			{
				SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_CHECK, CB_ADDSTRING, 0, (LPARAM)a[i]);
			}
			if (m_main->m_active_classman != nullptr)
			{
				int OK;
				OK = SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_FIO, WM_SETTEXT, 0, (LPARAM)m_main->m_active_classman->get_FIO().c_str());
				OK = SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_DAY_OF_BRITH, DTM_SETSYSTEMTIME, 0, (LPARAM)&m_main->m_active_classman->m_day_of_brith);
				if (m_main->m_active_classman->m_many) SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_CHECK, BM_SETCHECK, BST_CHECKED, (LPARAM)0);
			}
			return (INT_PTR)TRUE;

		case WM_COMMAND:

			if (LOWORD(wParam) == IDOK)
			{
				classman_ok();
			}

			if (LOWORD(wParam) == IDOK)
			{
				EndDialog(m_my_hwnd, LOWORD(wParam));
				delete this;
				return (INT_PTR)TRUE;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}

	
	char classman_dialog::classman_ok()
	{
		classman* tek;
		int OK = 0;

		int i = SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_FIO, WM_GETTEXTLENGTH, 0, 0);
		i++;

		wchar_t FIO[MAX_BUFFER_SIZE];
		SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_FIO, WM_GETTEXT, MAX_BUFFER_SIZE, (LPARAM)FIO);

		SYSTEMTIME day_of_brith;
		SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_DAY_OF_BRITH, DTM_GETSYSTEMTIME, i, (LPARAM)&day_of_brith);

		i = SendDlgItemMessage(m_my_hwnd, IDC_CLASSMAN_CHECK, BM_GETCHECK, 0, 0);

		tek = classman::s_find_classman(std::wstring(FIO));
		if (m_main->m_active_classman != nullptr)
		{
			if (tek != nullptr) return -1;
			tek = m_main->m_active_classman;
			tek->set_FIO(std::wstring(FIO));
			tek->m_day_of_brith = day_of_brith;
			tek->m_many = (i == BST_CHECKED);
			OK = SendDlgItemMessage(m_main->m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_DELETESTRING, ms_select_pos, 0);
			OK = SendDlgItemMessage(m_main->m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_INSERTSTRING, ms_select_pos, (LPARAM)FIO);
		}
		else
		{
			if (tek != nullptr)
			{
				EndDialog(m_my_hwnd, LOWORD(IDOK));
				return -1;
			}
			tek = new classman(std::wstring(FIO), day_of_brith, i == BST_CHECKED);
			SendDlgItemMessage(m_main->m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_ADDSTRING, 0, (LPARAM)FIO);
		}

		return 0;
	}

}
