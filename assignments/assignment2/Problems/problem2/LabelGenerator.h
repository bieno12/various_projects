#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class LabelGenerator
{
protected:
	int m_index;
	string m_prefix;
public:
	LabelGenerator(string prefix, int index);
	virtual string nextLabel();
};
class FileLabelGenerator : public LabelGenerator
{
private:
	string m_filename;
	ifstream m_file;
	bool m_opened;
public:
	FileLabelGenerator(string prefix, int index, string filename);
	string nextLabel();
};