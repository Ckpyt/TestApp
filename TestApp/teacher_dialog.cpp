#include "stdafx.h"
#include "teacher_dialog.h"

namespace test_app
{
	teacher_dialog::teacher_dialog(HWND hwnd, main_wnd* mn) :base_dialog_wnd(hwnd), main(mn)
	{
	}


	teacher_dialog::~teacher_dialog()
	{
	}

	INT_PTR teacher_dialog::wnd_proc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		static wchar_t* a[3] = // ученые степени.
		{
			L"отсутствует", L"кандидат наук", L"доктор наук"
		};
		int k;

		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
		{
			for (int i = 0; i < 3; i++)
			{
				k = SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_HD, CB_ADDSTRING, 0, (LPARAM)a[i]);
			}
			if (main->m_active_teacher != nullptr)						//если изменяем препода, то передаем в окно его параметры
			{
				SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_FIO, WM_SETTEXT, 0, (LPARAM)main->m_active_teacher->get_FIO().c_str());
				SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_MONEY, WM_SETTEXT, 0, (LPARAM)main->m_active_teacher->m_money.c_str());
				SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_HD, CB_SETCURSEL, main->m_active_teacher->m_step, 0);
			}
		}
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDC_TEACHER_MONEY && HIWORD(wParam) == EN_CHANGE) //ввод зарплаты. только числа.
			{
				wchar_t q[MAX_BUFFER_SIZE];
				bool ed = false;
				memset(q, 0, sizeof(wchar_t)* 256);
				k = SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_MONEY, WM_GETTEXT, MAX_BUFFER_SIZE, (LPARAM)q);
				std::wstring mes(q);
				for (size_t i = 0; i < wcslen(q); i++)
				{
					if (!(q[i] >= '0'&&q[i] <= '9'))
					{
						memcpy(q + i, q + 1 + i, (wcslen(q) - i + 1) << 1);
						ed = true;
					}
				}
				if (q[0] == 0)q[0] = '0';
				if (ed)k = SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_MONEY, WM_SETTEXT, wcslen(q), (LPARAM)q);
			}

			if (LOWORD(wParam) == IDOK)
			{
				teacher_ok();
			}

			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(m_my_hwnd, LOWORD(wParam));
				delete this;
				return (INT_PTR)TRUE;
			}
			break;
		}

		return (INT_PTR)FALSE;
	}

	void teacher_dialog::teacher_ok()
	{
		teacher* tek;
		int len = 0;
		int OK = 0;
		if (main->m_active_teacher != nullptr)
		{
			
		}
		
		int i = SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_FIO, WM_GETTEXTLENGTH, 0, (LPARAM)&len);
		if (i == 0 ) return;
		i++;
		wchar_t FIO[MAX_BUFFER_SIZE];
		SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_FIO, WM_GETTEXT, MAX_BUFFER_SIZE, (LPARAM)FIO);

		wchar_t money[MAX_BUFFER_SIZE];
		if (i > 0)
		{
			i++;
			SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_MONEY, WM_GETTEXT, MAX_BUFFER_SIZE, (LPARAM)money);	//берем зарплату
		}
		else
		{
			memcpy(money, L"0", 2 * sizeof(wchar_t));
		}

		tek = teacher::s_find_teacher(std::wstring(FIO));
		i = SendDlgItemMessage(m_my_hwnd, IDC_TEACHER_HD, CB_GETCURSEL, 0, 0);			//ученую степень
		if (i == -1) i = 0;
		if (main->m_active_teacher != nullptr){									//если есть редактирование
			if (tek != nullptr) return;
			tek = main->m_active_teacher;									//то передаем все тому, кого редактируем
			tek->set_FIO( std::wstring(FIO));
			tek->m_money = money;
			tek->m_step = i;
			OK = SendDlgItemMessage(main->m_my_hwnd, IDC_MAIN_TEACHERS, LB_DELETESTRING, ms_select_pos, 0);
			OK = SendDlgItemMessage(main->m_my_hwnd, IDC_MAIN_TEACHERS, LB_INSERTSTRING, ms_select_pos, (LPARAM)FIO);
		}
		else
		{
											//смотрим есть ли такие же ФИО в таблице
			if (tek != nullptr) //и если есть, прекращаем работу
			{ 
				return; 
			}	
			tek = new teacher(std::wstring(FIO), money, i);							//иначе создает препода
			SendDlgItemMessage(main->m_my_hwnd, IDC_MAIN_TEACHERS, LB_ADDSTRING, 0, (LPARAM)FIO);
		}
		
	}
}
