#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdio.h>
#include "Constants.h"

class Errors
{
public:
	void PrintError(const char *ErrorMsg)
	{
		printf("\n\n%s\n", ErrorMsg);
	}

	void CatchError(int ErrorCode)
	{
		switch (ErrorCode)
		{
		case Error_DataTable_Invalid_Variable_No: 
													PrintError("Error: Invalid Number of variables in datatable");
													break;
		case Error_DataTable_Invalid_No_Of_Data_Val:
													PrintError("Error: Invalid Number of datavalues being inserted in datatable");
													break;
		case Error_DataTable_Invalid_Index:
													PrintError("Error: Invalid Index being accessed in the datatable");
													break;
		case Error_Variable_No_Of_Steps_Already_Set:
													PrintError("Error: No of steps already set for the variable");
													break;
		case Error_Variable_Delta_Already_Set:
													PrintError("Error: Delta set for the variable");
													break;
		default:
			break;
		}
	}
};

#endif