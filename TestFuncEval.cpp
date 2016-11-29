#include <stdio.h>
#include <stdlib.h>
#include "FuncEval.h"

void TestFuncEval( TestModules &TestModule )
{
	DataTable <double> TestFnTable;
	Variable <double> TestVar[4];
	FunctionEval<double> FnEval;
	
	FnEval.DebugModeOn();

	for (int i = 0; i < 3; i++)
	{
		TestVar[i].SetMin(1);
		TestVar[i].SetMax(10);
		TestVar[i].SetNoOfSteps(9);
	}

	TestModule.TestMsg("Set the no of variable:");
	FnEval.Parser2DataTable(TestFnTable, 4);
	TestModule.FunctionTest(TestFnTable.GetNoOfVariables() == 4);

	TestModule.TestMsg("Evaluated values:");
	FnEval.Evaluate(TestFnTable, TestVar);
	auto lastrow = TestFnTable.GetRowAt(TestFnTable.GetNoOfRows() - 1);
	TestModule.FunctionTest(lastrow[3] == 1000.0 && lastrow[2] == 10 && lastrow[1] == 10 && lastrow[0] == 10);

	TestModule.TestMsg("Z variable is altered:");
	TestModule.FunctionTest(TestVar[3].GetMax() == 1000 && TestVar[3].GetMin() == 1);

	FnEval.DebugModeOff();
}