#ifndef __MOUSE_INPUTS__
#define __MOUSE_INPUTS__

class MouseInputs
{
public:
	int lb,mb,rb,mx,my;
	int prev_lb;
	int LEFT_BUTTON_CLICK;
	int MOUSE_EVENT_CATCH;

	MouseInputs()
	{
		lb = 0; mb = 0; rb = 0; mx = 0; my = 0;
		LEFT_BUTTON_CLICK = 0;
		MOUSE_EVENT_CATCH = 0;
		prev_lb = 0;
	};
	~MouseInputs()
	{
		lb = 0; mb = 0; rb = 0; mx = 0; my = 0;
		LEFT_BUTTON_CLICK = 0;
		MOUSE_EVENT_CATCH = 0;
		prev_lb = 0;
	};

	void SetMouseState(const int l, const int m, const int r, 
							const int x, const int y)
	{
		lb = l; mb = m; rb = r;
		mx = x; my = y;
		if (prev_lb == NOT_ACTIVE && lb == ACTIVE)
		{
			LEFT_BUTTON_CLICK = ACTIVE;
			printf("left button clicked\n");
		}
		else
		{
			LEFT_BUTTON_CLICK = NOT_ACTIVE;
		}

		/*if(LEFT_BUTTON_CLICK == NOT_ACTIVE && (prev_lb==NOT_ACTIVE && lb== ACTIVE))
		{
			LEFT_BUTTON_CLICK = ACTIVE;
			printf("LEFT_BUTTON_CLICK\n");
			printf("lb: %d mb: %d rb: %d mx: %d my: %d \n",lb,mb,rb,mx,my);	
		}
		else if(LEFT_BUTTON_CLICK == ACTIVE && (prev_lb==NOT_ACTIVE && lb== ACTIVE))
		{
			LEFT_BUTTON_CLICK = NOT_ACTIVE;
			printf("LEFT_BUTTON_CLICK NOT\n");
			printf("lb: %d mb: %d rb: %d mx: %d my: %d \n",lb,mb,rb,mx,my);	
		}*/
		prev_lb = lb;
	}
};


#endif
