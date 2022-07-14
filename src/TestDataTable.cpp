#include <stdio.h>
#include <stdlib.h>
#include "DataTable.h"
#include "TestModules.h"

void TestDataTable( TestModules &TestModule )
{
	DataTable<double> FnTable;

	int NoOfVar = 3, i = 0;

	TestModule.TestMsg("Setting the no of variables:");
	FnTable.SetNoOfVariables(NoOfVar);
	TestModule.FunctionTest(FnTable.GetNoOfVariables() == NoOfVar);
	
	std::vector<double> row;
	for (i = 0; i < NoOfVar; i++)
		row.push_back(rand());

	TestModule.TestMsg("Setting the no of variables:");
	FnTable.SetNoOfVariables(NoOfVar);
	TestModule.FunctionTest(FnTable.GetNoOfVariables() == NoOfVar);

	TestModule.TestMsg("Adding row to DataTable:");
	FnTable.AppendRow( row );
	TestModule.FunctionTest(FnTable.GetNoOfRows() == 1);

	TestModule.TestMsg("Data Consistency:");
	auto RetrivedRow = FnTable.GetRowAt(0);
	for (i = 0; i < NoOfVar; i++)
		if (row[i] != RetrivedRow[i])
			break;
	TestModule.FunctionTest(i == NoOfVar);
}	
