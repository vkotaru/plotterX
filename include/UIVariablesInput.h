#ifndef __UI_VARIABLES_INPUT_H__
#define __UI_VARIABLES_INPUT_H__

#include "UIInput.h"

class UIVariablesInput : public UIInput
{
private:
	std::string VariableInput[NO_OF_INDEPENDENT_VARIABLE_PARAMETERS];
	double VariableInputValues[NO_OF_INDEPENDENT_VARIABLE_PARAMETERS];
	int CursorLocation;

public:
	UIVariablesInput();
	~UIVariablesInput();

	bool Input(std::string& str_, int CursorLoc);
	void Display(const char msgtitle[]);
	void DisplayInput(std::string str_, int CursorLoc);

	const double GetMin() const;
	const double GetMax() const;
	const double GetDelta() const;
	const int GetNoOfSteps() const;

	void ConvertVariablesToValues();
	double Convert2Double(std::string str_);

};





#endif