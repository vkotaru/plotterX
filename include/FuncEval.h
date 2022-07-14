#ifndef __FUNC_EVAL_H__
#define __FUNC_EVAL_H__

#include <math.h>
#include "Variable.h"
#include "DataTable.h"
#include "Parser.h"

template <class T>
class FunctionEval
{
	bool Debug;

	void AddRowToDataTable(T t, T x, T y, T z, DataTable<T> &FnTable)
	{
		std::vector<T> row;
		row.push_back(t);
		row.push_back(x);
		row.push_back(y);
		row.push_back(z);
		FnTable.AppendRow(row);
	};

	void UpdateVariableZ(Variable<T> &VarZ, T CurrZ)
	{
		if (VarZ.IsVariableAltered())
		{
			VarZ.SetMin( CurrZ > VarZ.GetMin()? VarZ.GetMin() : CurrZ );
			VarZ.SetMax( CurrZ > VarZ.GetMax()? CurrZ : VarZ.GetMax() );
		}
		else
		{
			VarZ.SetMin(CurrZ);
			VarZ.SetMax(CurrZ);
		}
	};

public:

	FunctionEval()
	{
		Debug = false;
	}

	~FunctionEval()
	{
		Debug = false;
	}

	void DebugModeOn()
	{
		Debug = true;
	}

	void DebugModeOff()
	{
		Debug = false;
	}

	void Parser2DataTable(DataTable<T> &FnTable, const int NoOfVariables )
	{
		if( Debug )
			FnTable.SetNoOfVariables(4);
		else
			FnTable.SetNoOfVariables(NoOfVariables);
	};

	void Evaluate(DataTable<T> &FnTable, Variable<T> Var[], Parser &FnParser)
	{
		for (T i = 0; i < Var[0].GetNoOfSteps(); i++)
		{
			for (T j = 0; j < Var[1].GetNoOfSteps(); j++)
			{
				for (T k = 0; k < Var[2].GetNoOfSteps(); k++)
				{
					auto t = Var[0].GetMin() + i * Var[0].GetDelta();
					auto x = Var[1].GetMin() + j * Var[1].GetDelta();
					auto y = Var[2].GetMin() + k * Var[2].GetDelta();
					
					T z;
					if (Debug)
						z = x*y*t;
					else
						z = FnParser.Evaluate(x, y, t);
					
					AddRowToDataTable(t, x, y, z, FnTable);
					UpdateVariableZ( Var[3], z);
				}
			}
		}
	}
};

#endif