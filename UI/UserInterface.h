#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include "UIUtilities.h"
#include "CameraTmp.h"

class UserInterface : public UIUtilities
{
private:

	// Evaluate options
	int RenderState;
	bool AnyWindowActivated;
	CameraObject camera;
public:
	UserInterface();
	~UserInterface();


	// Basic Functions
	void Initialize();
	void OpenWindow(const double AspectRatio);
	void AutoScaleWindow();

	// 2D & 3D
	void SetUp2DEnvironment();

	// UI_polling
	void Polling();
	void DeActivateAllInputWindows();
	// Windows
	void DisplayTitleWindow();

	void DisplayInputWindow();
	void DisplayEquationWindow();
	void DisplayVariablesWindow();
	void DisplayPlotIconWindow();
	
	void DisplayGraphicsWindow();
	void DisplayToolsWindow();
	void DisplayFooterWindow();
};













#endif