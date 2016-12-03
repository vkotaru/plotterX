
#include "UserInterface.h"
#include "CameraTmp.h"


UserInterface::UserInterface()
{
	RenderState = 0;
	AnyWindowActivated = false;
}

UserInterface::~UserInterface()
{
	RenderState = 0;
	AnyWindowActivated = false;
}

void UserInterface::OpenWindow(const double AspectRatio)
{
	FsOpenWindow(400, 0, UI_DEFAULT_HEIGHT*AspectRatio, UI_DEFAULT_HEIGHT, 1);
}

void UserInterface::Initialize()
{
	OpenWindow(ASPECT_RATIO_4_3);

	int terminate = 0;
	camera.y = 30.0;
	camera.nearZ = 1.0;
	camera.farZ = 1000.0;
}

void UserInterface::AutoScaleWindow()
{
	int wid, hei;
	FsGetWindowSize(wid,hei);
	SetWidth(wid);
	SetHeight(hei);

	DisplayGraphicsWindow();
	
	SetUp2DEnvironment();
	DisplayTitleWindow();
	DisplayInputWindow();
	DisplayToolsWindow();
	DisplayFooterWindow();

	//DrawTextDesiredSize(GetWidth()*0.25, GetHeight() / 2, 16, 16, "HI");
	DisplayTextMsgAt(GetWidth()*0.45, GetHeight()*0.5, "WELCOME", 14, 255, 0, 0);

}

