#include <math.h>
#include "TimeCurve.h"
#include "TestModules.h"

void TestTimeCurve(TestModules &TestModule)
{
	TimeCurve <double> TestTimeCurve;

	TestModule.TestMsg("Adding the Time Steps:");
	TestTimeCurve.SetNoOfTimeSteps(2);
	TestModule.FunctionTest(TestTimeCurve.GetNoOfTimeSteps() == 2);

	DataTable<double> TestFnTable;
	int NoOfVar = 4, NoOfRow = 6;
	TestFnTable.SetNoOfVariables(NoOfVar);

	for (int j = 0; j < NoOfRow; j++)
	{
		std::vector<double> row;

		row.push_back(fmax(3, fmin(4, j)));
		for (int i = 1; i < NoOfVar; i++)
			row.push_back(j);

		TestFnTable.AppendRow(row);
	}

	TestModule.TestMsg("Checking the Time Surfaces:");
	TestTimeCurve.CalculateTimeSurfaces(TestFnTable);
	auto row1 = TestTimeCurve.GetSurfaceRow(0, 2);
	TestModule.FunctionTest(row1[0] == 3 && row1[1] == 3 && row1[2] == 4);
}