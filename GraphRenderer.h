#ifndef __GRAPH_RENDERER_H__
#define __GRAPH_RENDERER_H__

#include <vector>
#include "fssimplewindow.h"

template <class T>
class GraphRenderer
{
	DrawFigures<T> DrawFig;
	Color FigColor;

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

public:
	void PlotEquationSurface(DataTable<T> &FnTable, TimeCurve<T> FnTimeCurve, int TimeIndex, int NoOfTriangles)
	{
		for (int k = 0; k < NoOfTriangles; k++)
		{
			PlotTriangularFace(FnTable, FnTimeCurve.GetSurfaceRow(TimeIndex, k));
		}
	};

	void DrawAxis(double Xmin, double Ymin, double Zmin, double Xmax, double Ymax, double Zmax)
	{

		FigColor.SetAndChangeColor(0, 0, 0, 255);
		DrawFig.DrawLines3D(Xmin, Ymin, Zmin, Xmax, Ymin, Zmin, GL_LINES);
		DrawFig.DrawLines3D(Xmin, Ymin, Zmin, Xmin, Ymax, Zmin, GL_LINES);
		DrawFig.DrawLines3D(Xmin, Ymin, Zmin, Xmin, Ymin, Zmax, GL_LINES);

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