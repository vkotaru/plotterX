#ifndef __GRAPH_RENDERER_H__
#define __GRAPH_RENDERER_H__

#include <vector>
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

	void PlotEquationSurface(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfRows)
	{
		glBegin(GL_TRIANGLES);
		for (int k = 0; k < NoOfRows; k++)
		{
			PlotTriangularFace(FnTable, FnTimeCurve.GetSurfaceRow(TimeIndex, k));
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

	void PlotTriangularFace(DataTable<T> &FnTable, std::vector<int> TableIndex)
	{
		FigColor.SetAndChangeColor(0, 0, 255, 255);

		DataTable<T> TriangleCoords = ExtractCoords(FnTable, TableIndex);

		DrawFig.DrawTriangle3D(
			TriangleCoords.GetRowAt(0),
			TriangleCoords.GetRowAt(1),
			TriangleCoords.GetRowAt(2),
			GL_TRIANGLES
		);
	};

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

		for (int i = 1; i < NoOfDivisions; i++)
		{
			glBegin(GL_LINES);
			DrawFig.DrawLines3D(Xmin, Ymax*i / NoOfDivisions, Zmin, Xmax, Ymax*i / NoOfDivisions, Zmin, GL_LINES);
			DrawFig.DrawLines3D(Xmax*i / NoOfDivisions, Ymin, Zmin, Xmax*i / NoOfDivisions, Ymax, Zmin, GL_LINES);
			glEnd();
		}
		glDisable(GL_LINE_STIPPLE);
	};

	void PlotFunction(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfVariables)
	{
		int NoOfRows = FnTimeCurve.GetNoOfSurfaceRowsForTimeIndex(TimeIndex);

		if (NoOfVariables == 3)
			PlotEqationLine(FnTable, FnTimeCurve, TimeIndex, NoOfRows);
		else
			PlotEquationSurface(FnTable, FnTimeCurve, TimeIndex, NoOfRows);
	};

	void DrawAxis(double Xmin, double Ymin, double Zmin, double Xmax, double Ymax, double Zmax, int NoOfDivisions = 10, bool DrawMesh = false)
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


		for (int i = 1; i < NoOfDivisions; i++)
		{
			sprintf(CoordinateMarkings, "%lf \0", Xmax*i / NoOfDivisions);
			DrawFig.WriteMsgAtXYZ(Xmax*i / NoOfDivisions, Ymin, Zmin, CoordinateMarkings);

			sprintf(CoordinateMarkings, "%lf \0", Ymax*i / NoOfDivisions);
			DrawFig.WriteMsgAtXYZ(Xmin, Ymax*i / NoOfDivisions, Zmin, CoordinateMarkings);

			sprintf(CoordinateMarkings, "%lf \0", Zmax*i / NoOfDivisions);
			DrawFig.WriteMsgAtXYZ(Xmin, Ymin, Zmax*i / NoOfDivisions, CoordinateMarkings);
		}

		if (DrawMesh)
			GenerateXYMesh(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax, NoOfDivisions);
	};

public:
	void PlotGraph(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, Variable<T> Var[],int NoOfVariables, int NoOfDivisionsForAxis = 10, bool DrawMeshOnXYPlane = false)
	{
		Camera Cam;

		if ( !FsCheckWindowOpen() )
			FsOpenWindow(0, 0, 800, 600, 1);

		glEnable(GL_DEPTH_TEST);
		Cam.SetPosXYZ(Var[1].GetMin(), Var[2].GetMin(), Var[3].GetMax() + 10);

		int key = FsInkey();

		int PrevTimeIndex = -1;

		GLuint index = glGenLists(1);
		
		for (int TimeIndex = 0, Counter = 0; key != FSKEY_ESC; Counter++)
		{
			FsPollDevice();
			key = FsInkey();
			Cam.ChangeCameraWithInput(key);
			Cam.SetUpCameraProjection();
			Cam.SetUpCameraTransformation();

			if (PrevTimeIndex != TimeIndex)
			{
				glNewList(index, GL_COMPILE);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				PlotFunction(FnTable, FnTimeCurve, TimeIndex, 4);
				DrawAxis(Var[1].GetMin(), Var[2].GetMin(), Var[3].GetMin(), Var[1].GetMax(), Var[2].GetMax(), Var[3].GetMax(), 10, true);

				glEndList();				
				glCallList(index);
				
				PrevTimeIndex = TimeIndex;
			}
			else
			{
				glCallList(index);

			};
			FsSwapBuffers();
			
			if (Counter >= 50)
			{
				if (++TimeIndex >= FnTimeCurve.GetNoOfTimeSteps())
					TimeIndex = 0;
				Counter = 0;
			}
		};
	};

	void CloseGraphics()
	{
		FsCloseWindow();
	};
};
#endif