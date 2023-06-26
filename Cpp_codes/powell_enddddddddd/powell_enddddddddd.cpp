#include <iostream>
#include <math.h>
using namespace std;


double function(double x1, double x2);

class Value {
public:
	int iterations = 0;
	double acc = 0.000000001;
	double d1[2] = { 1,0 };
	double d2[2] = { 0,1 };
	double d3[2];
	double start[2];

	double x2[2], x3[2], x4[2];

	double p_x, p_y;

	double a, min;

	Value(double p_x, double p_y, double d3[2], double x2[2], double x3[2], double x4[2], double a, double min) {

		start[0] = 0;
		start[1] = 0;
	}

};


void print_conditions(Value& v);

void step_x1(Value& v);

void step_x2(Value& v);

void step_x3(Value& v, int& retflag);

int main() {

	Value v = Value(0, 0, 0, 0, 0, 0, 0, 0);

	print_conditions(v);

	while (true) {

		step_x1(v);

		step_x2(v);

		int retflag;
		step_x3(v, retflag);
		if (retflag == 2) break;
	}

}

void step_x3(Value& v, int& retflag)
{
	retflag = 1;
	v.d3[0] = v.x3[0] - v.start[0];
	v.d3[1] = v.x3[1] - v.start[1];

	v.a = -1;
	v.min = function(v.x3[0] + v.a * v.d3[0], v.x3[1] + v.a * v.d3[1]);
	for (double i = -0.99;i <= 1;i += 0.01) {
		if (function(v.x3[0] + i * v.d3[0], v.x3[1] + i * v.d3[1]) < v.min) {
			v.a = i;
			v.min = function(v.x3[0] + v.a * v.d3[0], v.x3[1] + v.a * v.d3[1]);
		}
	}
	v.x4[0] = v.x3[0] + v.a * v.d3[0];
	v.x4[1] = v.x3[1] + v.a * v.d3[1];


	v.p_x = abs(v.x4[0] - v.start[0]);
	v.p_y = abs(v.x4[1] - v.start[1]);

	if (v.p_x <= v.acc && v.p_y <= v.acc) {
		cout << "Minimum is located at x: " << v.x4[0] << " y: " << v.x4[1] << "\nNumber of iterations : " << v.iterations << endl;
		{ retflag = 2; return; };
	}
	v.d1[0] = v.d2[0];
	v.d1[1] = v.d2[1];
	v.d2[0] = v.d3[0];
	v.d2[1] = v.d3[1];
	v.start[0] = v.x4[0];
	v.start[1] = v.x4[1];
	++v.iterations;
}

void step_x2(Value& v)
{
	v.a = -1;
	v.min = function(v.x2[0] + v.a * v.d2[0], v.x2[1] + v.a * v.d2[1]);
	for (double i = -0.99;i <= 1;i += 0.01) {
		if (function(v.x2[0] + i * v.d2[0], v.x2[1] + i * v.d2[1]) < v.min) {
			v.a = i;
			v.min = function(v.x2[0] + v.a * v.d2[0], v.x2[1] + v.a * v.d2[1]);
		}
	}
	v.x3[0] = v.x2[0] + v.a * v.d2[0];
	v.x3[1] = v.x2[1] + v.a * v.d2[1];

}

void step_x1(Value& v)
{
	v.a = -1;
	v.min = function(v.start[0] + v.a * v.d1[0], v.start[1] + v.a * v.d1[1]);
	for (double i = -0.99;i <= 1;i += 0.01) {
		if (function(v.start[0] + i * v.d1[0], v.start[1] + i * v.d1[1]) < v.min) {
			v.a = i;
			v.min = function(v.start[0] + v.a * v.d1[0], v.start[1] + v.a * v.d1[1]);
		}
	}
	v.x2[0] = v.start[0] + v.a * v.d1[0];
	v.x2[1] = v.start[1] + v.a * v.d1[1];

}

void print_conditions(Value& v)
{
	cout << "Accuarancy: " << v.acc << endl;
	cout << "Starting points:\n x0 = " << v.start[0] << " y0 = " << v.start[1] << endl << endl;
}

double function(double x1, double x2) {
	return pow((x1-5),2)+pow((x2+4),2);
}