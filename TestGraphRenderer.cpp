#include "Camera.h"
#include "fssimplewindow.h"
#include "TimeCurve.h"
#include "DrawFigures.h"
#include "Colors.h"
#include "GraphRenderer.h"


void TestGraphRenderer()
{
	GraphRenderer<double> data;
	
	const int NoOfVar = 4;

	DataTable<double> FnTable;
	FnTable.SetNoOfVariables(NoOfVar);

	std::vector<double> row[NoOfVar];

	Variable <double> var[NoOfVar];

	var[1].SetNoOfSteps(2);
	var[2].SetNoOfSteps(2);

	row[0].push_back(0);
	row[0].push_back(0);
	row[0].push_back(0);
	row[0].push_back(0);	
	FnTable.AppendRow(row[0]);

	row[1].push_back(0);
	row[1].push_back(0);
	row[1].push_back(1);
	row[1].push_back(1);
	FnTable.AppendRow(row[1]);

	row[2].push_back(0);
	row[2].push_back(1);
	row[2].push_back(0);
	row[2].push_back(2);
	FnTable.AppendRow(row[2]);
	
	row[3].push_back(0);
	row[3].push_back(1);
	row[3].push_back(1);
	row[3].push_back(0);
	FnTable.AppendRow(row[3]);

	TimeCurve<double> FnTimeCurve;
	FnTimeCurve.SetNoOfTimeSteps(1);
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

		if (key == FSKEY_ESC)
			break;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Cam.ChangeCameraWithInput(key);
		Cam.SetUpCameraProjection();
		Cam.SetUpCameraTransformation();
		data.PlotFunction(FnTable, FnTimeCurve, 0, 4);
		data.DrawAxis(0, 0, 0, 10, 10, 10, 10, true);
		FsSwapBuffers();
		FsSleep(25);
	}

	FsCloseWindow();
}