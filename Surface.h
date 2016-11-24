#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "DataTable.h"
#include "Variable.h"

template <class T>
class Surface
{
private:
	int NStepsOfT;
	int NPoints;

	void Initialize()
	{
		NStepsOfT = 0;
		NPoints = 0;
	}

public:

	std::vector<DataTable<int> > Index;
	// std::vector<DataTable<T> > Points;
	std::vector<T> Time;

	Surface()
	{
		Initialize();
	}

	~Surface()
	{
		Initialize();
	}

	void CalculateParams(const Variable<T> Var[])
	{
		NStepsOfT = Var[0].GetNoOfSteps();
		NPoints = 1;
		for (int i(1); i<4; ++i)
		{
			NPoints*=Var[i].GetNoOfSteps();	
		}
	}

	void CreateSurface(const Variable<T> Var[], const DataTable<T> &FnTable)
	{

		CalculateParams(Var);

		
		for(int i=0; i<NStepsOfT; ++i)
		{

			DataTable<int> tempIndex;
			// DataTable<T> tempPoints;
			tempIndex.SetNoOfVariables(3);	// Index-> 1, 2, 3
			// tempPoints.SetNoOfVariables(3);	// Points-> x, y, z 
		
			// tempPoints = FnTable.ExtractDataFromTable(i*NPoints, (i+1)*NPoints);
			std::vector<std::vector<int> > tempIndexVector;
		
			for(int j=0; j<NPoints-2; ++j)
			{
				std::vector<int> ind;
				ind.push_back(j+i*(NPoints)); ind.push_back(j+1+i*(NPoints)); ind.push_back(j+2+i*(NPoints));
				tempIndexVector.push_back(ind);
			}
			tempIndex.SetDataVector(tempIndexVector);

			Time.push_back(FnTable.GetColumnForRowAt(i*NPoints,0));
			Index.push_back(tempIndex);
			// Points.push_back(tempPoints);
		}

	}

};




#endif



