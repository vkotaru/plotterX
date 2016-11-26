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

	FsOpenWindow(0, 0, 800, 600, 0);
	glEnable(GL_DEPTH_TEST);

	float h = 0.0, p = 0.0;
	int zoom=-10,pan=0;
	for (;;)
	{
		FsPollDevice();

		int key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}
		if (FSKEY_UP == key)
		{
			zoom++;
		}
		if (FSKEY_DOWN == key)
		{
			zoom--;
		}
		if (FSKEY_LEFT == key)
		{
			pan++;
		}
		if (FSKEY_RIGHT == key)
		{
			pan--;
		}
		if (FSKEY_D == key)
		{
			h--;
		}
		if (FSKEY_A == key)
		{
			h++;
		}
		if (FSKEY_W == key)
		{
			p--;
		}
		if (FSKEY_S == key)
		{
			p++;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int wid, hei;
		FsGetWindowSize(wid, hei);

		double aspect = (double)wid / (double)hei;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, aspect, 0.1, 100.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(pan, 0, zoom);

		glRotatef(h, 0, 1, 0);
		glRotatef(p, 1, 0, 0);

		data.PlotEquationSurface(FnTable, FnTimeCurve, 0, NoOfTrianglesPerTime);
		data.DrawAxis(0,0,0,10,10,10);

		glFlush();
		FsSleep(25);
	}
	FsCloseWindow();
}