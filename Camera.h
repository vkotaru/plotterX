#include<math.h>
#include "fssimplewindow.h"

const double YsPi = 3.1415927;

class Camera
{
public:
	double PosX, PosY, PosZ;
	double EulerAngH, EulerAngP, EulerAngB;

	double fov, nearZ, farZ;

	Camera()
	{
		PosX = 5;
		PosY = 5;
		PosZ = 5;
		EulerAngH = 0;
		EulerAngP = 0;
		EulerAngB = 0;

		fov = YsPi / 6.0;  // 30 degree
		nearZ = 0.1;
		farZ = 200.0;
	};

	void SetUpCameraProjection(void)
	{
		int ScreenWidth, ScreenHeight;
		double AspectRatio;

		FsGetWindowSize(ScreenWidth, ScreenHeight);
		AspectRatio = double(ScreenWidth/ScreenHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov*180.0 / YsPi, AspectRatio, nearZ, farZ);
	}

	void SetUpCameraTransformation(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(-EulerAngB*180.0 / YsPi, 0.0, 0.0, 1.0);  // Rotation about Z axis
		glRotated(-EulerAngP*180.0 / YsPi, 1.0, 0.0, 0.0);  // Rotation about X axis
		glRotated(-EulerAngH*180.0 / YsPi, 0.0, 1.0, 0.0);  // Rotation about Y axis
		glTranslated(-PosX, -PosY, -PosZ);
	}

	void GetForwardVector(double &vx, double &vy, double &vz)
	{
		vx = -cos(EulerAngP)*sin(EulerAngH);
		vy = sin(EulerAngP);
		vz = -cos(EulerAngP)*cos(EulerAngH);
	}

};