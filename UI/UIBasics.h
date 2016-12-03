#ifndef __UI_BASICS_H__
#define __UI_BASICS_H__


#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

#include "fssimplewindow.h"
#include "ysglfontdata.h"

#include "DrawFigures.h"
#include "UIConstants.h"


class UIBasics : public DrawFigures<double>
{
public:
	UIBasics()
	{};
	~UIBasics(){};

	void DisplayBackground(const double x1, const double y1,
												const double wid, const double hei,
												const int r, const int g, const int b)
	{
		glColor3ub(r, g, b);
		DrawRectangle2D(x1,y1,x1+wid,y1+hei,GL_QUADS);
	};

	void DrawTextDesiredSize(int X, int Y, int wid, int hei, const char str[])
	{
		auto fontDispList = glGenLists(256);
		int selHeight, selWidth, width, height;
		FsGetWindowSize(width, height);
		YsGlSelectAndUseFontBitmapByHeight(&selWidth, &selHeight, fontDispList, height / 50);
		glRasterPos2d(X + wid / 2 - strlen(str) / 2 * selWidth, Y+hei/2+selHeight/2);
		glListBase(fontDispList);
		glCallLists((int)strlen(str), GL_UNSIGNED_BYTE, str);
		for (int i = 0; i < 256; i++)
			glDeleteLists(fontDispList + i, 1);
	}

	void DisplayTextMsgAt(const double x, const double y, const char msg[],
		const int size,
		const int txt_r, const int txt_g, const int txt_b)
	{
		glColor3ub(txt_r, txt_g, txt_b);
		glRasterPos2d(x, y);

		  switch(size)
		  {
		  	case 0: YsGlDrawFontBitmap6x7(msg); 
		  			break;
			  case 1: YsGlDrawFontBitmap6x8(msg); 
		  			break;
			  case 2: YsGlDrawFontBitmap6x10(msg); 
		  			break;
		  	case 3: YsGlDrawFontBitmap7x10(msg); 
		  			break;
			  case 4: YsGlDrawFontBitmap8x8(msg); 
		  			break;
			  case 5: YsGlDrawFontBitmap8x12(msg); 
		  			break;
		  	case 6: YsGlDrawFontBitmap10x14(msg); 
		  			break;
			  case 7: YsGlDrawFontBitmap12x16(msg); 
		  			break;
			  case 8: YsGlDrawFontBitmap16x20(msg); 
		  			break;
		  	case 9: YsGlDrawFontBitmap16x24(msg); 
		  			break;
			  case 10: YsGlDrawFontBitmap20x28(msg); 
		  			break;
			  case 11: YsGlDrawFontBitmap20x32(msg); 
		  			break;
		  	case 12: YsGlDrawFontBitmap24x40(msg); 
		  			break;
			  case 13: YsGlDrawFontBitmap28x44(msg); 
		  			break;
			  case 14: YsGlDrawFontBitmap32x48(msg); 
		  			break;
			  default: YsGlDrawFontBitmap8x12(msg); 
		  			break;
		  }
	}

};


#endif