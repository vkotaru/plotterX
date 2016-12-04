#ifndef __PLOTTER_X_H__
#define __PLOTTER_X_H__

#include "Camera.h"
#include "fssimplewindow.h"
#include "TimeCurve.h"
#include "DrawFigures.h"
#include "Colors.h"
#include "GraphRenderer.h"
#include "FuncEval.h"
#include "DataTable.h"

#include "./UI/UserInterface.h"

class PlotterX
{
private:
	UserInterface UI;

	GraphRenderer<double> FnGraph;
	DataTable<double> FnTable;
	Variable <double> var[NO_OF_VARIABLES];
	Parser FnParser;
	FunctionEval<double> FnEval;
	TimeCurve<double> FnTimeCurve;
	bool IsPlot;
	GLuint *DisplayLists;

	char InputEquation[100];
	
	// Flags
	int WelcomeScreen = 1;
	int PlottingStuff = 0;

	int key;
public:
	PlotterX();
	~PlotterX();

	void TestFunctionalities();
	int Run();

};









#endif