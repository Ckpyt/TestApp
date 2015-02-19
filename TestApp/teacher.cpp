#include "stdafx.h"
#include "teacher.h"
#include "classman.h"

namespace test_app
{
	std::unordered_map<std::wstring, std::unique_ptr<teacher>> teacher::ms_all_teacher;

	//запрещенные конструкторы
	teacher::teacher(){}
	teacher::teacher(teacher*next){}

	teacher& teacher::operator=(teacher& next) { return next; }

	teacher::teacher(std::wstring& FIO, wchar_t*Money, int step)
	{
		this->m_FIO = FIO;
		this->m_money = Money;
		this->m_step = step;
		this->m_classmans.clear();
		ms_all_teacher[FIO] = unique_ptr<teacher>(this);
	}

	teacher::~teacher()
	{
		m_classmans.clear();
	}

	bool teacher::add_classman(std::wstring& FIO)
	{
		classman* tek = classman::s_find_classman(FIO);
		if (tek == nullptr) return false;
		m_classmans[FIO] = tek;
		return true;
	}

	bool teacher::del_classman(std::wstring& FIO)
	{
		m_classmans.erase(FIO);
		return true;
	}

	classman* teacher::find_classman(std::wstring& FIO)
	{
		return m_classmans[FIO];
	}

	teacher* teacher::s_find_teacher(std::wstring& FIO)
	{
		return ms_all_teacher[FIO].get();
	}

	bool teacher::s_del_teacher(std::wstring& FIO)
	{
		ms_all_teacher.erase(FIO);
		return true;
	};

	bool teacher::s_drop_studen_as_all_teacher(std::wstring& FIO)
	{
		for (auto& tek_teacher : ms_all_teacher)
		{
			tek_teacher.second->del_classman(FIO);
		}
		return true;
	}

	bool teacher::s_rename_classman(std::wstring& old, std::wstring& newnm)
	{
		for (auto& tek_teacher : ms_all_teacher)
		{
			if (tek_teacher.second->m_classmans[old] != nullptr)
			{
				tek_teacher.second->m_classmans[newnm] = tek_teacher.second->m_classmans[old];
				tek_teacher.second->m_classmans.erase(old);
			}
		}
		return true;
	}

	std::wstring& teacher::get_FIO()
	{
		return m_FIO;
	}

	void teacher::set_FIO(std::wstring& FIO)
	{
		ms_all_teacher[FIO] = move(ms_all_teacher[m_FIO]);
		ms_all_teacher.erase(m_FIO);
		m_FIO = FIO;
	}
}