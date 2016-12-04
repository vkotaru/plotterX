#ifndef __GRAPH_RENDERER_H__
#define __GRAPH_RENDERER_H__

#include <vector>
#include <thread>
#include "fssimplewindow.h"

template <class T>
class GraphRenderer
{
	DrawFigures<T> DrawFig;
	Color FigColor;

	void PlotEqationLine(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfRows)
	{
		glBegin(GL_LINES);
		for (int k = 0; k < NoOfRows; k++)
		{
			PlotLines(FnTable, FnTimeCurve.GetSurfaceRow(TimeIndex, k));
		}
		glEnd();
	};

	void PlotEquationSurface(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfRows, Variable<T> Var[])
	{
		glBegin(GL_TRIANGLES);
		for (int k = 0; k < NoOfRows; k++)
		{
			PlotTriangularFace(FnTable, FnTimeCurve.GetSurfaceRow(TimeIndex, k), Var);
		}
		glEnd();
	};

	std::vector<T> ExtractRow(DataTable<T> &FnTable, int RowIndex)
	{
		std::vector<T> Row;

		for (int j = 1; j < 4; j++)
			Row.push_back(FnTable.GetColumnForRowAt(RowIndex, j));

		return Row;
	};

	DataTable<T> ExtractCoords(DataTable<T> &FnTable, std::vector<int> TableIndex)
	{
		DataTable<T> TriangleCoords;
		TriangleCoords.SetNoOfVariables(3);
		for (decltype(TableIndex.size()) i = 0; i < TableIndex.size(); i++)
		{
			TriangleCoords.AppendRow(ExtractRow(FnTable, TableIndex.at(i)));
		}

		return TriangleCoords;
	};

	void PlotTriangularFace(DataTable<T> &FnTable, std::vector<int> TableIndex, Variable<T> Var[])
	{
		DataTable<T> TriangleCoords = ExtractCoords(FnTable, TableIndex);
		double max = Var[3].GetMax();
		double delta = Var[3].GetMax() - Var[3].GetMin();
		float r, g, b, r1, g1, b1, r2, g2, b2;
		double avg = (TriangleCoords.GetRowAt(0).at(2) + TriangleCoords.GetRowAt(1).at(2) + TriangleCoords.GetRowAt(2).at(2)) / 3;

		RainbowColor(r, g, b, TriangleCoords.GetRowAt(0).at(2)/ Var[3].GetMax());
		RainbowColor(r1, g1, b1, TriangleCoords.GetRowAt(1).at(2)/ Var[3].GetMax());
		RainbowColor(r2, g2, b2, TriangleCoords.GetRowAt(2).at(2)/ Var[3].GetMax());


		DrawFig.DrawTriangle3D(
			TriangleCoords.GetRowAt(0),
			TriangleCoords.GetRowAt(1),
			TriangleCoords.GetRowAt(2),
			GL_TRIANGLES,r,g,b,r1,g1,b1,r2,g2,b2
		);
	};
	void RainbowColor(float &r, float &g, float &b, const double t)
	{

		if (t<0)
		{
			r = 0;
			g = 0;
			b = 1;
		}
		else if (1<t)
		{
			r = 1;
			g = 0;
			b = 0;
		}
		else if (t<0.25)
		{
			r = 0;
			b = 1;
			g = t / 0.25;
		}
		else if (t<0.5)
		{
			r = 0;
			g = 1;
			b = 1 - (t - 0.25) / 0.25;
		}
		else if (t<0.75)
		{
			r = (t - 0.5) / 0.25;
			g = 1;
			b = 0;
		}
		else
		{
			r = 1;
			g = 1 - (t - 0.75) / 0.25;
			b = 0;
		}
	}

	void PlotLines(DataTable<T> &FnTable, std::vector<int> TableIndex)
	{
		FigColor.SetAndChangeColor(0, 0, 255, 255);

		DataTable<T> TriangleCoords = ExtractCoords(FnTable, TableIndex);

		DrawFig.DrawLines3D(
			TriangleCoords.GetRowAt(0),
			TriangleCoords.GetRowAt(1),
			GL_LINES
		);
	};

