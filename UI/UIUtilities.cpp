

#include "UIUtilities.h"

UIUtilities::UIUtilities()
{
	width = UI_DEFAULT_WIDTH;
	height = UI_DEFAULT_HEIGHT;

	InputX = 0;
	InputY = UI_DEFAULT_WIDTH*UI_INPUT_WINDOW_HEIGHT_RATIO;
	InputWidth = UI_DEFAULT_WIDTH*UI_INPUT_WINDOW_WIDTH_RATIO;
	InputHeight = UI_DEFAULT_HEIGHT*UI_TITLE_WINDOW_HEIGHT_RATIO;
	GraphicsX = 0; GraphicsY = 0; GraphicsWidth = 0; GraphicsHeight = 0;
	ToolsX = 0; ToolsY = 0; ToolsWidth = 0; ToolsHeight = 0;
}

UIUtilities::~UIUtilities()
{
	width = 0;
	height = 0;
	InputX = 0; InputY = 0; InputWidth = 0; InputHeight = 0;
	GraphicsX = 0; GraphicsY = 0; GraphicsWidth = 0; GraphicsHeight = 0;
	ToolsX = 0; ToolsY = 0; ToolsWidth = 0; ToolsHeight = 0;
}

void UIUtilities::SetWidth(const int wid)
{
	width = wid;
}

void UIUtilities::SetHeight(const int hei)
{
	height = hei;
}

const int UIUtilities::GetWidth() const
{
	return width;
}

const int UIUtilities::GetHeight() const
{
	return height;
}

void UIUtilities::DisplayTitleWindowBackground()
{
	double tWID, tHEI;
	tWID = (double) GetWidth();
	tHEI = (double) GetHeight()*UI_TITLE_WINDOW_HEIGHT_RATIO;

	//Background
	// glColor3ub(TITLE_WINDOW_COLOR_R,TITLE_WINDOW_COLOR_G,TITLE_WINDOW_COLOR_B);
	DisplayBackground(0,0, tWID, tHEI,
						TITLE_WINDOW_COLOR_R,TITLE_WINDOW_COLOR_G,TITLE_WINDOW_COLOR_B);
	// Title Text
	DisplayTextMsgAt(tWID/4,tHEI*3/4,TITLE_COURSE,8,
						TITLE_MSG_COLOR_R,TITLE_MSG_COLOR_G,TITLE_MSG_COLOR_B);	
}


/***************** INPUT ****************************/
void UIUtilities::DisplayInputWindowBackground()
{
	double iWID, iHEI;
	iWID = (double) GetWidth()*UI_INPUT_WINDOW_WIDTH_RATIO;
	iHEI = (double)	GetHeight()*UI_INPUT_WINDOW_HEIGHT_RATIO;

	InputX = 0;
	InputY = GetHeight()*UI_TITLE_WINDOW_HEIGHT_RATIO;
	InputWidth = iWID;
	InputHeight = iHEI;

	//Background
	DisplayBackground(InputX, InputY, InputWidth, InputHeight,
						INPUT_WINDOW_COLOR_R,INPUT_WINDOW_COLOR_G,INPUT_WINDOW_COLOR_B);
}

void UIUtilities::DisplayEquationWindowBackground()
{
	double iWID, iHEI, ix1, iy1;
	iWID = (double) GetWidth()*INPUT_EQUATION_WINDOW_WIDTH_RATIO;
	iHEI = (double)	GetHeight()*INPUT_EQUATION_WINDOW_HEIGHT_RATIO;

	ix1 = GetWidth()*INPUT_EQUATION_WINDOW_THICKNESS; 
	iy1 = ((double)GetHeight())*UI_TITLE_WINDOW_HEIGHT_RATIO + ((double)GetHeight())*INPUT_EQUATION_WINDOW_THICKNESS;
	//Background
	DisplayBackground(ix1, iy1, iWID, iHEI,
						EQUATION_WINDOW_COLOR_R,EQUATION_WINDOW_COLOR_G,EQUATION_WINDOW_COLOR_B);

	EquationInput.SetLocation(ix1,iy1,iWID,iHEI);
}

