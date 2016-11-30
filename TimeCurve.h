#ifndef __TIMECURVE_H__
#define __TIMECURVE_H__

#include <vector>
#include "Surface.h"

template <class T>
class TimeCurve
{
	std::vector< Surface<T> > TimeSurfaces;
	int NoOfTimeSteps;

public:
	TimeCurve()
	{
		NoOfTimeSteps = 0;
	};

	~TimeCurve()
	{
		NoOfTimeSteps = 0;
	};

	void SetNoOfTimeSteps(int No_Of_Time_Steps)
	{
		NoOfTimeSteps = No_Of_Time_Steps;
	};

	int GetNoOfTimeSteps()
	{
		return NoOfTimeSteps;
	};

	void CalculateTimeSurfaces(DataTable<T> &FnTable, Variable<T> var[])
	{
		int NoOfDataPointsPerTimeStep = FnTable.GetNoOfRows() / NoOfTimeSteps;

		for (int i = 0; i < NoOfTimeSteps; i++)
		{
			Surface<T> CurrSurface;
			
			int TimeIndex = 0;
			
			CurrSurface.SetTime(FnTable.GetColumnForRowAt(i * NoOfDataPointsPerTimeStep, TimeIndex));
			CurrSurface.TriangulatePoints(i * NoOfDataPointsPerTimeStep, var[1].GetNoOfSteps(), var[2].GetNoOfSteps());
			TimeSurfaces.push_back(CurrSurface);
		}
	}

	std::vector<int> GetSurfaceRow(int TimeIndex, int RowIndex)
	{
		Surface<T> CurrSurface;
		CurrSurface = TimeSurfaces.at(TimeIndex);

		return CurrSurface.GetSurfaceRow(RowIndex);
	}

	int GetNoOfSurfaceRowsForTimeIndex( int TimeIndex )
	{
		Surface<T> CurrSurface;
		CurrSurface = TimeSurfaces.at(TimeIndex);

		return CurrSurface.GetNoOfSurfaceRows();
	}
};

#endif