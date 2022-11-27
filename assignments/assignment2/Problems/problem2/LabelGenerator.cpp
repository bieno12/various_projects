#include "LabelGenerator.h"

using namespace std;

LabelGenerator::LabelGenerator(string prefix, int index) : m_prefix(prefix), m_index(index)
{
}
string LabelGenerator::nextLabel()
{
	return m_prefix + to_string(m_index++);
}

FileLabelGenerator::FileLabelGenerator(string prefix, int index, string filename)
	: LabelGenerator(prefix, index), m_filename(filename)
{
	m_file.open(filename);
	m_opened = m_file.is_open();

}
string FileLabelGenerator::nextLabel()
{
	string line;
	if(m_opened && getline(m_file, line))
	{
		m_opened = 1; 
	}
	else
		m_opened = 0;
	return m_prefix + to_string(m_index++) + " " + line   + ".";
}