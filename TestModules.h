#ifndef __TEST_MODULES_H__
#define __TEST_MODULES_H__

class TestModules
{
public:
	void TestMsg(const char *msg)
	{
		printf("\nTest: %s", msg);
	};

	void FunctionTest( bool TestVal )
	{
		if(TestVal)
			printf("Test passed\n");
		else
			printf("Test Failed\n");
	};
};

#endif