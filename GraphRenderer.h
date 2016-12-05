#ifndef __GRAPH_RENDERER_H__
#define __GRAPH_RENDERER_H__

#include <vector>
#include <thread>
#include "fssimplewindow.h"

#include "./UI/UserInterface.h"

template <class T>
class GraphRenderer
{
	DrawFigures<T> DrawFig;
	Color FigColor;

	void PlotEqationLine(DataTable<T> &FnTable, TimeCurve<T> &FnTimeCurve, int TimeIndex, int NoOfRows)
	{
		glBegin(GL_LINES);
		for (int k = 0; k < NoOfRows; k++)
		{
			PlotLines(FnTable, FnTimeCurve.GetSurfaceRow(TimeIndex, k));
		}
		glEnd();
	};

	void PlotEquationSurface(DataTable<T> &FnTable, TimeCurve<T> &FnTimeCurve, int TimeIndex, int NoOfRows, Variable<T> Var[])
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

		DrawFig.DrawTriangle3D(
			TriangleCoords.GetRowAt(0),
			TriangleCoords.GetRowAt(1),
			TriangleCoords.GetRowAt(2),
			true, Var[3].GetMin(), Var[3].GetMax()
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

	void PlotFunction(DataTable<T> &FnTable, TimeCurve<T> &FnTimeCurve, int TimeIndex, int NoOfVariables, Variable<T> Var[])
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

	void GenerateTimeIndexDisplayList(GLuint &DisplayLists, int TimeIndex, DataTable<T> &FnTable, TimeCurve<T> &FnTimeCurve, Variable<T> Var[], int NoOfVariables, int NoOfDivisionsForAxis, bool DrawMeshOnXYPlane)
	{
		printf("\nGenerating List %d of %d", TimeIndex + 1, FnTimeCurve.GetNoOfTimeSteps());
		glNewList(DisplayLists + TimeIndex, GL_COMPILE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		PlotFunction(FnTable, FnTimeCurve, TimeIndex, NoOfVariables,Var);
		DrawAxis(Var[1].GetMin(), Var[2].GetMin(), Var[3].GetMin(), Var[1].GetMax(), Var[2].GetMax(), Var[3].GetMax(), NoOfDivisionsForAxis, DrawMeshOnXYPlane);
		glEndList();
		printf("\nGenerated List %d of %d", TimeIndex + 1, FnTimeCurve.GetNoOfTimeSteps());
	};

	void GenerateGLLists(GLuint &DisplayLists, DataTable<T> &FnTable, TimeCurve<T> &FnTimeCurve, Variable<T> Var[], int NoOfVariables, int NoOfDivisionsForAxis, bool DrawMeshOnXYPlane)
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

	GLuint * PlotGraphInitialize(DataTable<T> &FnTable, TimeCurve<T> &FnTimeCurve, Variable<T> Var[], int NoOfVariables, int NoOfDivisionsForAxis = 10, bool DrawMeshOnXYPlane = true)
	{
		static GLuint DisplayLists = glGenLists(FnTimeCurve.GetNoOfTimeSteps());
		GenerateGLLists(DisplayLists, FnTable, FnTimeCurve, Var, NoOfVariables, NoOfDivisionsForAxis, DrawMeshOnXYPlane);
		//double Counter = 0;

		return &DisplayLists;
	}

	void PlotGraph(GLuint &DisplayLists, TimeCurve<T> &FnTimeCurve, int key)
	{
//		Camera Cam;
//		if ( !FsCheckWindowOpen() )
//			FsOpenWindow(0, 0, 800, 600, 1);

//		glEnable(GL_DEPTH_TEST);
//		Cam.SetPosXYZ(Var[1].GetMin(), Var[2].GetMin(), Var[3].GetMax() + 10);
//		Cam.SetEulerAngles(0,-70,0);

//		GLuint DisplayLists = glGenLists(FnTimeCurve.GetNoOfTimeSteps());
//		GenerateGLLists(DisplayLists, FnTable, FnTimeCurve, Var, NoOfVariables, NoOfDivisionsForAxis, DrawMeshOnXYPlane);

//		double Counter = 0;
		static int TimeIndex = 0;
		static double Counter = 0;
		static double Speed = 1;
		Counter += Speed;
		//for (int TimeIndex = 0, key = FsInkey(); key != FSKEY_ESC; Counter += Speed)
		{
			//FsPollDevice();
//			Cam.ChangeCameraWithInput(key);
//			Cam.SetUpCameraProjection();
//			Cam.SetUpCameraTransformation();
			glCallList(DisplayLists + TimeIndex);
			//FsSwapBuffers();
			
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
			//if (key == FSKEY_ESC)
				//break;
			//FsSleep(10);
		};
	};

	void CloseGraphics()
	{
		FsCloseWindow();
	};
};
#endif