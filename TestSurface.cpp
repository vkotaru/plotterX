#include "Surface.h"
#include "TestModules.h"

void TestSurface(TestModules &TestModule)
{
	Surface <double> TestSurface;

	TestModule.TestMsg("Adding the time:");
	TestSurface.SetTime(5);
	TestModule.FunctionTest(TestSurface.GetTime() == 5);

	TestModule.TestMsg("Triangulate Points:");
	TestSurface.TriangulatePoints(2, 1,1);
	auto LastSurfaceRow = TestSurface.GetSurfaceRow(1);
	TestModule.FunctionTest(LastSurfaceRow[0] == 3 && LastSurfaceRow[1] == 4 && LastSurfaceRow[2] == 5);
}