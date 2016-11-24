#include <stdio.h>
#include <stdlib.h>
#include "DataTable.h"
#include "Surface.h"

void TestDataTable()
{
	DataTable<double> FnTable;

	int NoOfVar = 3, i = 0;
	printf("Test: Setting the no of variables:");
	FnTable.SetNoOfVariables(NoOfVar);
	if (FnTable.GetNoOfVariables() == NoOfVar)
		printf("Test Passed\n\n");
	else 
		printf("Test Failed\n\n");

	std::vector<double> row;
	for (i = 0; i < NoOfVar; i++)
		row.push_back(rand());

	printf("Adding row to DataTable\n");

	FnTable.AppendRow( row );
	printf("Test: Is the row added: ");
	if (FnTable.GetNoOfRows() == 1)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test: Is the row added correctly: ");
	auto RetrivedRow = FnTable.GetRowAt(0);
	for (i = 0; i < NoOfVar; i++)
		if (row[i] != RetrivedRow[i])
			break;

	if (i == NoOfVar)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");
}	
