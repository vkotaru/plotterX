#ifndef __UI_UTILITIES_H__
#define __UI_UTILITIES_H__


#include "UIInput.h"
#include "UIVariablesInput.h"
#include "UIBasics.h"
#include "MouseInputs.h"
#include "UIIcons.h"


class UIUtilities : public UIBasics
{
private:
	// Dimensions
	int x,y, width, height;

	//input variables Locations
	int CharacterSize;
protected:
	// Input Window Parameters
	double InputX, InputY, InputWidth, InputHeight;
	double GraphicsX, GraphicsY, GraphicsWidth, GraphicsHeight;
	double ToolsX, ToolsY, ToolsWidth, ToolsHeight;

public:
	UIUtilities();
	~UIUtilities();

	MouseInputs mouse;
	UIInput EquationInput;
	UIVariablesInput VariablesInput[NO_OF_INDEPENDENT_VARIABLES];
	UIIcons PlotIcon;

	// Set Functions
	void SetWidth(const int wid);
	void SetHeight(const int hei);
	void SetCharacterSize(const int size);

	// Get Functions
	const int GetWidth() const;
	const int GetHeight() const;
	const int GetCharacterSize() const;

	// Different Windows
	void DisplayTitleWindowBackground();

	void DisplayInputWindowBackground();
	void DisplayEquationWindowBackground();
	void DisplayVariablesWindowBackground(int i);
	void DisplayPlotIconWindowBackground();

	void DisplayToolsWindowBackground();

	void DisplayFooterWindowBackground();
};





#endif
