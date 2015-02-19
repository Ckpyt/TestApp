#include "stdafx.h"
#include "classman.h"
#include "teacher.h"

namespace test_app
{
	std::unordered_map<std::wstring, std::unique_ptr<classman>> classman::ms_all_classman;

	classman::~classman(){
	}

	classman::classman(std::wstring& FIO, SYSTEMTIME&day_of_brith, bool many)
	{
		this->m_FIO = FIO;
		this->m_day_of_brith = day_of_brith;
		this->m_many = many;
		ms_all_classman[m_FIO] = std::unique_ptr<classman>(this);
	};

	//поиск студента по фамилии
	classman* classman::s_find_classman(std::wstring& FIO)
	{
		return ms_all_classman[FIO].get();
	}

	//удаляем студента
	bool classman::s_del_classman(std::wstring& FIO)
	{
		//удаляем из списков преподавателей
		teacher::s_drop_studen_as_all_teacher(FIO);
		//находим студента
		ms_all_classman.erase(FIO);
		return true;
	}


	std::wstring& classman::get_FIO()
	{
		return m_FIO;
	}

	void classman::set_FIO(std::wstring& FIO)
	{
		//меняем ключ в хранилище
		ms_all_classman[FIO] = move(ms_all_classman[m_FIO]);
		ms_all_classman.erase(m_FIO);

		//меняем ключи для всех учителей
		teacher::s_rename_classman(m_FIO, FIO);

		m_FIO = FIO;

	}

}


