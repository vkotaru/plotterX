#include "DataTable.h"

DataTable::DataTable()
{
	NoOfVariables = 0;
}

DataTable::~DataTable()
{
	NoOfVariables = 0;
}

void DataTable::SetNoOfVariables(const int NoOfVar)
{
	if (NoOfVar <= 0)
		throw "Invalid no of variables";

	NoOfVariables = NoOfVar;
}

const int DataTable::GetNoOfVariables() const
{
	return NoOfVariables;
}

const int DataTable::GetNoOfRows() const
{
	return Data.size();
}

void DataTable::AppendRow(const std::vector<double> row)
{
	if (row.size() != NoOfVariables)
		throw "Invalid number of data values!!!";
	
	Data.push_back(row);
}

const std::vector<double> DataTable::GetRowAt(const int index) const
{
	if (index >= GetNoOfRows() || index < 0)
		throw "Invalid Index";

	return Data.at(index);
}

void DataTable::SetRowAt(const std::vector<double> row, const int index)
{
	if (index > GetNoOfRows() || index < 0)
		throw "Invalid Index";
	
	auto InsertAt = Data.begin() + index;
	Data.insert(InsertAt, row);
 }
