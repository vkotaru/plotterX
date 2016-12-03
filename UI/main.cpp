#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "UserInterface.h"
#include "ysglfontdata.h"
UserInterface UI;

int main(void)
{
	srand((int)time(nullptr));
	UI.Initialize();

	int lb,mb,rb,mx,my;
	FsPassedTime();
	while (1)
	{
		//FSKEY_ESC != FsInkey()
		FsPollDevice();

		UI.mouse.MOUSE_EVENT_CATCH = FsGetMouseEvent(lb,mb,rb,mx,my);
		// if(FSMOUSEEVENT_MOVE == UI.mouse.MOUSE_EVENT)
		{
			UI.mouse.SetMouseState(lb,mb,rb,mx,my);
			UI.Polling();
/*			printf("lb: %d mb: %d rb: %d mx: %d my: %d \n",lb,mb,rb,mx,my);	*/		
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UI.AutoScaleWindow();
		FsSwapBuffers();
		FsSleep(25);
	}

	FsCloseWindow();

	return 0;
}