#include "Camera.h"
#include "fssimplewindow.h"
#include "TimeCurve.h"
#include "DrawFigures.h"
#include "Colors.h"
#include "GraphRenderer.h"


void TestGraphRenderer()
{
	const int NoOfVar = 4;

	DataTable<double> FnTable;
	FnTable.SetNoOfVariables(NoOfVar);

	std::vector<double> row[NoOfVar];

	Variable <double> var[NoOfVar];

	var[1].SetNoOfSteps(2);
	var[2].SetNoOfSteps(2);

	var[1].SetMin(0);
	var[2].SetMin(0);

	var[1].SetMax(10);
	var[2].SetMax(10);

	var[3].SetMin(0);
	var[3].SetMax(10);

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

	GraphRenderer<double> TestFnGraph;
	TestFnGraph.PlotGraph(FnTable, FnTimeCurve, var, 4);
}