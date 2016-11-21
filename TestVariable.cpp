#include <stdio.h>
#include <stdlib.h>
#include "Variable.h"

void TestVariable()
{
	Variable <double> TestVar;
	
	double Min = rand();
	double Max = rand();
	double Del = rand();

	printf("Test: Setting the Min value of variable: ");
	TestVar.SetMin(Min);

	if (TestVar.GetMin() == Min)
		printf("Test passed\n\n");
	else 
		printf("Test Failed\n\n");

	printf("Test: Setting the Max value of variable: ");
	TestVar.SetMax(Max);

	if (TestVar.GetMax() == Max)
		printf("Test passed\n\n");
	else
		printf("Test Failed\n\n");
	

	printf("Test: Setting the Delta of variable: ");
	TestVar.SetDelta(Del);

	if (TestVar.GetDelta() == Del)
		printf("Test passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test: Testing the number of steps of variables: ");

	if(TestVar.GetNoOfSteps() == ceil((Max - Min)/Del) )
		printf("Test passed\n\n");
	else
		printf("Test Failed\n\n");
}