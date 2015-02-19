#pragma once
#include "stdafx.h"

#include <list>

namespace test_app
{
	class classman
	{
	public:
		static std::unordered_map<std::wstring,std::unique_ptr<classman>> ms_all_classman;	//������ ���� ���������

		SYSTEMTIME m_day_of_brith;										//���� ��������
		bool m_many;													//���������

		classman(std::wstring& FIO, SYSTEMTIME&day_of_brith, bool many);		//�����������
		~classman();													//����������

		std::wstring& get_FIO();
		void set_FIO(std::wstring& FIO);

		static classman* s_find_classman(std::wstring& FIO);
		static bool s_del_classman(std::wstring& FIO);
	private:
		std::wstring m_FIO;												//���

	};

}