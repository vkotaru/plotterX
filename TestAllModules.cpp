#include "Camera.h"
#include "fssimplewindow.h"
#include "TimeCurve.h"
#include "DrawFigures.h"
#include "Colors.h"
#include "GraphRenderer.h"
#include "FuncEval.h"

void TestModuleintegration()
{
	const int NoOfVar = 4;
	GraphRenderer<double> data;

	DataTable<double> FnTable;
	FnTable.SetNoOfVariables(NoOfVar);

	Variable <double> var[NoOfVar];
	var[0].SetMin(0);
	var[0].SetMax(4);
	var[0].SetNoOfSteps(5);

	var[1].SetMin(0);
	var[1].SetMax(4);
	var[1].SetNoOfSteps(5);

	var[2].SetMin(0);
	var[2].SetMax(4);
	var[2].SetNoOfSteps(5);

	Parser FnParser;
	FnParser.SetInfix("x+y");

	FunctionEval<double> FnEval;
	FnEval.Parser2DataTable(FnTable, NoOfVar);
	
	FnEval.Evaluate(FnTable, var, FnParser);

	TimeCurve<double> FnTimeCurve;
	FnTimeCurve.SetNoOfTimeSteps(var[0].GetNoOfSteps());
	FnTimeCurve.CalculateTimeSurfaces(FnTable, var);

	Camera Cam;

	FsOpenWindow(0, 0, 800, 600, 1);
	glEnable(GL_DEPTH_TEST);
	Cam.SetPosXYZ(0, 0, 10);
	Cam.SetEulerAngles(0, 0, 0);

	for (;;)
	{
		FsPollDevice();

		int key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		Cam.ChangeCameraWithInput(key);
		Cam.SetUpCameraProjection();
		Cam.SetUpCameraTransformation();

		data.PlotFunction(FnTable, FnTimeCurve, 0, 4);
		data.DrawAxis(var[1].GetMin(), var[2].GetMin(), var[3].GetMin(), var[1].GetMax(), var[2].GetMax(), var[3].GetMax(), 10, true);
		FsSwapBuffers();
	}
	FsCloseWindow();
}