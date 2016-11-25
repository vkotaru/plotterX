#include "TestDataTable.cpp"
#include "TestVariable.cpp"
#include "TestFuncEval.cpp"
#include "TestSurface.cpp"
#include "TestTimeCurve.cpp"

#include "TestModules.h"

int main()
{
	TestModules TestModule;

	printf("Testing the DataTable\n");
	TestDataTable(TestModule);

	printf("\n\nTesting the Variable\n");
	TestVariable(TestModule);

	printf("\n\nTesting the FunctionEval\n");
	TestFuncEval(TestModule);

	printf("\n\nTesting the Surface\n");
	TestSurface(TestModule);

	printf("\n\nTesting the Time Curves\n");
	TestTimeCurve(TestModule);

	return 0;
}