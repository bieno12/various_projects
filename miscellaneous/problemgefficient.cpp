#include<iostream>
#include<cmath>
using namespace std;

int method1(int k, int s)
{
	k = min(k, s);

	int start = max(0, s -2 * k - 1);

	int end = min(k, s - k);
	
	int n = (end - start + 1);
	
	int count = (2 * k + 1 - s) * n + n * (start + end) / 2;
	
	if(k > s - k)
		count += (s + 1) * (2 * k - s) / 2;
	
	return count;
}

int method2(int k, int s)
{
	int count = 0;
	for(int x = 0; x <=k; x++)
	{
		count +=  max(0,2 * min(k, s - x) + 1 - (s - x));
	}
	return count;
}

int main(){
	int k, s;
	cin >> k >> s;
	cout << method1(k,s);
	//cout << "incorrect: "<< method1(k,s)<< ", correct: " << method2(k,s) <<endl;
}


/*
x + y = s, s = 3, k = 2; 
0   3
1   2
2   1
3   0 
s + 1 - 2(s - k) = 2k + 1 - s

rule = 2k + 1  - s + z


x + y  = s - z; k;
for z = 0;
x + y = s , k;
2k + 1 - (s)

from z = 0 to z = k
sum of (2* min(k, s - z) + 1 - (s - z))
z >= s - 2k - 1
#first constraint
z >=  s - 2 * k - 1  
#second constraint
z <= s - k

 max(0, s - 2 * k - 1) <= z  <= s - k


*/

























/*
(start + end)* n/2, (10 + 13) * 
max(0,2 * min(k, s - x) + 1 - (s - x));
k <= s - x
x <= s - k

case#1:  x <= s - k
2 * k + 1 - (s - x) >= 0
2k + 1 - s + x >= 0
x >= s - 2k - 1 

start = max(0, s - 2k - 1)

end = min(k, s - k)

sum from start to end of (2 * k + 1 - s + x))

count = (end - start + 1)*(2 * k + 1 - s) + (end - start + 1) * (start + end) / 2



case#2: x > s - k,and k > s - k

2 * (s - x) + 1 - (s - x)
(s - x) + 1 >= 0
s + 1 >= x
x <= s + 1;

start = s - k + 1; end = k;
sum of start to end of (s + 1 - x);

sum of n1 to n2 = (n2 - n1 + 1)/2 *(n1 + n2);
count += (k - (s - k + 1) + 1)(s + 1) - (k - (s - k + 1) + 1) * (s - k + 1 + k) / 2
= 
*/