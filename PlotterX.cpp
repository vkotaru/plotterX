#include "PlotterX.h"


PlotterX::PlotterX()
{
	UI.Initialize();
	IsPlot = false;
}

PlotterX::~PlotterX()
{
}

int PlotterX::Run()
{
	FsPollDevice();

	int lb, mb, rb, mx, my;
	
	// POLLING
	UI.mouse.MOUSE_EVENT_CATCH = FsGetMouseEvent(lb, mb, rb, mx, my);
	UI.mouse.SetMouseState(lb, mb, rb, mx, my);
	key  = UI.Polling();

	// CLEAR BUFFERS
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// RUN STUFF
	UI.AutoScaleWindow();

	if (WelcomeScreen == 1)
	{
		UI.DisplayGraphics();
		
	}

	if (UI.PlotIcon.GetState() && IsPlot == false )
	{
		WelcomeScreen = 0;
		UI.ValidateInput();
		UI.TransferDataToBackEnd(var, FnParser, InputEquation);
		IsPlot = true;
		TestFunctionalities();
		UI.cam.SetPosXYZ(var[1].GetMin(), var[2].GetMin(), var[3].GetMax() + 10);
		UI.cam.SetEulerAngles(0,-70,0);
		DisplayLists = FnGraph.PlotGraphInitialize(FnTable, FnTimeCurve, var, NO_OF_VARIABLES, 10, true);
		printf("DisplayList done");
	}

	if (IsPlot == true)
	{
		UI.DisplayGraphicsWindow();
		UI.cam.ChangeCameraWithInput(key);

		FnGraph.PlotGraph(*DisplayLists, FnTimeCurve, key);
	}

	UI.DisplayInterface();

	FsSwapBuffers();
	FsSleep(25);

	return 0;
}

void PlotterX::TestFunctionalities()
{
	const int NoOfVar = NO_OF_VARIABLES;
	FnTable.SetNoOfVariables(NoOfVar);
/*
	var[0].SetMin(0.5);
	var[0].SetMax(2);
	var[0].SetNoOfSteps(6);

	var[1].SetMin(0);
	var[1].SetMax(4);
	var[1].SetNoOfSteps(10);

	var[2].SetMin(0);
	var[2].SetMax(4);
	var[2].SetNoOfSteps(10);

	printf("\nSet the Variables");

	FnParser.SetInfix("sin(t*x)+cos(y*t)");

	printf("\nSet the Parser Function");*/

	FnEval.Parser2DataTable(FnTable, NoOfVar);

	FnEval.Evaluate(FnTable, var, FnParser);

	printf("\nEvaluated the Function");

	FnTimeCurve.SetNoOfTimeSteps(var[0].GetNoOfSteps());
	FnTimeCurve.CalculateTimeSurfaces(FnTable, var);

	printf("\nCalculated Time Curves");
}

	





