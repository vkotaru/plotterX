#include<vector>

class DataTable
{
private:
	int NoOfVariables;
	int NoOfRows;
	std::vector< std::vector<double> > Data;
public:
	DataTable();
	~DataTable();

	void SetNoOfVariables(const int NoOfVar);
	const int GetNoOfVariables() const;
	const int GetNoOfRows() const ;

	void AppendRow(const std::vector<double> row);
	void SetRowAt(const std::vector<double> row, const int index);

	const std::vector<double> GetRowAt(const int index) const;
};








