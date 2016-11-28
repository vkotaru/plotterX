#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <math.h>

template <class T>
class Variable
{
	T Min, Max, Delta;
	int NoOfSteps, NoOfBlocks;
	bool IsAltered;

public:
	void InitializeToZero()
	{
		Min = 0;
		Max = 0;
		Delta = 0;
		NoOfSteps = 0;
		NoOfBlocks = 0;
		IsAltered = false;
	}

	void ComputeDelta() 
	{
		Delta = (GetMax() - GetMin()) /(GetNoOfSteps()-1);
		NoOfBlocks = NoOfSteps-1;
	}

	void ComputeNoOfSteps()
	{
		NoOfSteps = int(ceil((GetMax() - GetMin()) / GetDelta()))+1;
		NoOfBlocks = NoOfSteps-1;
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

	bool IsVariableAltered()
	{
		return IsAltered;
	}

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

	const int GetNoOfBlocks() const
	{
		return NoOfBlocks;
	};

	void SetMin(const T min)
	{
		Min = min;
		IsAltered = true;
	};

	void SetMax(const T max)
	{
		Max = max;
		IsAltered = true;
	}

	void SetDelta(const T delta)
	{
		if (GetNoOfSteps() != 0)
			throw "No of steps already set";

		Delta = delta;
		ComputeNoOfSteps();
		IsAltered = true;
	};

	void SetNoOfSteps(const int No_Of_Steps)
	{
		if (GetDelta() != T(0) )
			throw "Delta already set";

		NoOfSteps = No_Of_Steps;
		ComputeDelta();
		IsAltered = true;
	};
};
#endif