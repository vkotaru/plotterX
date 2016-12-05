#include "UIInput.h"
#include "fssimplewindow.h"

UIInput::UIInput()
{
	state = 0; key = 0;
	InputEntered = 0;
	x = 0; y = 0; width = 0; height = 0;
	CharacterSize[0] = 8;
	CharacterSize[1] = 12;
	NoOfCharsInaLine = 0; MaxNoOfLines = 0;
}
UIInput::~UIInput()
{
	CleanUp();
	state = 0; key = 0;
	InputEntered = 0;
	x = 0; y = 0; width = 0; height = 0;
	NoOfCharsInaLine = 0; MaxNoOfLines = 0;
}
void UIInput::CleanUp(void)
{

}
void UIInput::SetKey(int k)
{
	key = k;
}

void UIInput::SetState(const int s)
{
	state = s;
}

void UIInput::SetLocation(const double x, const double y, const double wid, const double hei)
{
	this-> x = x;
	this-> y = y;
	this-> width = wid;
	this-> height = hei;
	this->NoOfCharsInaLine = (this->width - LINESPACE - RIGHTSPACE) / CharacterSize[0];
	this->MaxNoOfLines = (this->height - LINESPACE - HEADERSPACE - FOOTERSPACE) / CharacterSize[1];
}

void UIInput::SetInputEntered(const int set)
{
	InputEntered = set;
}

const int UIInput::GetState() const
{
	return state;
}
const double UIInput::GetX() const
{
	return x;
}
const double UIInput::GetY() const
{
	return y;
}
const double UIInput::GetWidth() const
{
	return width;
}
const double UIInput::GetHeight() const
{
	return height;
}
const int UIInput::IsInputEntered() const
{
	return InputEntered;
}
const int UIInput::GetNoOfCharsInaLine() const
{
	return NoOfCharsInaLine;
}

void UIInput::SetCaption(const char c[])
{
	//caption.Set(c);
}
void UIInput::SetString(const char s[])
{
	//str.Set(s);
}

const std::string UIInput::GetUIInput() const
{
	return str;
}

bool UIInput::Input(std::string& str_)
{
		//FsPollDevice();
		//auto key=FsInkey();
		if(key==FSKEY_ENTER)
		{
			return true;
		}
		else if(key==FSKEY_ESC)
		{
			SetState(NOT_ACTIVE);
		}
		else if(key==FSKEY_BS)
		{
			//str.BackSpace();
			if(str_.length()>0)	str_.pop_back();
		}

		auto c = FsInkeyChar();
		while (FsInkeyChar() != NULL);
		if(' '<=c)
		{
			//str.Add(c);
			char tmp[2]; tmp[0] = (char)c; tmp[1] = 0;
			str_.append(tmp);
			InputEntered = YES;
		}

		if(0!=time(nullptr)%2)
		{
			//str.Add('_');
			str_.append("_");
		}
		else
		{
			//str.Add('|');
			str_.append("|");
		}
		DisplayInput(str_);
		//DisplayTextMsgAt(x + 10, y + 16 + 16, str.GetPointer(), 5, GENERAL_TEXT_FONT_COLOR_R, GENERAL_TEXT_FONT_COLOR_G, GENERAL_TEXT_FONT_COLOR_B);
		//str.BackSpace();
		str_.pop_back();
}

void UIInput::DisplayInput(std::string str_)
{
	int NoOfLines = 1+str_.length()/NoOfCharsInaLine;
	// printf("chars: %d, lines: %d, strlen: %d\n",NoOfCharsInaLine, NoOfLines, str.length());
	int i = 0, imax = 0;
	imax = MIN(NoOfLines, MaxNoOfLines);
	for (i; i < imax; ++i)
	{
		char chr[100];
		std::string substr;
		// printf("%d\n", i*NoOfCharsInaLine);
		substr = str_.substr(i*NoOfCharsInaLine, 100);
		substr.copy(chr,100);
		chr[MIN(NoOfCharsInaLine, str_.length() - i*NoOfCharsInaLine)] = 0;
		DisplayTextMsgAt(x + LEFTSPACE, y + HEADERSPACE+ (i+1)*LINESPACE,
							chr, 5,
							GENERAL_TEXT_FONT_COLOR_R,
							GENERAL_TEXT_FONT_COLOR_G,
							GENERAL_TEXT_FONT_COLOR_B);
	}

}

void UIInput::Display(MouseInputs m, const char msgtitle[])
{
	DisplayTextMsgAt(x+LEFTSPACE, y+HEADERSPACE,msgtitle, 5, GENERAL_TEXT_FONT_COLOR_R, GENERAL_TEXT_FONT_COLOR_G, GENERAL_TEXT_FONT_COLOR_B);
	if (GetState() == ACTIVE)
	{
		Input(str);
	}
	else if (GetState() == NOT_ACTIVE && IsInputEntered() == YES)
	{
		//printf("IM HERE\n");
		DisplayInput(str);
		//DisplayTextMsgAt(x + 10, y + 16 + 16, str.GetPointer(),5, GENERAL_TEXT_FONT_COLOR_R, GENERAL_TEXT_FONT_COLOR_G, GENERAL_TEXT_FONT_COLOR_B);
	}

}

void UIInput::GetCharArrayOfString(char *ChrArray)
{
	str.copy(ChrArray, 100);
	ChrArray[str.length()] = 0;
}
