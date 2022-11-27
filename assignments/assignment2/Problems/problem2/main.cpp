#include <iostream>
#include <string>
#include "LabelGenerator.h"


using namespace std;

int main()
{
	LabelGenerator figureNumbers("Figure ", 1);
	LabelGenerator pointNumbers("P", 0);
	cout << "Figure numbers: ";

	for (int i = 0; i < 3; i++)
	{
		cout << figureNumbers.nextLabel() << ", ";
	}
	cout << endl << "Point numbers: ";

	for (int i = 0; i < 5; i++)
	{
		cout << pointNumbers.nextLabel() << ", ";
	}
		cout << endl << "More figures: ";
	
	for (int i = 0; i < 3; i++)
	{
		cout << figureNumbers.nextLabel() << ", ";
	}
	cout << endl;

	FileLabelGenerator figureLabels ("Figure ", 1, "labels.txt");
	cout << "Figure labels: \n";
	for (int i = 0; i < 3; i++)
		cout << figureLabels.nextLabel() << endl;
}