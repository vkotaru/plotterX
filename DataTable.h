#ifndef __DATA_TABLE_H__
#define __DATA_TABLE_H__

#include <vector>
#include "Errors.h"

template <class T>
class DataTable
{
private:
	int NoOfVariables;
	std::vector< std::vector<T> > Data;

public:
	DataTable()
	{
		NoOfVariables = 0;
	};

	~DataTable()
	{
		NoOfVariables = 0;
	}

	void CleanDataTable()
	{
		NoOfVariables = 0;
		Data.clear();
	}

	void SetNoOfVariables(const int NoOfVar)
	{
		if (NoOfVar <= 0)
			throw Error_DataTable_Invalid_Variable_No;

		NoOfVariables = NoOfVar;
	}

	const int GetNoOfVariables() const
	{
		return NoOfVariables;
	}

	const int GetNoOfRows() const
	{
		return Data.size();
	}

	void AppendRow(const std::vector<T> row)
	{
		if (row.size() != NoOfVariables)
			throw Error_DataTable_Invalid_No_Of_Data_Val;

		Data.push_back(row);
	}

	void SetRowAt(const std::vector<T> row, const int index)
	{
		if (index > GetNoOfRows() || index < 0)
			throw Error_DataTable_Invalid_Index;

		auto InsertAt = Data.begin() + index;
		Data.insert(InsertAt, row);
	}

	const std::vector<T> GetRowAt(const int index) const
	{
		if (index >= GetNoOfRows() || index < 0)
			throw Error_DataTable_Invalid_Index;

		return Data.at(index);
	}

	const T GetColumnForRowAt(const int RowIndex, const int ColumnIndex) const
	{
		std::vector<T> row = GetRowAt(RowIndex);
		return row[ColumnIndex];	
	}
};
#endif