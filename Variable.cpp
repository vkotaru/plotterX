#include <math.h>
#include "Variable.h"

template <class T> 
Variable<T>::Variable()
{
	Min = 0;
	Max = 0;
	Delta =0;
	NoOfSteps = 0;
}

template <class T> 
Variable<T>::~Variable()
{
	Min = 0;
	Max = 0;
	Delta = 0;
	NoOfSteps = 0;
}

template <class T> 
const T Variable<T>::GetMin() const
{
	return Min;
}

template <class T> 
const T Variable<T>::GetMax() const
{
	return Max;
}

template <class T> 
const T Variable<T>::GetDelta() const
{
	if (Delta != 0)
		return Delta;

	if (GetNoOfSteps() == 0)
		throw "Error! Step or Delta not defined";

	Delta = T(( GetMin() - GetMax() ) / NoOfSteps());

	return Delta;
}

template <class T> 
const int Variable<T>::GetNoOfSteps()
{
	if (NoOfSteps != 0)
		return NoOfSteps;

	if (GetDelta() == 0)
		throw "Error! Step or Delta not defined";

	NoOfSteps = ceil((GetMin() - GetMax()) / GetDelta());
	
	return NoOfSteps;
}

template <class T> 
void Variable<T>::SetMin(const T min)
{
	Min = min;
}

template <class T> 
void Variable<T>::SetMax(const T max)
{
	Max = max;
}

template <class T> 
void Variable<T>::SetDelta(const T delta)
{
	Delta = delta;
}

template <class T> 
void Variable<T>::SetNoOfSteps(const int No_Of_Steps)
{
	NoOfSteps = No_Of_Steps;
}