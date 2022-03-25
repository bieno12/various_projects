#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <regex>
#include <cmath>
using namespace std;

#define all(x) begin(x),end(x)
#define in :

//defining a complex number and its various operations
//imaginary number : a + bi

struct complex 
{
	double a;
	double b;

	//overriding how cout prints the complex number;
	friend ostream & operator<<(std::ostream & Str, complex const & v) { 
  		// print something from v to str, e.g: Str << v.getX();
  		Str << v.a << ' ' << ((v.b > 0)? "+ " : "- ") << abs(v.b) << "i";
	  return Str;
	}
	//overloading the plus operator
	complex operator+(complex Z)
	{
		complex res;
		res.a = a + Z.a;
		res.b = b + Z.b;
		return res;
	}
	//overriding the minus operator
	complex operator-(complex Z)
	{
		complex res;
		res.a = a - Z.a;
		res.b = b - Z.b;
		return res;
	}
	//overriding the multiply operator
	complex operator*(complex Z)
	{
		complex res;
		res.a = a * Z.a - b * Z.b;
		res.b = a * Z.b + b * Z.a;
		return res;
	}
	// overriding the divide operator
	complex operator/(const complex Z)
	{
		complex res, conj, this_n;
		this_n.a = a; this_n.b = b;
		conj.a = Z.a;
		conj.b = -Z.b;
		res = this_n * conj;
		res.a /= (Z.a * Z.a + Z.b * Z.b); 
		res.b /= (Z.a * Z.a + Z.b * Z.b); 
		return res;
	}

};


//defining what an operation is
//an operation contains two operands and an operator
//execute method is resposible for performing the operation
//and returning a result
struct operation
{
	complex z1, z2;
	string operator_;
	complex execute()
	{
		if(operator_ == "+")
			return z1 + z2;
		else if(operator_ == "-")
			return z1 - z2;
		else if(operator_ == "*")
			return z1 * z2;
		else if(operator_ == "/")
			return z1 / z2;
		else 
		{
			return {NAN,NAN};
		}
	}
};

//responsible for validing the expression and ensuring that the user enters a valid input
bool validate_extract(string expression, operation &op);


int main()
{
	cout << "Welcome to FCAI Complex Number Calculator\n";
	cout << "enter expression in the form of : \n (a +bi) op (a2 + b2i) \n";

	string expression;
	while (true)
	{
		expression = "";
		cout << "--> ";
		getline(cin, expression);
		if(expression == "exit")
			break;
		operation op;
		bool isvalid = validate_extract(expression, op);
		if(!isvalid)
		{
			cout << "please enter a valid expression\n";
			continue;
		}
		complex result = op.execute();
		cout << result << endl;
	}
	cout << "Thanks for using FCAI Complex Number Calculator =)\n";
}

bool validate_extract(string expression, operation &op)
{
	//"(+-num +- numi) (operator) (+-num +- numi)"                                         "
	regex terms_regex(R"(\(\s*([+-]*\s*\d+(?:\.\d*)?)\s*([+-]\s*\d+(?:\.\d*)?)i\)\s*([\*/\+\-])\s*\(\s*([+-]*\d+(?:\.\d*)?)\s*([+-]\s*\d+(?:\.\d*)?)i\))");
	smatch matches;

	bool valid = regex_match(expression, matches, terms_regex);
	if(!valid)
		return valid;
	vector<string> strs;

	for(int i = 0; i < matches.size(); i++)
	{
		strs.push_back(matches[i].str());
	}
	for(auto &s in strs)
		s.erase(remove(all(s), ' '), end(s));
	
	op.z1.a = stod(strs[1]);
	op.z1.b = stod(strs[2]);
	op.z2.a = stod(strs[4]);
	op.z2.b = stod(strs[5]);
	op.operator_ = strs[3];
	return 1;
}

