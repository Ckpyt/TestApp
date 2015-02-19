#pragma once
#include <list>
#include "stdafx.h"
#include "classman.h"
using namespace std;

namespace test_app
{

	class teacher
	{
		
	public:
		std::wstring m_money;		//��������
		int m_step;					//������ �������
		std::unordered_map <std::wstring, classman*> m_classmans;	//�������� � ������� ��������

		teacher(std::wstring& FIO, wchar_t*Money, int step);
		~teacher();

		std::wstring& get_FIO();
		void set_FIO(std::wstring& FIO);

		//���������� ��������
		bool add_classman(std::wstring& FIO);

		classman* find_classman(std::wstring& FIO);

		//�������� �������� �� ������
		bool del_classman(std::wstring& FIO);


		//����� ������� � ������ ��������
		static teacher* s_find_teacher(std::wstring& FIO);
		
		//�������� �������
		static bool s_del_teacher(std::wstring& FIO);
		//�������� �������� �� ���� ��������.
		static bool s_drop_studen_as_all_teacher(std::wstring& FIO);

		static bool s_rename_classman(std::wstring& old, std::wstring& newnm);

	private:
		//������ ���� ��������������
		static std::unordered_map<std::wstring, std::unique_ptr<teacher>> ms_all_teacher;

		std::wstring m_FIO;			//���

		teacher();
		teacher(teacher*);

		teacher& operator=(teacher& next);
	};

}
