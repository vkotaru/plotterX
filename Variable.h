template <class T>
class Variable
{
	T Min, Max, Delta;
	int NoOfSteps;

public:
	Variable();
	~Variable();
	
	const T GetMin() const;
	const T GetMax() const;
	const T GetDelta() const;
	const int GetNoOfSteps();

	void SetNoOfSteps( const int No_Of_Steps );
	void SetMin( const T min);
	void SetMax( const T max);
	void SetDelta( const T delta );
};