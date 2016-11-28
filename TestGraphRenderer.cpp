#include "Camera.h"
#include "fssimplewindow.h"
#include "TimeCurve.h"
#include "DrawFigures.h"
#include "Colors.h"
#include "GraphRenderer.h"


void TestGraphRenderer()
{
	GraphRenderer<double> data;
	
	DataTable<double> FnTable;
	FnTable.SetNoOfVariables(4);

	std::vector<double> row[4];

	row[0].push_back(0);
	row[0].push_back(0);
	row[0].push_back(0);
	row[0].push_back(0);	
	FnTable.AppendRow(row[0]);

	row[1].push_back(0);
	row[1].push_back(1);
	row[1].push_back(1);
	row[1].push_back(0);
	FnTable.AppendRow(row[1]);

	row[2].push_back(0);
	row[2].push_back(1);
	row[2].push_back(-1);
	row[2].push_back(0);
	FnTable.AppendRow(row[2]);
	
	row[3].push_back(0);
	row[3].push_back(0);
	row[3].push_back(0);
	row[3].push_back(2);
	FnTable.AppendRow(row[3]);

	TimeCurve<double> FnTimeCurve;
	FnTimeCurve.SetNoOfTimeSteps(1);
	FnTimeCurve.CalculateTimeSurfaces(FnTable);

	int NoOfTrianglesPerTime = FnTable.GetNoOfRows() / FnTimeCurve.GetNoOfTimeSteps() - 2;

	Camera Cam;

	FsOpenWindow(0, 0, 800, 600, 1);
	glEnable(GL_DEPTH_TEST);

	float h = 0.0, p = 0.0;
	Cam.SetPosXYZ(0, 0, 10);
	Cam.SetEulerAngles(0, 0, 0);
	int zoom=-10,pan=0;
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
		
		data.PlotEquationSurface(FnTable, FnTimeCurve, 0, NoOfTrianglesPerTime);
		data.DrawAxis(0,0,0,10,10,10);

		//glFlush();
		FsSwapBuffers();
		FsSleep(25);
	}
	FsCloseWindow();
}