	void GenerateXYMesh(double Xmin, double Ymin, double Zmin, double Xmax, double Ymax, double Zmax, int NoOfDivisions)
	{
		FigColor.SetAndChangeColor(0, 0, 0, 255);

		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0xf0f0);
		double deltaX = (Xmax - Xmin)/ NoOfDivisions;
		double deltaY = (Ymax - Ymin)/ NoOfDivisions;
		for (int i = 1; i < NoOfDivisions; i++)
		{
			glBegin(GL_LINES);
			DrawFig.DrawLines3D(Xmin, Ymin+i*deltaY, Zmin, Xmax, Ymin + i*deltaY, Zmin, GL_LINES);
			DrawFig.DrawLines3D(Xmin + i*deltaX, Ymin, Zmin, Xmin + i*deltaX, Ymax, Zmin, GL_LINES);
			glEnd();
		}
		glDisable(GL_LINE_STIPPLE);
	};

	void PlotFunction(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfVariables, Variable<T> Var[])
	{
		int NoOfRows = FnTimeCurve.GetNoOfSurfaceRowsForTimeIndex(TimeIndex);

		if (NoOfVariables == 3)
			PlotEqationLine(FnTable, FnTimeCurve, TimeIndex, NoOfRows);
		else
			PlotEquationSurface(FnTable, FnTimeCurve, TimeIndex, NoOfRows,Var);
	};

	void DrawAxis(double Xmin, double Ymin, double Zmin, double Xmax, double Ymax, double Zmax, int NoOfDivisions, bool DrawMesh)
	{

		FigColor.SetAndChangeColor(0, 0, 0, 255);
		glBegin(GL_LINES);
		DrawFig.DrawLines3D(Xmin, Ymin, Zmin, Xmax, Ymin, Zmin, GL_LINES);
		DrawFig.DrawLines3D(Xmin, Ymin, Zmin, Xmin, Ymax, Zmin, GL_LINES);
		DrawFig.DrawLines3D(Xmin, Ymin, Zmin, Xmin, Ymin, Zmax, GL_LINES);
		glEnd();

		char *CoordinateMarkings = new char[255];
		sprintf(CoordinateMarkings, "%lf %lf %lf\0", Xmin, Ymin, Zmin);
		DrawFig.WriteMsgAtXYZ(Xmin, Ymin, Zmin, CoordinateMarkings);

		sprintf(CoordinateMarkings, "%lf X_axis\0", Xmax);
		DrawFig.WriteMsgAtXYZ(Xmax, Ymin, Zmin, CoordinateMarkings);

		sprintf(CoordinateMarkings, "%lf Y_axis\0", Ymax);
		DrawFig.WriteMsgAtXYZ(Xmin, Ymax, Zmin, CoordinateMarkings);

		sprintf(CoordinateMarkings, "%lf Z_axis\0", Zmax);
		DrawFig.WriteMsgAtXYZ(Xmin, Ymin, Zmax, CoordinateMarkings);

		double deltaX = (Xmax - Xmin) / NoOfDivisions;
		double deltaY = (Ymax - Ymin) / NoOfDivisions;
		double deltaZ = (Zmax - Zmin) / NoOfDivisions;

		for (int i = 1; i < NoOfDivisions; i++)
		{
			sprintf(CoordinateMarkings, "%lf \0", Xmin + i*deltaX);
			DrawFig.WriteMsgAtXYZ(Xmin + i*deltaX, Ymin, Zmin, CoordinateMarkings);

			sprintf(CoordinateMarkings, "%lf \0", Ymin + i*deltaY);
			DrawFig.WriteMsgAtXYZ(Xmin, Ymin + i*deltaY, Zmin, CoordinateMarkings);

			sprintf(CoordinateMarkings, "%lf \0", Zmin + i*deltaZ);
			DrawFig.WriteMsgAtXYZ(Xmin, Ymin, Zmin + i*deltaZ, CoordinateMarkings);
		}

		if (DrawMesh)
			GenerateXYMesh(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax, NoOfDivisions);
	};

	void GenerateTimeIndexDisplayList(GLuint &DisplayLists, int TimeIndex, DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, Variable<T> Var[], int NoOfVariables, int NoOfDivisionsForAxis, bool DrawMeshOnXYPlane)
	{
		printf("\nGenerating List %d of %d", TimeIndex + 1, FnTimeCurve.GetNoOfTimeSteps());
		glNewList(DisplayLists + TimeIndex, GL_COMPILE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		PlotFunction(FnTable, FnTimeCurve, TimeIndex, NoOfVariables,Var);
		DrawAxis(Var[1].GetMin(), Var[2].GetMin(), Var[3].GetMin(), Var[1].GetMax(), Var[2].GetMax(), Var[3].GetMax(), NoOfDivisionsForAxis, DrawMeshOnXYPlane);
		glEndList();
		printf("\nGenerated List %d of %d", TimeIndex + 1, FnTimeCurve.GetNoOfTimeSteps());
	};

	void GenerateGLLists(GLuint &DisplayLists, DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, Variable<T> Var[], int NoOfVariables, int NoOfDivisionsForAxis, bool DrawMeshOnXYPlane)
	{
//		std::vector<std::thread> DisplayListThread;
//		for (int TimeIndex = 0; TimeIndex < FnTimeCurve.GetNoOfTimeSteps(); TimeIndex++)
//		{
//			DisplayListThread.push_back(std::thread( &GraphRenderer<T>::GenerateTimeIndexDisplayList, this, DisplayLists, TimeIndex, FnTable, FnTimeCurve, Var, NoOfVariables, NoOfDivisionsForAxis, DrawMeshOnXYPlane));
//		}
//
//		for (int TimeIndex = 0; TimeIndex < FnTimeCurve.GetNoOfTimeSteps(); TimeIndex++)
//		{
//			DisplayListThread.at(TimeIndex).join();
//		}
//
//		DisplayListThread.clear();

		for (int TimeIndex = 0; TimeIndex < FnTimeCurve.GetNoOfTimeSteps(); TimeIndex++)
		{
			GenerateTimeIndexDisplayList(DisplayLists, TimeIndex, FnTable, FnTimeCurve, Var, NoOfVariables, NoOfDivisionsForAxis, DrawMeshOnXYPlane);
		}
	};

public:

	void PlotGraph(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, Variable<T> Var[],int NoOfVariables, int NoOfDivisionsForAxis = 10, bool DrawMeshOnXYPlane = true, double Speed = 1)
	{
		Camera Cam;
		if ( !FsCheckWindowOpen() )
			FsOpenWindow(0, 0, 800, 600, 1);

		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);

		Cam.SetPosXYZ(Var[1].GetMin(), Var[2].GetMin(), Var[3].GetMax() + 10);

		GLuint DisplayLists = glGenLists(FnTimeCurve.GetNoOfTimeSteps());
		GenerateGLLists(DisplayLists, FnTable, FnTimeCurve, Var, NoOfVariables, NoOfDivisionsForAxis, DrawMeshOnXYPlane);

		double Counter = 0;

		for (int TimeIndex = 0, key = FsInkey(); key != FSKEY_ESC; Counter += Speed)
		{
			FsPollDevice();
			key = FsInkey();

			Cam.ChangeCameraWithInput(key);
			Cam.SetUpCameraProjection();
			Cam.SetUpCameraTransformation();
			glCallList(DisplayLists + TimeIndex);
			FsSwapBuffers();
			
			if (Counter >= 100)
			{
				if (++TimeIndex >= FnTimeCurve.GetNoOfTimeSteps())
					TimeIndex = 0;
				Counter = 0;
			}

			if (key == FSKEY_UP)
				Speed++;

			if (key == FSKEY_DOWN)
				Speed--;

			FsSleep(10);
		};
	};

	void CloseGraphics()
	{
		FsCloseWindow();
	};
};
#endif