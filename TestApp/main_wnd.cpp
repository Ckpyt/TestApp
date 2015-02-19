#include "stdafx.h"
#include "main_wnd.h"
#include "teacher.h"
#include "classman.h"
#include "teacher_dialog.h"
#include "classman_dialog.h"

namespace test_app 
{
	main_wnd::main_wnd(HWND its): base_wnd(its)
	{
		
	}

	BOOL main_wnd::wnd_proc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		int wm_id, wm_event;
		PAINTSTRUCT ps;
		HDC hdc;

		switch (message)
		{
		case WM_COMMAND:
			wm_id = LOWORD(wParam);
			wm_event = HIWORD(wParam);
			switch (wm_id)
			{
			case IDC_MAIN_TEACHERS:
				if (wm_event == LBN_SELCHANGE) view_classman_to_teacher();		//���� ������������� �� ������ �������, ��������� ��� ��������
				break;
			case IDC_MAIN_REMOVE_CLASSMAN_FROM_TEACHER:			//������� �������� �� �������
				del_classman_from_teacher();
				break;
			case IDC_MAIN_ADD_CLASSMAN_TO_TEACHER:
				add_classman_to_teacher();								//��������� �������� �������
				break;
			case IDC_MAIN_REMOVE_TEACHER:
				if (wm_event == BN_CLICKED)							//������� �������
				{
					del_teacher();
				}
				break;
			case IDC_MAIN_EDIT_TEACHER:							//����������� �������
				if (wm_event == BN_CLICKED)
				{
					edit_teacher();
				}
				break;
			case IDC_MAIN_ADD_TEACHER:
				if (wm_event == BN_CLICKED)						//��������� ������ �������
				{
					m_active_teacher = nullptr;
					teacher_dialog*newdialog = new teacher_dialog(0, this);
					base_dialog_wnd::ms_new_window = (base_dialog_wnd*)newdialog;
					DialogBox(ms_this_inst, MAKEINTRESOURCE(IDD_DIALOG1), m_my_hwnd, base_dialog_wnd::s_static_wnd_proc);
				}
				break;
			case IDC_MAIN_REMOVE_CLASSMAN:
				if (wm_event == BN_CLICKED)						//������� ��������
				{
					del_classman();
				}
			case IDC_MAIN_EDIT_CLASSMAN:
				if (wm_event == BN_CLICKED)						//����������� ��������
				{
					edit_classman();
				}
				break;
			case IDC_MAIN_ADD_CLASSMAN:
				if (wm_event == BN_CLICKED)						//��������� ��������
				{
					m_active_classman = nullptr;
					classman_dialog*newdialog = new classman_dialog(0, this);
					base_dialog_wnd::ms_new_window = (base_dialog_wnd*)newdialog;
					DialogBox(ms_this_inst, MAKEINTRESOURCE(IDD_DIALOG2), m_my_hwnd, base_dialog_wnd::s_static_wnd_proc);
				}
				break;
			case 2:												//�����
				PostQuitMessage(0);
				break;
			default:
				return false;
			}

			break;
		case WM_PAINT:
			hdc = BeginPaint(m_my_hwnd, &ps);
			// TODO: �������� ����� ��� ���������...
			EndPaint(m_my_hwnd, &ps);
			break;
		case WM_DESTROY:
			DestroyWindow(m_my_hwnd);
			PostQuitMessage(0);
			delete this;
			break;
		default:
			return false;
		}
		return 0;
	}

	main_wnd::~main_wnd()
	{

	}


	//������� �������� �� �������
	bool main_wnd::del_classman_from_teacher()
	{													
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELCOUNT, 0, 0);						//���� �������� ������ ������ �������, �������
		if (i>1) return -1;
		wchar_t tek[MAX_BUFFER_SIZE];
		SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELITEMS, 1, (LPARAM)&i);					//����� ���������� �������
		SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETTEXT, i, (LPARAM)tek);

		teacher* tek_teach = teacher::s_find_teacher(std::wstring(tek));

		i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_GETSELCOUNT, 0, 0);
		int selItems[MAX_PEOPLES];
		SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_GETSELITEMS, i, (LPARAM)selItems);				//���� �������� ������ ������ ��������
		i--;
		int OK;
		for (; i >= 0; i--){																	//������� �� ����
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_GETTEXT, selItems[i], (LPARAM)tek);
			if (OK != LB_ERR){
				tek_teach->del_classman(std::wstring(tek));
				SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_DELETESTRING, selItems[i], 0);
			}
		}
		view_classman_to_teacher();
		return true;
	}

	bool main_wnd::view_classman_to_teacher()
	{																//����� ������ ����������� ���������
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_GETITEMHEIGHT, 0, 0);					//������� �������
		i--;
		for (; i >= 0; i--)
		{
			SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_DELETESTRING, i, 0);
		}
		
		i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELCOUNT, i, 0);
		if (i != 1) return -1; //���� �������� ������ ������ �������, �� ������� ������ ���������
		
		wchar_t tek[MAX_BUFFER_SIZE];
		SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELITEMS, 1, (LPARAM)&i);					//�������� ����������� �������
		SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETTEXT, i, (LPARAM)tek);
		teacher* tek_t = teacher::s_find_teacher(std::wstring(tek));
		//� ������� ��� ��������� � �������.
		for (auto tek_c : tek_t->m_classmans)
		{
			if (tek_c.second != nullptr)
				SendDlgItemMessage(m_my_hwnd, IDC_MAIN_CLASSMANS, LB_ADDSTRING, 0, (LPARAM)tek_c.second->get_FIO().c_str());
		}
		return true;
	}

	//���������� ��������� ��������
	bool main_wnd::add_classman_to_teacher()
	{																
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELCOUNT, 0, 0);						//������� �������� ��������
		int ii = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETSELCOUNT, 0, 0);						//������� �������� ���������
		int selItemsP[MAX_PEOPLES];
		int selItemsS[MAX_PEOPLES];
		teacher* tek_t;
		wchar_t tek[MAX_BUFFER_SIZE];
		int OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELITEMS, i, (LPARAM)selItemsP);
		if (OK == LB_ERR) return nullptr;
		OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETSELITEMS, ii, (LPARAM)selItemsS);
		if (OK == LB_ERR) return nullptr;
		i--;
		ii--;
		for (; i >= 0; i--)//� ������� ������� ��������� ���� ���������� ���������
		{																	
			SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETTEXT, selItemsP[i], (LPARAM)tek);
			if (tek[0] != 0)
			{
				tek_t = teacher::s_find_teacher(std::wstring(tek));
				for (int i1 = ii; i1 >= 0; i1--)
				{
					OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETTEXT, selItemsS[i1], (LPARAM)tek);
					if (tek[0] != 0 && OK != LB_ERR)
					{
						if (tek_t->find_classman(std::wstring(tek)) == nullptr)
						{
							tek_t->add_classman(std::wstring(tek));
						}
					}
				}
			}
		}
		view_classman_to_teacher();
		
		return true;
	}

	//�������� ��������
	bool main_wnd::del_teacher()
	{																
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELCOUNT, 0, 0);
		int selItems[MAX_PEOPLES];
		wchar_t tek[MAX_BUFFER_SIZE];
		int OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELITEMS, i, (LPARAM)selItems);
		if (OK == LB_ERR)
		{
			return false;
		}
		
		i--;
		for (; i >= 0; i--)
		{
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETTEXT, selItems[i], (LPARAM)tek);
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_DELETESTRING, selItems[i], 0);
			if (tek[0] != 0)
			{
				teacher::s_del_teacher(std::wstring(tek));
			}
			
		}
		view_classman_to_teacher();
		return true;
	}


	//����������� �������
	bool main_wnd::edit_teacher()
	{																
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELCOUNT, 0, 0);					//������� ������� �������� ��������
		int selItems[MAX_PEOPLES];
		wchar_t tek[MAX_BUFFER_SIZE];
		int OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETSELITEMS, i, (LPARAM)selItems);
		if (OK == LB_ERR) return nullptr;
		i--;
		for (; i >= 0; i--)//� ��� ������� �� ��� ��������� ��������������
		{																
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_TEACHERS, LB_GETTEXT, selItems[i], (LPARAM)tek);
			if (tek != nullptr) m_active_teacher = teacher::s_find_teacher(std::wstring(tek));
			if (m_active_teacher != nullptr)
			{

				base_dialog_wnd::ms_new_window = (base_dialog_wnd*)new teacher_dialog(0, this);
				base_dialog_wnd::ms_select_pos = selItems[i];
				DialogBox(ms_this_inst, MAKEINTRESOURCE(IDD_DIALOG1), m_my_hwnd, base_dialog_wnd::s_static_wnd_proc);
			}
		}
		return true;
	}




	//������� ��������
	bool main_wnd::del_classman()
	{														
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETSELCOUNT, 0, 0);				//������� ������� ������� ���������
		int selItems[MAX_PEOPLES];
		wchar_t tek[MAX_BUFFER_SIZE];
		int OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETSELITEMS, i, (LPARAM)selItems);
		if (OK == LB_ERR) return nullptr;
		i--;
		for (; i >= 0; i--)															//� ������� ������� �� ���
		{
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETTEXT, selItems[i], (LPARAM)tek);
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_DELETESTRING, selItems[i], 0);
			if (tek[0] != 0)
			{
				classman::s_del_classman(std::wstring(tek));
			}

		}
		view_classman_to_teacher();														//��������� ������ ��������� �������
		return true;
	}


	//�������������� ���������
	bool main_wnd::edit_classman()
	{														
		int i = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETSELCOUNT, 0, 0);				//���� ������� ��������� ���������,
		int selItems[MAX_PEOPLES];
		wchar_t tek[MAX_BUFFER_SIZE];
		int OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETSELITEMS, i, (LPARAM)selItems);
		if (OK == LB_ERR) return nullptr;
		i--;
		for (; i >= 0; i--)//��������� �� �������������� ������� �� ���
		{																	
			OK = SendDlgItemMessage(m_my_hwnd, IDC_MAIN_ALL_CLASSMANS, LB_GETTEXT, selItems[i], (LPARAM)tek);
			if (tek != nullptr) m_active_classman = classman::s_find_classman(std::wstring(tek));
			if (m_active_classman != nullptr)
			{
				base_dialog_wnd::ms_new_window = (base_dialog_wnd*)new classman_dialog(0, this);
				base_dialog_wnd::ms_select_pos = selItems[i];
				DialogBox(ms_this_inst, MAKEINTRESOURCE(IDD_DIALOG2), m_my_hwnd, base_dialog_wnd::s_static_wnd_proc);
			}
		}
		view_classman_to_teacher();																//� ��������� ������ ��������� ���������� �������
		return true;
	}


}