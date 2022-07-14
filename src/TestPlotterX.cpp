#include "TestDataTable.cpp"
#include "TestVariable.cpp"
#include "TestFuncEval.cpp"
#include "TestSurface.cpp"
#include "TestTimeCurve.cpp"
#include "TestGraphRenderer.cpp"
#include "TestAllModules.cpp"
#include "TestParser.cpp"

#include "PlotterX.h"

#include "TestModules.h"
#include "Errors.h"


int main()
{
	//try 
	//{
	//	TestModules TestModule;

	//	printf("\n\nTesting the Parser\n");
	//	TestParser(TestModule);

	//	printf("\n\nTesting the DataTable\n");
	//	TestDataTable(TestModule);

	//	printf("\n\nTesting the Variable\n");
	//	TestVariable(TestModule);

	//	printf("\n\nTesting the FunctionEval\n");
	//	TestFuncEval(TestModule);

	//	printf("\n\nTesting the Surface\n");
	//	TestSurface(TestModule);

	//	printf("\n\nTesting the Time Curves\n");
	//	TestTimeCurve(TestModule);

	//	//Can't open 2 windows hence commenting this
	//	//printf("\n\nTesting Graph Renderer\n");
	////	TestGraphRenderer();
	//	
	//	printf("\n\nTesting All Modules Integration\n");
	//	TestModuleintegration();
	//}
	//catch ( int ErrorCode )
	//{
	//	Errors Error;
	//	Error.CatchError(ErrorCode);
	//}

	{

		PlotterX plotterX;
		int Terminate = 0;
		while (Terminate != YES)
		{
			Terminate = plotterX.Run();
		}

	}

	return 0;
}