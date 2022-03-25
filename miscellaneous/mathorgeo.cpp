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
 
#include <stdio.h>
#include <stdlib.h>

#define all(x) begin(x),end(x)
#define has(s,x) (s.find(x) != s.end())

using namespace std;
using ll = long long;
using ull = unsigned long long;
double r;

struct intPoint
{
	ll x, y;
};
struct Point
{
	double x, y;
};
struct Line
{
	double m;
	double c;
};

double dist(Point A, Point B)
{
	return hypot(A.x-B.x, A.y-B.y);
}
vector<Point> get_intercept_with_circle(Line l)
{
	//using x^2 + y^2 = r^2 and the quadratic equation
	double a = 1.0 + l.m * l.m;
	double b = 2.0 * l.m * l.c;
	double c = l.c * l.c - r * r;
	double d = sqrt(b * b - 4.0 * a * c);

	Point p1;
	p1.x = (-b + d) / (2.0*a);
	p1.y = sqrt(r*r - p1.x * p1.x);
	Point p2;
	p2.x = (-b - d) / (2*a);
	p2.y = sqrt(r*r - p2.x * p2.x);

	return {p1, p2};
}
double angle_at_B(Point A, Point B, Point C)
{
	Point BA = {A.x - B.x, A.y - B.y};
	Point BC = {C.x - B.x, C.y - B.y};
	double cos_theta = (BA.x * BC.x + BA.y * BC.y) / (hypot(BA.x, BA.y)*hypot(BC.x, BC.y));
	return acos(cos_theta);
}
Point get_intersection_point(intPoint p1, intPoint p2, intPoint p3, intPoint p4)
{
	//using m1*x +c1 = m2*x + c2
	Point intersect;
	if(p1.x == p2.x)
	{
		intersect.x = double(p1.x);
		intersect.y = double(p4.y - p3.y)*double(intersect.x - double (p3.x)) / double(p4.x-p3.x);
		return intersect;
	}
	if(p3.x == p4.x)
	{
		intersect.x =double(p3.x);
		intersect.y = double(p2.y - p1.y)*double(intersect.x - double (p1.x)) / double(p2.x-p1.x);
		return intersect;
	}

	double m1 = double(p2.y - p1.y) / double(p2.x - p1.x);
	double m2 = double(p4.y - p3.y) / double(p4.x - p3.x);
	double c1 = double(p1.y) - m1 * double(p1.x);
	double c2 = double(p3.y) - m2 *double (p3.x);

	intersect.x = (c2 - c1) / (m1 - m2);

	intersect.y = m1 * intersect.x + c1;
	return intersect;
}
int main()
{
	freopen("matheo.in", "r", stdin);
	ll t;
	intPoint p1, p2, p3, p4;
	cin >> t;
	while(t--)
	{
		cin >> r;
		cin >> p1.x >> p1.y >> p2.x >> p2.y;
		cin >> p3.x >> p3.y >> p4.x >> p4.y; 

		vector<Point> intercept1, intercept2;
		Point intersection;
		if(p1.x == p2.x)
		{
			intercept1.push_back({double(p1.x) , sqrt(r*r - double(p1.x*p1.x))});
			intercept1.push_back({double(p1.x), -sqrt(r*r - double(p1.x*p1.x))});
		}
		else
		{
			Line line1;
			line1.m = double(p1.y -p2.y)/ double(p1.x - p2.x);
			line1.c = double(double(p1.y) - line1.m * double(p1.x));
			intercept1 = get_intercept_with_circle(line1);
		}

		if(p3.x == p4.x)
		{

			intercept2.push_back({double(p3.x), sqrt(r*r - double(p3.x*p3.x))});
			intercept2.push_back({double(p3.x), -sqrt(r*r - double(p3.x*p3.x))});
		}
		else
		{
			Line line2;
			line2.m = double(p3.y -p4.y)/ double(p3.x - p4.x);
			line2.c = double(double(p3.y) - line2.m * double(p3.x));
			intercept2 = get_intercept_with_circle(line2);
		}

		intersection = get_intersection_point(p1,p2,p3,p4);
		double center, angle;
		// area of first section intercept1[0] and  intercept2[0]
		center = angle_at_B(intercept1[0], {0,0}, intercept2[0]);
		angle = angle_at_B(intercept1[0], intersection, intercept2[0]);
		double Area1 = 0.5 * r * r *(center - sin(center));
		Area1 += 0.5 * dist(intercept1[0], intersection) * dist(intercept2[0], intersection) * sin(angle);

		//area of second intercept1[0] and intercept2[1];
		center = angle_at_B(intercept1[0], {0,0}, intercept2[1]);
		angle = angle_at_B(intercept1[0], intersection, intercept2[1]);
		double Area2 = 0.5 * r * r *(center - sin(center));
		Area2 += 0.5 * dist(intercept1[0], intersection) * dist(intercept2[1], intersection) * sin(angle);

		//area of third intercept[1] and intercept2[0]

		center = angle_at_B(intercept1[1], {0,0}, intercept2[0]);
		angle = angle_at_B(intercept1[1], intersection, intercept2[0]);
		double Area3 = 0.5 * r * r *(center - sin(center));
		Area3 += 0.5 * dist(intercept1[1], intersection) * dist(intercept2[0], intersection) * sin(angle);
		
		// area of fourth intercept1[1] and intercept2[1]
		center = angle_at_B(intercept1[1], {0,0}, intercept2[1]);
		angle = angle_at_B(intercept1[1], intersection, intercept2[1]);
		double Area4 = 0.5 * r * r *(center - sin(center));
		Area4 += 0.5 * dist(intercept1[1], intersection) * dist(intercept2[1], intersection) * sin(angle);


		double a = max(Area1, max(Area2, max(Area3, Area4)));
		cout << fixed << showpoint << setprecision(4) << a / (r*r* M_PI) * 100 << endl;
	}
}
