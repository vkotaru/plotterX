#ifndef __FUNC_EVAL_H__
#define __FUNC_EVAL_H__


class FunctionEval
{
private:

public:
	FunctionEval();
	~FunctionEval();

	void Parser2DataTable(const Parser parser, DataTable FnTable);
	void Evaluate(const Parser parser, const Variable var[], DataTable FnTable);
};


#endif







