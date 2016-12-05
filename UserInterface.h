#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include "UIUtilities.h"
#include "Camera.h"
#include "Parser.h"
#include "Variable.h"

class UserInterface : public UIUtilities
{
private:

	// Evaluate options
	int RenderState;
	bool AnyWindowActivated;

	int key;
public:
	UserInterface();
	~UserInterface();
	Camera cam;

	// Basic Functions
	void Initialize();
	void OpenWindow(const double AspectRatio);
	void AutoScaleWindow();
	void DisplayInterface();
	void DisplayGraphics();

	// 2D & 3D
	void SetUp2DEnvironment();

	// UI_polling
	int Polling();
	void DeActivateAllInputWindows();

	// Data-Transfer
	void ValidateInput();
	void TransferDataToBackEnd(Variable <double> var[], Parser& FnParser, char * InputEq);

	// Windows
	void DisplayTitleWindow();

	void DisplayInputWindow();
	void DisplayEquationWindow();
	void DisplayVariablesWindow();
	void DisplayPlotIconWindow();
	
	void DisplayGraphicsWindow();
	void DisplayToolsWindow();
	void DisplayFooterWindow();

	void DrawGroundLattice(void);
};













#endif