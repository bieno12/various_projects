#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator> 
#include <string>
#include <set>
#include <bitset>
#include <stdio.h>
#include <vector>
#include <numeric>
#include <numbers>
#include <map>
#include <sstream>
#include <array>
#include <stdio.h>
#include <stdlib.h>

#define NaN INT_MIN;
#define all(x) begin(x),end(x)
#define has(s,x) (s.find(x) != s.end())

using namespace std;
using ll = long long;
using ull = unsigned long long;
vector<int> arr;
ll n, k;

int string_to_int(string num_str)
{
	int i = 0;
	int sign = 1;
	while (i < num_str.size())
	{
		if(isspace(num_str[i]) || num_str[i] == '+')
			i++;
		else if(num_str[i] == '-')
		{
			sign *= -1;
			i++;
		}
		else
			break;
	}
	int num_len = 0;
	while(isdigit(num_str[i + num_len]))
		num_len++;
	if(num_len == 0)
		return NaN;

	int num = 0;
	while(num_len > 0)
	{
		num += (num_str[i] - '0') * pow(10, num_len - 1);
		i++;
		num_len--;
	}
	return num * sign;

}

int string_to_int(const char * num_str)
{
	int i = 0;
	int sign = 1;
	int num_len = 0;

	while (true)
	{
		if(isspace(num_str[i]) || num_str[i] == '+')
			i++;
		else if(num_str[i] == '-')
		{
			sign *= -1;
			i++;
		}
		else
			break;
	}
	while(isdigit(num_str[i + num_len]))
	{
		num_len++;
	}
	if(num_len == 0)
		return NaN;

	int num = 0;
	while(num_len > 0)
		num += (num_str[i++] - '0') * pow(10, num_len-- - 1);
	return num * sign;
}

int main()
{
	const char * str = " ++--10022";
	cout << string_to_int(str);
}
