#ifndef __DATA_TABLE_H__
#define __DATA_TABLE_H__

#include<vector>

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

	void SetNoOfVariables(const int NoOfVar)
	{
		if (NoOfVar <= 0)
			throw "Invalid no of variables";

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
			throw "Invalid number of data values!!!";

		Data.push_back(row);
	}

	void SetRowAt(const std::vector<T> row, const int index)
	{
		if (index > GetNoOfRows() || index < 0)
			throw "Invalid Index";

		auto InsertAt = Data.begin() + index;
		Data.insert(InsertAt, row);
	}

	const std::vector<T> GetRowAt(const int index) const
	{
		if (index >= GetNoOfRows() || index < 0)
			throw "Invalid Index";

		return Data.at(index);
	}
};

#endif