/******************  SETTING UP 2D AND 3D ******************************/
void UserInterface::SetUp2DEnvironment()
{
	glViewport(0, 0, GetWidth(), GetHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GetWidth(), GetHeight(), 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
}

/********************** POLLING ****************************************/
void UserInterface::Polling()
{
	FsPollDevice();

	if (mouse.LEFT_BUTTON_CLICK == ACTIVE &&
		mouse.mx >= EquationInput.GetX() &&
		mouse.mx <= (EquationInput.GetX() + EquationInput.GetWidth()) &&
		mouse.my >= EquationInput.GetY() &&
		mouse.my <= (EquationInput.GetY() + EquationInput.GetHeight()))
	{
		printf("%d\n", EquationInput.GetState());
		EquationInput.SetState((1 - EquationInput.GetState()));
		printf("Equation Box Activated %d\n\n", EquationInput.GetState());
		for (int iter = 0; iter < NO_OF_INDEPENDENT_VARIABLES; ++iter)
		{
			VariablesInput[iter].SetState(NOT_ACTIVE);
		}
		AnyWindowActivated = YES;
	}
	else if (mouse.LEFT_BUTTON_CLICK == ACTIVE &&
		mouse.mx >= PlotIcon.GetX() &&
		mouse.mx <= (PlotIcon.GetX() + PlotIcon.GetWidth()) &&
		mouse.my >= PlotIcon.GetY() &&
		mouse.my <= (PlotIcon.GetY() + PlotIcon.GetHeight()))
	{
		printf("PLOTTTTTTTTTTTTTTTTTTTTTTT\n");
		PlotIcon.SetState(ACTIVE);
		DeActivateAllInputWindows();
	}
	else if (mouse.LEFT_BUTTON_CLICK == ACTIVE &&
		mouse.mx >= InputX &&
		mouse.mx <= (InputX + InputWidth) &&
		mouse.my >= InputY &&
		mouse.my <= (InputY + InputHeight))
	{
		int IsVariableActive[3] = { 0,0,0 };
		for (int iter = 0; iter < NO_OF_INDEPENDENT_VARIABLES; ++iter)
		{
			if (mouse.LEFT_BUTTON_CLICK == ACTIVE &&
				mouse.mx >= VariablesInput[iter].GetX() &&
				mouse.mx <= (VariablesInput[iter].GetX() + VariablesInput[iter].GetWidth()) &&
				mouse.my >= VariablesInput[iter].GetY() &&
				mouse.my <= (VariablesInput[iter].GetY() + VariablesInput[iter].GetHeight()))
			{
				printf("%d\n", VariablesInput[iter].GetState());
				VariablesInput[iter].SetState((1 - VariablesInput[iter].GetState()));
				printf("Equation Box Activated %d\n\n", VariablesInput[iter].GetState());
				EquationInput.SetState(NOT_ACTIVE);
				IsVariableActive[iter] = ACTIVE;
				AnyWindowActivated = YES;
			}
		}
		for (int iter = 0; iter < NO_OF_INDEPENDENT_VARIABLES; ++iter)
		{
			if (IsVariableActive[iter]==NOT_ACTIVE)
			{
				VariablesInput[iter].SetState(NOT_ACTIVE);
			}
		}
	}
	else if (mouse.LEFT_BUTTON_CLICK == ACTIVE)
	{
		//printf("%d, %d, %d, %d, %d %d\n", mouse.mx, mouse.my, PlotIcon.GetX(), (PlotIcon.GetX() + PlotIcon.GetWidth()), PlotIcon.GetY(), (PlotIcon.GetY() + PlotIcon.GetHeight()));
		//EquationInput.SetState(NOT_ACTIVE);
		//for (int iter = 0; iter < NO_OF_INDEPENDENT_VARIABLES; ++iter)
		//{
		//	VariablesInput[iter].SetState(NOT_ACTIVE);
		//}
		DeActivateAllInputWindows();
		AnyWindowActivated = NO;
	}
	//if (AnyWindowActivated == NO)
	//{
	//	printf("IMHERE\n");
	//	if (0 != FsGetKeyState(FSKEY_LEFT))
	//	{
	//		camera.h += YsPi / 240.0;
	//	}
	//	else if (0 != FsGetKeyState(FSKEY_RIGHT))
	//	{
	//		camera.h -= YsPi / 240.0;
	//	}
	//	else if (0 != FsGetKeyState(FSKEY_UP))
	//	{
	//		camera.p += YsPi / 240.0;
	//	}
	//	else if (0 != FsGetKeyState(FSKEY_DOWN))
	//	{
	//		camera.p -= YsPi / 240.0;
	//	}
	//	else if (0 != FsGetKeyState(FSKEY_F))
	//	{
	//		double vx, vy, vz;
	//		camera.GetForwardVector(vx, vy, vz);
	//		camera.x += vx / 4.0;
	//		camera.y += vy / 4.0;
	//		camera.z += vz / 4.0;
	//	}
	//	else if (0 != FsGetKeyState(FSKEY_B))
	//	{
	//		double vx, vy, vz;
	//		camera.GetForwardVector(vx, vy, vz);
	//		camera.x -= vx / 4.0;
	//		camera.y -= vy / 4.0;
	//		camera.z -= vz / 4.0;
	//	}
	//}

}

void UserInterface::DeActivateAllInputWindows()
{
	EquationInput.SetState(NOT_ACTIVE);
	for (int iter = 0; iter < NO_OF_INDEPENDENT_VARIABLES; ++iter)
	{
		VariablesInput[iter].SetState(NOT_ACTIVE);
	}
}

/************************* WINDOWS *************************************/
// TITLE WINDOW
void UserInterface::DisplayTitleWindow()
{
	DisplayTitleWindowBackground();
}
// INPUT-WINDOW
void UserInterface::DisplayInputWindow()
{
	DisplayInputWindowBackground();
	DisplayEquationWindow();
	DisplayVariablesWindow();
	DisplayPlotIconWindow();
}

void UserInterface::DisplayEquationWindow()
{
	DisplayEquationWindowBackground();
	// Equation Window
	EquationInput.Display(mouse, EQUATION_PROMPT);
}

void UserInterface::DisplayVariablesWindow()
{
	// Variables Window
	for (int i = 0; i < NO_OF_INDEPENDENT_VARIABLES; ++i)
	{
		DisplayVariablesWindowBackground(i);
		// Prompt Message --> LOOK FOR A SIMPLE PROCESS 
		std::string PromptMsg = VARIABLES_PROMPT;
		std::string VariableTxt = VARIABLES_TEXT;
		PromptMsg = PromptMsg + VariableTxt[i] + " >";
		char MsgPrompt[25];
		PromptMsg.copy(MsgPrompt, 25);
		MsgPrompt[PromptMsg.length() + 3]=0;
		// Prompt Message --> LOOK FOR A SIMPLE PROCESS 
		VariablesInput[i].Display(MsgPrompt);
	}
}

void UserInterface::DisplayPlotIconWindow()
{
	DisplayPlotIconWindowBackground();
}

// TOOLS-WINDOW
void UserInterface::DisplayToolsWindow()
{
	DisplayToolsWindowBackground();
}

// FOOT-WINDOW
void UserInterface::DisplayFooterWindow()
{
	DisplayFooterWindowBackground();
}

// GRAPHICS WINOW
void UserInterface::DisplayGraphicsWindow()
{

	double gWID, gHEI;
	gWID = (double)GetWidth()*UI_GRAPHICS_WINDOW_WIDTH_RATIO;
	gHEI = (double)GetHeight()*UI_GRAPHICS_WINDOW_HEIGHT_RATIO;

	GraphicsX = InputWidth;
	GraphicsY = GetHeight()*UI_TITLE_WINDOW_HEIGHT_RATIO;
	GraphicsWidth = gWID;
	GraphicsHeight = gHEI;

	// Set up 3D drawing
	glViewport(GraphicsX, GraphicsY, GraphicsWidth, GraphicsHeight);
	camera.SetUpCameraProjection();
	camera.SetUpCameraTransformation();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);

	// 3D drawing from here
	camera.DrawGroundLattice();

	SetUp2DEnvironment();
}