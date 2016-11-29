#include "Parser.h"

#include "TestModules.h"
#include "Errors.h"

void TestParser( TestModules &TestModule )
{
	char infix[255] = "x+y+t";
	TestModule.TestMsg("Checking if the Parser computes the function:");
	auto z = Func(1.0,2.0,3.0,infix);
	TestModule.FunctionTest(z == 6);
}