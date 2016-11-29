#include "Parser.h"

#include "TestModules.h"
#include "Errors.h"

void TestParser( TestModules &TestModule )
{
	Parser FnParser;
	FnParser.SetInfix("x+y+t");
	TestModule.TestMsg("Checking if the Parser computes the function:");
	auto z = FnParser.Evaluate(1.0,2.0,3.0);
	TestModule.FunctionTest(z == 6);
}