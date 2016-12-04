
#include "UIVariablesInput.h"

UIVariablesInput::UIVariablesInput()
{
	CursorLocation = 0;
	VariableInputValues[0] = 0.0;
	VariableInputValues[1] = 0.0;
	VariableInputValues[2] = 0.0;
	VariableInputValues[3] = 0.0;
}

UIVariablesInput::~UIVariablesInput()
{
	CursorLocation = 0;
	VariableInputValues[0] = 0.0;
	VariableInputValues[1] = 0.0;
	VariableInputValues[2] = 0.0;
	VariableInputValues[3] = 0.0;
}


const double UIVariablesInput::GetMin() const
{
	return VariableInputValues[0];
}
const double UIVariablesInput::GetMax() const
{
	return VariableInputValues[1];
}
const double UIVariablesInput::GetDelta() const
{
	return VariableInputValues[2];
}
const int UIVariablesInput::GetNoOfSteps() const
{
	return (int) VariableInputValues[3];
}

bool UIVariablesInput::Input(std::string & str_, int CursorLoc)
{
	//key = FsInkey();
	if (key == FSKEY_ENTER)
	{
		//return true
		CursorLocation = MAX(MIN(CursorLocation + 1, (NO_OF_INDEPENDENT_VARIABLE_PARAMETERS - 1)), 0);
	}
	else if (key == FSKEY_ESC)
	{
		SetState(NOT_ACTIVE);
	}
	else if (key == FSKEY_BS)
	{
		//str.BackSpace();
		if (str_.length()>0)	str_.pop_back();
	}
	else if (key == FSKEY_DOWN)
	{
		//printf("cursorlocation %d\n", CursorLocation);
		CursorLocation = MAX(MIN(CursorLocation + 1, (NO_OF_INDEPENDENT_VARIABLE_PARAMETERS - 1)),0);
		//printf("cursorlocation %d\n", CursorLocation);
	}
	else if (key == FSKEY_UP)
	{
		CursorLocation = MAX(MIN(CursorLocation - 1, (NO_OF_INDEPENDENT_VARIABLE_PARAMETERS - 1)), 0);
	}
	auto c =FsInkeyChar();
	if (' ' <= c)
	{
		//str.Add(c);
		char tmp[2]; tmp[0] = (char)c; tmp[1] = 0;
		str_.append(tmp);
		SetInputEntered( YES);
	}

	if (0 != time(nullptr) % 2)
	{
		//str.Add('_');
		str_.append("_");
	}
	else
	{
		//str.Add('|');
		str_.append("|");
	}
	DisplayInput(str_, CursorLoc);
	//DisplayTextMsgAt(x + 10, y + 16 + 16, str.GetPointer(), 5, GENERAL_TEXT_FONT_COLOR_R, GENERAL_TEXT_FONT_COLOR_G, GENERAL_TEXT_FONT_COLOR_B);
	//str.BackSpace();
	str_.pop_back();

}

void UIVariablesInput::DisplayInput(std::string str_, int CursorLoc)
{
	int NoOfLines = 1 + str_.length() / GetNoOfCharsInaLine();
	// printf("chars: %d, lines: %d, strlen: %d\n",NoOfCharsInaLine, NoOfLines, str.length());
	int i = 0;
	char chr[100];
	std::string substr;
	// printf("%d\n", i*NoOfCharsInaLine);
	substr = str_.substr(i*GetNoOfCharsInaLine(), 100);
	substr.copy(chr, 100);
	chr[MIN(GetNoOfCharsInaLine(), str_.length())] = 0;
	DisplayTextMsgAt(GetX() + LEFTSPACE, GetY() + HEADERSPACE + (2*CursorLoc + 2)*LINESPACE,
		chr, 5,
		GENERAL_TEXT_FONT_COLOR_R,
		GENERAL_TEXT_FONT_COLOR_G,
		GENERAL_TEXT_FONT_COLOR_B);
}

void UIVariablesInput::Display(const char msgtitle[])
{
	DisplayTextMsgAt(GetX() + LEFTSPACE, GetY() + HEADERSPACE,
						msgtitle, 5,
						GENERAL_TEXT_FONT_COLOR_R,
						GENERAL_TEXT_FONT_COLOR_G,
						GENERAL_TEXT_FONT_COLOR_B);
	DisplayTextMsgAt(GetX() + LEFTSPACE, GetY() + HEADERSPACE + LINESPACE,
						"Enter Min>", 5,
						GENERAL_TEXT_FONT_COLOR_R,
						GENERAL_TEXT_FONT_COLOR_G,
						GENERAL_TEXT_FONT_COLOR_B);
	DisplayTextMsgAt(GetX() + LEFTSPACE, GetY() + HEADERSPACE + 3*LINESPACE,
						"Enter Max>", 5,
						GENERAL_TEXT_FONT_COLOR_R,
						GENERAL_TEXT_FONT_COLOR_G,
						GENERAL_TEXT_FONT_COLOR_B);
	DisplayTextMsgAt(GetX() + LEFTSPACE, GetY() + HEADERSPACE + 5*LINESPACE,
						"Enter Delta>", 5,
						GENERAL_TEXT_FONT_COLOR_R,
						GENERAL_TEXT_FONT_COLOR_G,
						GENERAL_TEXT_FONT_COLOR_B);
	DisplayTextMsgAt(GetX() + LEFTSPACE, GetY() + HEADERSPACE + 7 * LINESPACE,
						"No. of Steps>", 5,
						GENERAL_TEXT_FONT_COLOR_R,
						GENERAL_TEXT_FONT_COLOR_G,
						GENERAL_TEXT_FONT_COLOR_B);
	if (GetState() == ACTIVE)
	{
		for (int i = 0; i < NO_OF_INDEPENDENT_VARIABLE_PARAMETERS; ++i)
		{
			if(i==CursorLocation) Input(VariableInput[CursorLocation], CursorLocation);
			else DisplayInput(VariableInput[i], i);
		}		
	}
	else if (GetState() == NOT_ACTIVE && IsInputEntered() == YES)
	{
		//printf("im here\n");
		CursorLocation = 0;
		for (int i = 0; i < NO_OF_INDEPENDENT_VARIABLE_PARAMETERS; ++i)
		{
			DisplayInput(VariableInput[i],i);
		}
		//displaytextmsgat(x + 10, y + 16 + 16, str.getpointer(),5, general_text_font_color_r, general_text_font_color_g, general_text_font_color_b);
	}
	//ConvertVariablesToValues();
}
void UIVariablesInput::ConvertVariablesToValues()
{
	for (int i = 0; i < NO_OF_INDEPENDENT_VARIABLE_PARAMETERS; ++i)
	{
		VariableInputValues[i] =  Convert2Double(VariableInput[i]);
	}
}

double UIVariablesInput::Convert2Double(std::string str_)
{
	double value = atof(str_.c_str());
	//printf("%f \t", value);
	return value;
}

