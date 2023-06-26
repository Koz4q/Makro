#include <iostream>
#include <math.h>
using namespace std;
float a;
float b;
float d;
double x1;
double x2;
int i;
const float dr = 0.6180;

float Alpha;

float Gradient[2] = { 2,2 };

float randomx0[2] = { 3,2 };
float LastIteration[2] = { 999,999 };




int main()
{

	while (abs(LastIteration[0] - randomx0[0]) > 0.01 && abs(LastIteration[1] - randomx0[1]) > 0.01) {

		LastIteration[0] = randomx0[0];
		LastIteration[1] = randomx0[1];

		a = -9.0;
		b = 10.0;

		while ((abs(a - b)) > 0.0001f)
		{
			d = abs(a - b);//returns the distance between points
			d = d * dr;

			x1 = pow(randomx0[0] + (Gradient[0] * randomx0[0]) * (a + d), 2) + pow(randomx0[1] + (Gradient[1] * randomx0[1]) * (a + d), 2); //Enter Your Function where a+d = alpha

			x2 = pow(randomx0[0] + (Gradient[0] * randomx0[0]) * (b - d), 2) + pow(randomx0[1] + (Gradient[1] * randomx0[1]) * (b - d), 2);//Enter Your Function where b-d=  alpha


			if (x1 < x2)
			{

				a = b - d;

			}
			else
			{
				if (x1 > x2)
				{
					b = a + d;
				}
			}
		}

		Alpha = a;

		randomx0[0] = randomx0[0] + (randomx0[0] * Gradient[0] * Alpha);
		randomx0[1] = randomx0[1] + (randomx0[1] * Gradient[1] * Alpha);

	}


	//cout << a << " x value\n";

	//cout << x1 << " y value\n";

	std::cout.precision(3);

	std::cout << randomx0[0] + (randomx0[0] * Gradient[0] * Alpha) << " x1 after First Iteration\n";

	std::cout << randomx0[1] + (randomx0[1] * Gradient[1] * Alpha) << " x2 after First Iteration\n";


	return 0;
}