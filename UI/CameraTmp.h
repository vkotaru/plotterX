#ifndef __CAMERA_TEMP_H__
#define __CAMERA_TEMP_H__


#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"

const double YsPi = 3.1415927;

class CameraObject
{
public:
	double x, y, z;
	double h, p, b;

	double fov, nearZ, farZ;

	CameraObject()
	{
		Initialize();
	}

	void Initialize(void)
	{
		x = 0;
		y = 0;
		z = 0;
		h = 0;
		p = 0;
		b = 0;

		fov = YsPi / 6.0;  // 30 degree
		nearZ = 0.1;
		farZ = 200.0;
	}
	void SetUpCameraProjection(void)
	{
		int wid, hei;
		double aspect;

		FsGetWindowSize(wid, hei);
		aspect = (double)wid / (double)hei;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov*180.0 / YsPi, aspect, nearZ, farZ);
	}
	void SetUpCameraTransformation(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(-b*180.0 / YsPi, 0.0, 0.0, 1.0);  // Rotation about Z axis
		glRotated(-p*180.0 / YsPi, 1.0, 0.0, 0.0);  // Rotation about X axis
		glRotated(-h*180.0 / YsPi, 0.0, 1.0, 0.0);  // Rotation about Y axis
		glTranslated(-x, -y, -z);
	}

	void GetForwardVector(double &vx, double &vy, double &vz)
	{
		vx = -cos(p)*sin(h);
		vy = sin(p);
		vz = -cos(p)*cos(h);
	}


	void DrawGroundLattice(void)
	{
		glColor3ub(0, 0, 255);
		glBegin(GL_LINES);

		for (int i = -1000; i <= 1000; i += 20)
		{
			glVertex3i(i, 0, -1000);
			glVertex3i(i, 0, +1000);

			glVertex3i(-1000, 0, i);
			glVertex3i(+1000, 0, i);
		}

		glEnd();
	}
};







#endif