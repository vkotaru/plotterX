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

	if (UI.PlotIcon.GetState() )
	{
		UI.PlotIcon.SetState(false);
		WelcomeScreen = 0;
		UI.ValidateInput();
		UI.TransferDataToBackEnd(var, FnParser, InputEquation);
		var[3].InitializeToZero();
		IsPlot = true;
		TestFunctionalities();
		UI.cam.SetPosXYZ(var[1].GetMin(), var[2].GetMin(), var[3].GetMax() + 10);
		UI.cam.SetEulerAngles(0,-70,0);
		delete DisplayLists;
		DisplayLists = nullptr;
		DisplayLists = new GLuint;
		*DisplayLists = glGenLists(FnTimeCurve.GetNoOfTimeSteps());
		FnGraph.PlotGraphInitialize(*DisplayLists, FnTable, FnTimeCurve, var, NO_OF_VARIABLES, 10, true);
		printf("\nDisplayList Generated");
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
	FnTable.CleanDataTable();
	FnTimeCurve.CleanUpTimeCurve();
	const int NoOfVar = NO_OF_VARIABLES;
	FnTable.SetNoOfVariables(NoOfVar);

	FnEval.Parser2DataTable(FnTable, NoOfVar);

	FnEval.Evaluate(FnTable, var, FnParser);

	printf("\nEvaluated the Function");

	FnTimeCurve.SetNoOfTimeSteps(var[0].GetNoOfSteps());
	FnTimeCurve.CalculateTimeSurfaces(FnTable, var);

	printf("\nCalculated Time Curves");
}

	





