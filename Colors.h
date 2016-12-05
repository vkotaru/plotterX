#ifndef __COLOR_H__
#define __COLOR_H__

#include "fssimplewindow.h"

class Color
{
	GLfloat Red, Green, Blue;
public:
	Color()
	{
		Red		= 0;
		Green	= 0;
		Blue	= 0;
	};

	Color(GLfloat R, GLfloat G, GLfloat B, GLfloat Scale = 255)
	{
		SetColor(R, G, B, Scale);
	}

	void SetColor(GLfloat R, GLfloat G, GLfloat B, GLfloat Scale = 255)
	{
		Red		=	R / Scale;
		Green	=	G / Scale;
		Blue	=	B / Scale;
	}
	void ChangeColor()
	{
		glColor3f(Red, Green, Blue);
	}

	void ColorGrade(const double Value)
	{

		if (Value<0)
		{
			Red = 0;
			Green = 0;
			Blue = 1;
		}
		else if (1<Value)
		{
			Red = 1;
			Green = 0;
			Blue = 0;
		}
		else if (Value < 0.25)
		{
			Red = 0;
			Blue = 1;
			Green = Value / 0.25;
		}
		else if (Value<0.5)
		{
			Red = 0;
			Green = 1;
			Blue = 1 - (Value - 0.25) / 0.25;
		}
		else if (Value<0.75)
		{
			Red = (Value - 0.5) / 0.25;
			Green = 1;
			Blue = 0;
		}
		else
		{
			Red = 1;
			Green = 1 - (Value - 0.75) / 0.25;
			Blue = 0;
		}
		ChangeColor();
	}

	void SetAndChangeColor(GLfloat R, GLfloat G, GLfloat B, GLfloat Scale = 255)
	{
		SetColor(R, G, B, Scale);
		ChangeColor();
	}
};
#endif