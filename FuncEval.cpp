
#include "FuncEval.h"
#include "Variable.h"
#include "DataTable.h"
#include "Parser.h"



void FunctionEval::Parser2DataTable(const Parser parser, DataTable FnTable)
{
	FnTable.SetNoOfVariables(parser.GetNoOfVariables());
}

void FunctionEval::Evaluate(const Parser parser, const Variable var[], DataTable FnTable)
{
	// Looping over different variables
	for(int i = 0; i < parser.GetNoOfVariables(); ++i)
	{
		// Looping from Min to Max within each variables 
		for(auto j = var[i].GetMin(); j<=var[i].GetMax(); j+=var[i].GetDelta())
		{
			
		}
	}
}

