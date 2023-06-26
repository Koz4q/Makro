#include <iostream>
#include <math.h>
#include <algorithm>
#include "golden section project.h"

using namespace std;

class Values {
public:

    double a = 5;
    double b = 12;

    double gr = (sqrt(5) - 1) / 2;
    double d = gr * (b - a);

    double x1 = a + d;
    double x2 = b - d;

    double y1_x1 = ((-750 * (1 + 0.5 * exp(-x1 / 5)) - (1.5 * exp(-x1 / 20))) + 2007);
    double y1_x2 = ((-750 * (1 + 0.5 * exp(-x2 / 5)) - (1.5 * exp(-x2 / 20))) + 2007);

    double y2_x1 = (12 * x1) / sqrt(1 + 0.01 * ((x1)*x1)) + 1425;
    double y2_x2 = (12 * x2) / sqrt(1 + 0.01 * ((x2)*x2)) + 1425;

    double y3_x1 = 603 * atan(0.04 * x1) + 760;
    double y3_x2 = 603 * atan(0.04 * x2) + 760;

    int iteration1 = 1;
    int iteration2 = 1;
    int iteration3 = 1;
};



void check_lowest(Values& v);

int main()
{
    class Values v;
    

    //Y1
    calculate_y1(v.iteration1, v.y1_x1, v.y1_x2, v.a, v.x2, v.b, v.x1, v.d, v.gr);

    //set base value
    base_value(v.a, v.b, v.gr, v.d, v.x1, v.x2);

    //Y2
    calculate_y2(v.iteration2, v.y2_x1, v.y2_x2,v.a, v.x2, v.b, v.x1, v.d, v.gr);
    
    //set base value
    base_value(v.a, v.b, v.gr, v.d, v.x1, v.x2);

    //Y3
    calculate_y3(v.iteration3, v.y3_x1, v.y3_x2,v.a, v.x2, v.b, v.x1, v.d, v.gr);

    //best case
    check_lowest(v);
    
    
}

void check_lowest(Values& v)
{
    if (v.y1_x1 < v.y2_x1 && v.y1_x1<v.y3_x1) {
        cout << "The best function is Y1 and the total prize for 167 components is : " << 167 * v.y1_x1 << endl;
    }

    if (v.y2_x1 < v.y1_x1 && v.y2_x1 <v.y3_x1) {
        cout << "The best function is Y2 and the total prize for 167 components is : " << 167 * v.y2_x1 << endl;
    }

    if (v.y3_x1 < v.y1_x1 && v.y3_x1 < v.y2_x1) {
        cout << "The best function is Y3 and the total prize for 167 components is : " << 167 * v.y3_x1 << endl;
    }
}

void calculate_y1(int& iteration1, double& y1_x1, double& y1_x2, double& a, double& x2, double& b, double& x1, double& d, double gr)
{
    while (iteration1 < 52) {

        if (y1_x1 < y1_x2) {

            a = x2;
        }
        else {
            b = x1;
        }

        d = gr * (b - a);
        x1 = a + d;
        x2 = b - d;

        y1_x1 = ((-750 * (1 + 0.5 * exp(-x1 / 5)) - (1.5 * exp(-x1 / 20))) + 2007);
        y1_x2 = ((-750 * (1 + 0.5 * exp(-x2 / 5)) - (1.5 * exp(-x2 / 20))) + 2007);



        //cout << d << endl;
        if (d <= 0.0000009) {
            cout << "Function Y1" << endl;
            cout << "Best case found at iteration: " << iteration1 << "\nat point t = " << a << endl;
            cout << "Value of the function : " << y1_x1 << endl;
            cout << endl;
            
            break;
        }

        iteration1++;
    }
}

void calculate_y2(int& iteration2, double& y2_x1, double& y2_x2, double& a, double& x2, double& b, double& x1, double& d, double gr)
{
    while (iteration2<52) {

        if (y2_x1 < y2_x2) {

            a = x2;
        }
        else {
            b = x1;
        }

        d = gr * (b - a);
        x1 = a + d;
        x2 = b - d;

        y2_x1 = (12 * x1) / sqrt(1 + 0.01 * ((x1)*x1)) + 1425;
        y2_x2 = (12 * x2) / sqrt(1 + 0.01 * ((x2)*x2)) + 1425;



        //cout << d << endl;
        if (d <= 0.0000009) {
            cout << "Function Y2" << endl;
            cout << "Best case found at iteration: " << iteration2 << "\nat point t = " << a << endl;
            cout << "Value of the function : " << y2_x1 << endl;
            cout << endl;
            
            break;
        }

        iteration2++;
    }
}

void calculate_y3(int& iteration3, double& y3_x1, double& y3_x2, double& a, double& x2, double& b, double& x1, double& d, double gr)
{
    while (iteration3 < 52) {

        if (y3_x1 < y3_x2) {

            a = x2;
        }
        else {
            b = x1;
        }

        d = gr * (b - a);
        x1 = a + d;
        x2 = b - d;

        y3_x1 = 603 * atan(0.04 * x1) + 760;
        y3_x2 = 603 * atan(0.04 * x2) + 760;


        //cout << d << endl;
        if (d <= 0.0000009) {
            cout << "Function Y3" << endl;
            cout << "Best case found at iteration: " << iteration3 << "\nat point t = " << a <<  endl;
            cout << "Value of the function : " << y3_x1 << endl;
            cout << endl;
            
            break;
        }

        iteration3++;
    }
}

void base_value(double& a, double& b, double& gr, double& d, double& x1, double& x2)
{
    a = 5;
    b = 12;

    gr = (sqrt(5) - 1) / 2;
    d = gr * (b - a);

    x1 = a + d;
    x2 = b - d;
}