void UIUtilities::DisplayVariablesWindowBackground( int i)
{
	double iWID, iHEI, ix1, iy1;
	iWID = (double)GetWidth()*INPUT_VARIABLES_WINDOW_WIDTH_RATIO;
	iHEI = (double)GetHeight()*INPUT_VARIABLES_WINDOW_HEIGHT_RATIO;

	ix1 = EquationInput.GetX();
	iy1 = EquationInput.GetY() + EquationInput.GetHeight()
			+ (double) GetWidth()*INPUT_VARIABLES_WINDOW_THICKNESS
			+ i*((double)GetHeight()*INPUT_VARIABLES_WINDOW_HEIGHT_RATIO + (double) GetWidth()*INPUT_EQUATION_WINDOW_THICKNESS);
	//Background
	DisplayBackground(ix1, iy1, iWID, iHEI,
		EQUATION_WINDOW_COLOR_R, EQUATION_WINDOW_COLOR_G, EQUATION_WINDOW_COLOR_B);

	VariablesInput[i].SetLocation(ix1, iy1, iWID, iHEI);
}

void UIUtilities::DisplayPlotIconWindowBackground()
{
	double iWID, iHEI, ix1, iy1;
	iWID = (double)GetWidth()*INPUT_PLOT_ICON_WIDTH_RATIO;
	iHEI = (double)GetHeight()*INPUT_PLOT_ICON_HEIGHT_RATIO;

	ix1 = EquationInput.GetX();
	iy1 = VariablesInput[NO_OF_INDEPENDENT_VARIABLES-1].GetY() 
			+ VariablesInput[NO_OF_INDEPENDENT_VARIABLES-1].GetHeight()
			+ (double)GetHeight()*INPUT_EQUATION_WINDOW_THICKNESS;
	//Background
	DisplayBackground(ix1, iy1, iWID, iHEI,
		PLOT_ICON_COLOR_R, PLOT_ICON_COLOR_G, PLOT_ICON_COLOR_B);
	PlotIcon.SetLocation(ix1, iy1, iWID, iHEI);
	DisplayTextMsgAt(ix1+LEFTSPACE + iWID*0.35, iy1+iHEI*0.75, 
						"PLOT",8,
						PLOT_ICON_FONT_COLOR_R,
						PLOT_ICON_FONT_COLOR_G,
						PLOT_ICON_FONT_COLOR_B);
}

void UIUtilities::DisplayToolsWindowBackground()
{
	double tlWID, tlHEI, tlx1, tlx2, tly1, tly2;
	tlWID = (double) GetWidth()*UI_TOOL_WINDOW_WIDTH_RATIO;
	tlHEI = (double) GetHeight()*UI_TOOL_WINDOW_HEIGHT_RATIO;

	//Background
	DisplayBackground(((double) GetWidth())-tlWID, GetHeight()*UI_TITLE_WINDOW_HEIGHT_RATIO, tlWID, tlHEI,
						TOOL_WINDOW_COLOR_R,TOOL_WINDOW_COLOR_G,TOOL_WINDOW_COLOR_B);
}

void UIUtilities::DisplayFooterWindowBackground()
{
	double fWID, fHEI, fx1, fy1;
	fWID = (double) GetWidth();
	fHEI = (double) GetHeight()*UI_TOOL_WINDOW_HEIGHT_RATIO;

	//Background
	DisplayBackground(0, (double) GetHeight()*(1-UI_FOOTER_WINDOW_HEIGHT_RATIO), fWID, fHEI,
						FOOTER_WINDOW_COLOR_R,FOOTER_WINDOW_COLOR_G,FOOTER_WINDOW_COLOR_B);	

}
