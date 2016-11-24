#include "TestDataTable.cpp"
#include "TestVariable.cpp"
#include "TestFuncEval.cpp"

int main()
{
	printf("Testing the DataTable\n");
	TestDataTable();

	printf("\n\nTesting the Variable\n");
	TestVariable();

	printf("\n\nTesting the FunctionEval\n");
	TestFuncEval();

	return 0;
}