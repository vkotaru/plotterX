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
	var[0].SetMax(1);
	var[0].SetNoOfSteps(2);

	var[1].SetMin(0);
	var[1].SetMax(4);
	var[1].SetNoOfSteps(50);

	var[2].SetMin(0);
	var[2].SetMax(4);
	var[2].SetNoOfSteps(50);

	printf("\nSet the Variables");

	Parser FnParser;
	FnParser.SetInfix("sin(t*x)+cos(y*t)");

	printf("\nSet the Parser Function");

	FunctionEval<double> FnEval;
	FnEval.Parser2DataTable(FnTable, NoOfVar);

	FnEval.Evaluate(FnTable, var, FnParser);

	printf("\nEvaluated the Function");

	TimeCurve<double> FnTimeCurve;
	FnTimeCurve.SetNoOfTimeSteps(var[0].GetNoOfSteps());
	FnTimeCurve.CalculateTimeSurfaces(FnTable, var);

	printf("\nCalculated Time Curves");

	FnGraph.PlotGraph(FnTable, FnTimeCurve, var, NoOfVar);
}