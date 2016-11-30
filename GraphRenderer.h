#ifndef __GRAPH_RENDERER_H__
#define __GRAPH_RENDERER_H__

#include <vector>
#include "fssimplewindow.h"

template <class T>
class GraphRenderer
{
	DrawFigures<T> DrawFig;
	Color FigColor;

	void PlotEqationLine(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfTriangles)
	{
		glBegin(GL_LINES);
		for (int k = 0; k < NoOfTriangles; k++)
		{
			PlotLines(FnTable, FnTimeCurve.GetSurfaceRow(TimeIndex, k));
		}
		glEnd();
	};

	void PlotEquationSurface(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfTriangles)
	{
		glBegin(GL_TRIANGLES);
		for (int k = 0; k < NoOfTriangles; k++)
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

public:
	void PlotFunction(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfTriangles, int NoOfVariables)
	{
		if (NoOfVariables == 3)
			PlotEqationLine(FnTable, FnTimeCurve, TimeIndex, NoOfTriangles);
		else
			PlotEquationSurface(FnTable, FnTimeCurve, TimeIndex, NoOfTriangles);
	}

	void DrawAxis(double Xmin, double Ymin, double Zmin, double Xmax, double Ymax, double Zmax)
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
	}
};
#endif