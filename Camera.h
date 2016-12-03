#ifndef __CAMERA_H__
#define __CAMERA_H__

#include<math.h>
#include "fssimplewindow.h"

class Camera
{
	double PosX, PosY, PosZ;
	double EulerAngH, EulerAngP, EulerAngB;

	double fov, nearZ, farZ;

public:
	Camera()
	{
		PosX = 5;
		PosY = 5;
		PosZ = 5;
		EulerAngH = 0;
		EulerAngP = -70;
		EulerAngB = 0;

		fov = 60; 
		nearZ = 0.1;
		farZ = 100.0;
	};

	void SetPosX(double X)
	{
		PosX = X;
	};

	void SetPosY(double Y)
	{
		PosY = Y;
	};

	void SetPosZ(double Z)
	{
		PosZ = Z;
	};

	double GetPosX()
	{
		return PosX;
	};

	double GetPosY()
	{
		return PosY;
	};

	double GetPosZ()
	{
		return PosZ;
	};

	void SetPosXYZ(double X, double Y, double Z)
	{
		SetPosX(X);
		SetPosY(Y);
		SetPosZ(Z);
	};

	void SetEulerAngH( double H ) 
	{
		EulerAngH = H;
	};
	void SetEulerAngP( double P )
	{
		EulerAngP = P;
	};

	void SetEulerAngB( double B )
	{
		EulerAngB = B;
	}

	void SetEulerAngles(double H, double P, double B)
	{
		SetEulerAngB(B);
		SetEulerAngH(H);
		SetEulerAngP(P);
	};

	double GetEulerAngH()
	{
		return EulerAngH;
	};

	double GetEulerAngP()
	{
		return EulerAngP;
	};

	double GetEulerAngB()
	{
		return EulerAngB;
	};

	void ChangeCameraWithInput( int Key )
	{
		switch (Key)
		{
			case FSKEY_K:
						SetPosZ(GetPosZ() + 1); 
						break;
			case FSKEY_I:
						SetPosZ(GetPosZ() - 1);
						break;
			case FSKEY_J:
						SetPosX(GetPosX() + 1);
						break;
			case FSKEY_L:
						SetPosX(GetPosX() - 1);
						break;
			case FSKEY_U:
						SetPosY(GetPosY() + 1);
						break;
			case FSKEY_O:
						SetPosY(GetPosY() - 1);
						break;
			case FSKEY_D:
						SetEulerAngH(GetEulerAngH() - 1);
						break;			
			case FSKEY_A:
						SetEulerAngH(GetEulerAngH() + 1);
						break;
			case FSKEY_W:
						SetEulerAngP(GetEulerAngP() - 1);
						break;
			case FSKEY_S:
						SetEulerAngP(GetEulerAngP() + 1);
						break;
			case FSKEY_Q:
						SetEulerAngB(GetEulerAngB() - 1);
						break;
			case FSKEY_E:
						SetEulerAngB(GetEulerAngB() + 1);
						break;
		};
	};

	void SetUpCameraProjection(void)
	{
		int ScreenWidth, ScreenHeight;
		double AspectRatio;

		FsGetWindowSize(ScreenWidth, ScreenHeight);
		AspectRatio = double(ScreenWidth/ScreenHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, AspectRatio, nearZ, farZ);
	}

	void SetUpCameraTransformation(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-PosX, -PosY, -PosZ);
		glRotated(EulerAngB, 0.0, 0.0, 1.0);  // Rotation about Z axis
		glRotated(EulerAngP, 1.0, 0.0, 0.0);  // Rotation about X axis
		glRotated(EulerAngH, 0.0, 1.0, 0.0);  // Rotation about Y axis
	}

	/*void GetForwardVector(double &vx, double &vy, double &vz)
	{
		vx = -cos(EulerAngP)*sin(EulerAngH);
		vy = sin(EulerAngP);
		vz = -cos(EulerAngP)*cos(EulerAngH);
	}*/
};
#endif