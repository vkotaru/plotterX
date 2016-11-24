#include <stdio.h>
#include <stdlib.h>
#include "FuncEval.h"

void TestFuncEval()
{
	printf("\nCreating Table\n");
	DataTable <double> TestFnTable;
	
	//Varaibles for x, y , t
	Variable <double> TestVar[4];

	FunctionEval<double> FnEval;
	FnEval.DebugModeOn();
	
	printf("\nCreating Variables\n");
	TestVar[0].SetMin(1);
	TestVar[1].SetMin(1);
	TestVar[2].SetMin(1);

	TestVar[0].SetMax(10);
	TestVar[1].SetMax(10);
	TestVar[2].SetMax(10);


	TestVar[0].SetNoOfSteps(9);
	TestVar[1].SetNoOfSteps(9);
	TestVar[2].SetNoOfSteps(9);

	printf("\n\nEvaluating Function in Debug Mode");

	printf("\n\nTest: no of variable are set: ");
	FnEval.Parser2DataTable(TestFnTable);
	
	if (TestFnTable.GetNoOfVariables() == 4)
		printf("Test Passed\n");
	else
		printf("Test Failed\n");

	printf("\n\nTest: the evaluated values are correct: ");
	FnEval.Evaluate(TestFnTable, TestVar);

	auto lastrow = TestFnTable.GetRowAt(TestFnTable.GetNoOfRows() - 1);

	if (lastrow[3] == 1000.0 && lastrow[2] == 10 && lastrow[1] == 10 && lastrow[0] == 10)
		printf("Test Passed\n");
	else
		printf("Test Failed\n");

	printf("\n\nTest: Check if the Z variable is altered: ");
	if (TestVar[3].GetMax() == 1000 && TestVar[3].GetMin() == 1)
		printf("Test Passed\n");
	else
		printf("Test Failed\n");

	FnEval.DebugModeOff();
}