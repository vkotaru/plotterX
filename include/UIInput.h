#ifndef __UI_INPUT_H__
#define __UI_INPUT_H__


#include <cstdlib>
#include <cmath>
#include <string>

#include "UIBasics.h"
#include "MouseInputs.h"

class UIInput : public UIBasics
{
private:
	std::string str;

	// Location
	double x, y, width, height;
	double CharacterSize[2];
	int NoOfCharsInaLine;
	int state;
	int InputEntered, MaxNoOfLines;

public:
	UIInput();
	~UIInput();
	void CleanUp(void);
	int key;
	void SetKey(int k);
	void SetState(const int s);
	void SetLocation(const double x, const double y, const double wid, const double hei);
	void SetInputEntered(const int set);

	const int GetState() const;
	const double GetX() const;
	const double GetY() const;
	const double GetWidth() const;
	const double GetHeight() const;
	const int IsInputEntered() const;
	const int GetNoOfCharsInaLine() const;
	void GetCharArrayOfString(char *ChrArray);

	void SetCaption(const char c[]);
	void SetString(const char s[]);

	bool Input(std::string& str_);

	const std::string GetUIInput() const;

	void CheckForActiveState(MouseInputs m);
	void Display(MouseInputs m, const char msgtitle[]);
	void DisplayInput(std::string str_);
	
};


#endif















