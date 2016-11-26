#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <vector>
#include "DataTable.h"
#include "Variable.h"

template <class T>
class Surface
{
	DataTable<int> TriangleIndices;
	T time;

	std::vector<int> FormRow(int Index1, int Index2, int Index3)
	{
		std::vector<int> Row;
		Row.push_back(Index1);
		Row.push_back(Index2);
		Row.push_back(Index3);

		return Row;
	}

public:
	Surface()
	{
		time = 0;
		TriangleIndices.SetNoOfVariables(3);
	};

	~Surface()
	{
		time = 0;
	};

	void TriangulatePoints(int StartingIndex, int NoOfDataPoints)
	{
		for (int i = 0; i < NoOfDataPoints; i++)
		{
			TriangleIndices.AppendRow(	FormRow(StartingIndex + i, StartingIndex + i + 1, StartingIndex + i + 2)	);
		}
	}

	void SetTime(T Time)
	{
		time = Time;
	}

	T GetTime()
	{
		return time;
	}
	
	std::vector<int> GetSurfaceRow( int RowIndex )
	{
		return TriangleIndices.GetRowAt(RowIndex);
	}
};

#endif