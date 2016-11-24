#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <math.h>

template <class T>
class Variable
{
	T Min, Max, Delta;
	int NoOfSteps;
public:
	void InitializeToZero()
	{
		Min = 0;
		Max = 0;
		Delta = 0;
		NoOfSteps = 0;
	}

	void ComputeDelta() 
	{
		Delta = (GetMax() - GetMin()) / GetNoOfSteps();
	}

	void ComputeNoOfSteps()
	{
		NoOfSteps = int(ceil((GetMax() - GetMin()) / GetDelta()));
	}

public:
	Variable(void)
	{
		InitializeToZero();
	};

	~Variable(void)
	{
		InitializeToZero();
	};

	const T GetMin() const
	{
		return Min;
	};

	const T GetMax() const
	{
		return Max;
	}

	const T GetDelta() const
	{
		return Delta;
	};

	const int GetNoOfSteps() const
	{
		return NoOfSteps;
	};

	void SetMin(const T min)
	{
		Min = min;
	};

	void SetMax(const T max)
	{
		Max = max;
	}

	void SetDelta(const T delta)
	{
		if (GetNoOfSteps() != 0)
			throw "No of steps already set";

		Delta = delta;
		ComputeNoOfSteps();
	};

	void SetNoOfSteps(const int No_Of_Steps)
	{
		if (GetDelta() != T(0) )
			throw "Delta already set";

		NoOfSteps = No_Of_Steps;
		ComputeDelta();
	};
};
#endif
