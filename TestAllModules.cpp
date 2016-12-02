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
	GraphRenderer<double> FnGraph;

	DataTable<double> FnTable;
	FnTable.SetNoOfVariables(NoOfVar);

	Variable <double> var[NoOfVar];
	var[0].SetMin(0);
	var[0].SetMax(4);
	var[0].SetNoOfSteps(20);

	var[1].SetMin(0);
	var[1].SetMax(4);
	var[1].SetNoOfSteps(9);

	var[2].SetMin(0);
	var[2].SetMax(1);
	var[2].SetNoOfSteps(2);

	Parser FnParser;
	FnParser.SetInfix("sin(t*x)+cos(y*t)");

	FunctionEval<double> FnEval;
	FnEval.Parser2DataTable(FnTable, NoOfVar);
	
	FnEval.Evaluate(FnTable, var, FnParser);

	TimeCurve<double> FnTimeCurve;
	FnTimeCurve.SetNoOfTimeSteps(var[0].GetNoOfSteps());
	FnTimeCurve.CalculateTimeSurfaces(FnTable, var);

	FnGraph.PlotGraph(FnTable, FnTimeCurve, var, NoOfVar);
}