#ifndef __DRAW_FIGURES_H__
#define __DRAW_FIGURES_H__

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Colors.h"
#include "Constants.h"

template <class T>
class DrawFigures
{
	Color FigColor;
public:

	double ConvertAngleDegreetoRandian(double degree)
	{
		return degree / 180.00 * PI;
	};

	void DrawRectangle2D(GLdouble X1, GLdouble Y1, GLdouble X2, GLdouble Y2, int FillType)
	{
		glBegin(FillType);

		glVertex2d(X1, Y1);
		glVertex2d(X2, Y1);
		glVertex2d(X2, Y2);
		glVertex2d(X1, Y2);

		glEnd();
	};

	void DrawCircle2D(GLfloat cx, GLfloat cy, double r)
	{
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i<360; i += 10)
		{
			double angle = ConvertAngleDegreetoRandian(i);

			double s = sin(angle);
			double c = cos(angle);

			double x = (double)cx + (double)r*c;
			double y = (double)cy + (double)r*s;
			glVertex2d(x, y);
		}
		glEnd();
	};
	void DrawLines3D(GLdouble X1, GLdouble Y1, GLdouble Z1, GLdouble X2, GLdouble Y2, GLdouble Z2, int LineType)
	{
		glVertex3d(X1, -Y1, Z1);
		glVertex3d(X2, -Y2, Z2);
	};
	void DrawLines3D(std::vector<T> Coord1, std::vector<T> Coord2, int FillType)
	{
		DrawLines3D(Coord1.at(0), Coord1.at(1), Coord1.at(2),
			Coord2.at(0), Coord2.at(1), Coord2.at(2),
			FillType
		);
	};

	void DrawTriangle3D(	GLdouble X1, GLdouble Y1, GLdouble Z1,
							GLdouble X2, GLdouble Y2, GLdouble Z2,
							GLdouble X3, GLdouble Y3, GLdouble Z3,
							bool ColorGrade = false, GLdouble Min = 0, GLdouble Max = 1
						)
	{

		FigColor.ColorGrade((Z1 - Min) / (Max - Min));
		glVertex3d(X1, -Y1, Z1);

		FigColor.ColorGrade((Z2 - Min) / (Max - Min));
		glVertex3d(X2, -Y2, Z2);
		
		FigColor.ColorGrade((Z3 - Min) / (Max - Min));
		glVertex3d(X3, -Y3, Z3);
	};

	void DrawTriangle3D(	std::vector<T> Coord1, std::vector<T> Coord2, std::vector<T> Coord3,
							bool ColorGrade = false, GLdouble Min = 0, GLdouble Max = 1
						)
	{
			
		DrawTriangle3D(	Coord1.at(0), Coord1.at(1), Coord1.at(2),
						Coord2.at(0), Coord2.at(1), Coord2.at(2),
						Coord3.at(0), Coord3.at(1), Coord3.at(2),
						ColorGrade, Min, Max
					);
	};

	void WriteMsgAtXYZ(GLdouble X, GLdouble Y, GLdouble Z, const char *Msg)
	{
		glRasterPos3d(X, -Y, Z);
		YsGlDrawFontBitmap6x7(Msg);
	}
};
#endif