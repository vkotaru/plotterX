#include "fssimplewindow.h"
#include "ysglfontdata.h"

#define PI 3.1415927

template <class T>
class DrawFigures
{
public:

	double ConvertAngleDegreetoRandian(double degree)
	{
		return degree / 180.00 * PI;
	};

	void DrawRectangle2D(GLint X1, GLint Y1, GLint X2, GLint Y2, int FillType)
	{
		glBegin(FillType);

		glVertex2i(X1, Y1);
		glVertex2i(X2, Y1);
		glVertex2i(X2, Y2);
		glVertex2i(X1, Y2);

		glEnd();
	};

	void DrawCircle2D(GLint cx, GLint cy, double r)
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

	void DrawTriangle3D(	GLint X1, GLint Y1, GLint Z1, 
							GLint X2, GLint Y2, GLint Z2, 
							GLint X3, GLint Y3, GLint Z3, 
							int FillType
						)
	{
		glBegin(FillType);

		glVertex3i(X1, Y1, Z1);
		glVertex3i(X2, Y2, Z2);
		glVertex3i(X3, Y3, Z3);

		glEnd();
	};

	void DrawTriangle3D(std::vector<T> Coord1, std::vector<T> Coord2, std::vector<T> Coord3, int FillType)
	{
		DrawTriangle3D(Coord1.at(0), Coord1.at(1), Coord1.at(2),
			Coord2.at(0), Coord2.at(1), Coord2.at(2),
			Coord3.at(0), Coord3.at(1), Coord3.at(2),
			FillType
		);
	};

	void DrawLines3D(GLint X1, GLint Y1, GLint Z1, GLint X2, GLint Y2, GLint Z2, int LineType)
	{
		glBegin(LineType);

		glVertex3i(X1, Y1, Z1);
		glVertex3i(X2, Y2, Z2);

		glEnd();
	};

	void WriteMsgAtXYZ(GLdouble X, GLdouble Y, GLdouble Z, const char *Msg)
	{
		glRasterPos3d(X, Y, Z);
		YsGlDrawFontBitmap6x7(Msg);
	}
};