#include "UserInterface.h"

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
	cam.SetPosY(30.0);
}

void UserInterface::AutoScaleWindow()
{
	int wid, hei;
	FsGetWindowSize(wid,hei);
	SetWidth(wid);
	SetHeight(hei);
	DisplayGraphicsWindow();

}

void UserInterface::DisplayInterface()
{
	SetUp2DEnvironment();
	DisplayTitleWindow();
	DisplayInputWindow();
	DisplayToolsWindow();
	DisplayFooterWindow();

	//DrawTextDesiredSize(GetWidth()*0.25, GetHeight() / 2, 16, 16, "HI");
	//DisplayTextMsgAt(GetWidth()*0.45, GetHeight()*0.5, "WELCOME", 14, 255, 0, 0);
}

void UserInterface::DisplayGraphics()
{
	DisplayGraphicsWindow();
	// 3D drawing from here
	DrawGroundLattice();

	SetUp2DEnvironment();
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
int UserInterface::Polling()
{
	FsPollDevice();
	key = FsInkey();
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
	return key;
}

void UserInterface::DeActivateAllInputWindows()
{
	EquationInput.SetState(NOT_ACTIVE);
	for (int iter = 0; iter < NO_OF_INDEPENDENT_VARIABLES; ++iter)
	{
		VariablesInput[iter].SetState(NOT_ACTIVE);
	}
}

/************************* DATA TRANSFER *******************************/
void UserInterface::ValidateInput()
{
	char TempChar[100];
	EquationInput.GetCharArrayOfString(TempChar);
	printf("%s\n", TempChar);

	for (int i = 0; i < NO_OF_INDEPENDENT_VARIABLES; ++i)
	{
		VariablesInput[i].ConvertVariablesToValues();
		printf("%f %f %d\n ",VariablesInput[i].GetMin(), 
							 VariablesInput[i].GetMax(),
							VariablesInput[i].GetNoOfSteps());
	}
	printf("____________________________________________\n");
}

void UserInterface::TransferDataToBackEnd(Variable <double> var[], Parser& FnParser, char* InputEq)
{
	EquationInput.GetCharArrayOfString(InputEq);
	printf("%s\n", InputEq);
	FnParser.SetInfix(InputEq);
	FnParser.SetInfix(InputEq);

	for (int i = 0; i < NO_OF_INDEPENDENT_VARIABLES; ++i)
	{
		VariablesInput[i].ConvertVariablesToValues();
		var[i].SetMin(VariablesInput[i].GetMin());
		var[i].SetMax(VariablesInput[i].GetMax());
		var[i].SetNoOfSteps(VariablesInput[i].GetNoOfSteps());
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
	EquationInput.SetKey(key);
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
		VariablesInput[i].SetKey(key);
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
	cam.SetUpCameraProjection();
	cam.SetUpCameraTransformation();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(1, 1);

}

void UserInterface::DrawGroundLattice(void)
{
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);

	for (int i = -1000; i <= 1000; i += 20)
	{
		glVertex3i(i, 0, -1000);
		glVertex3i(i, 0, +1000);

		glVertex3i(-1000, 0, i);
		glVertex3i(+1000, 0, i);
	}

	glEnd();
}