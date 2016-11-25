#include <stdlib.h>
#include "Variable.h"
#include "TestModules.h"

void TestVariable( TestModules &TestModule )
{
	Variable <double> TestVar;
	
	double Min = rand();
	double Max = rand();
	double Del = rand();

	TestModule.TestMsg("Setting the Min value of variable:");
	TestVar.SetMin(Min);
	TestModule.FunctionTest(TestVar.GetMin() == Min);

	TestModule.TestMsg("Setting the Max value of variable:");
	TestVar.SetMax(Max);
	TestModule.FunctionTest(TestVar.GetMax() == Max);

	TestModule.TestMsg("Setting the Delta of variable:");
	TestVar.SetDelta(Del);
	TestModule.FunctionTest(TestVar.GetDelta() == Del);

	TestModule.TestMsg("Number of steps of variables:");
	TestVar.SetDelta(Del);
	TestModule.FunctionTest(TestVar.GetNoOfSteps() == ceil((Max - Min) / Del));
}