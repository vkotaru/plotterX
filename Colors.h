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

	void SetAndChangeColor(GLfloat R, GLfloat G, GLfloat B, GLfloat Scale = 255)
	{
		SetColor(R, G, B, Scale);
		ChangeColor();
	}
};