#include <iostream>
#include <cmath>
#include <math.h>


using namespace std;

class Gauss {
public:
    double x;
    double y;

};

class Stepest {
public:
    double x;
    double y;
};

class Value {
public:
    int  n;

    double a, b;
    double x0, y0;
    double gr = (sqrt(5) - 1) / 2;

    double acc;
    int it;

    Value() {

        a = -1;
        b = 1;
        n = 16;
        x0 = 0.7;
        y0 = -0.7;

        acc = 0.000000000000001;
        it = 1000;
    }

};

class Gradient {
public:
    double dx;
    double dy;

};



double function(double x, double y);

Gradient gradient_of(double x, double y);

double golden_for_g(double a, double b, double acc, double gr, double x0, double y0, bool x_or_y);
double golden_for_step(double a, double b, double acc, double gr, double x, double y);


Gauss gaussSeidel(double x0, double y0, double a, double b, double acc, int n);
Stepest steepestDescent(double x0, double y0, double a, double b, double acc, int n);


int main()
{

    Value v = Value();

    Gauss gauss_siedel = gaussSeidel(v.x0, v.y0, v.a, v.b, v.acc, v.it);
    //Stepest steepest_desent = steepestDescent(v.x0, v.y0, v.a, v.b, v.acc, v.it);

    cout << "Initial points:\nx0: " << v.x0 << " y0: " << v.y0 << endl;
    cout << "Range of the function:\nx=< " << v.a << ", " << v.b << ">, y=< " << v.a << ", " << v.b << ">" << endl;
    cout << "Accuracy: " << v.acc << endl << endl;
    cout << "Gauss Seidel Method: " << endl;
    cout << "x: " << gauss_siedel.x << " y: " << gauss_siedel.y << endl << endl;
    cout << "Steepest descent method: " << endl;
    //cout << "x: " << steepest_desent.x << " y: " << steepest_desent.y << endl;

}

double function(double x, double y)
{
    double returned;
    
    returned = -(((2 - (pow(y, 2)) * pow(2.718, -sin(2 * x - 1)))));

    return returned;
}


Gradient gradient_of(double x, double y)
{
    Gradient returned;

    returned.dx = -(2 * (y * y - 2) * pow(2.718, sin(1 - 2 * x) * cos(1 - 2 * x)));
    returned.dy = -(-2 * y * pow(2.718, sin(1 - 2 * x)));

    return returned;
}


double golden_for_g(double a, double b, double acc, double gr, double x0, double y0, bool x_or_y)
{
    int n = 0;
    double x1 = b - gr * (b - a);
    double x2 = a + gr * (b - a);
    if (x_or_y == true)
    {

        while (!(b - a < acc))
        {
            double fx1 = function(x0 + x1, y0);
            double fx2 = function(x0 + x2, y0);

            if (fx1 < fx2)
            {
                
                a = x1;
                x1 = x2;
                x2 = a + gr * (b - a);
            }
            else
            {
                b = x2;
                x2 = x1;
                x1 = b - gr * (b - a);
            }
            n++;
        }
        return (x2 + x1) / 2.0;
    }
    else
    {

        while (!(b - a < acc))
        {
            double fx1 = function(y0, x0 + x1);
            double fx2 = function(y0, x0 + x2);
            if (fx1 >= fx2)
            {
                a = x1;
                x1 = x2;
                x2 = a + gr * (b - a);
            }
            else
            {
                b = x2;
                x2 = x1;
                x1 = b - gr * (b - a);
            }
            n++;
        }
        return (x2 + x1) / 2.0;
    }

}


Gauss gaussSeidel(double x0, double y0, double a, double b, double acc, int n)
{

    Gauss returned;
    Value v = Value();

    returned.x = x0;
    returned.y = y0;

    int i = 1;
    while (true)
    {
        double initial_value = function(returned.x, returned.y);
        double golden_x = returned.x + golden_for_g(a, b, acc, v.gr, returned.x, returned.y, true);
        returned.x = golden_x;

        double golden_y = (returned.y + golden_for_g(a, b, acc, v.gr, returned.y, returned.x, false));
        returned.y = golden_y;

       
        double delta = initial_value - function(golden_x, golden_y);
        if ((delta <= acc) || (i < n)) {

            break;
        }

        i++;
    }


    return returned;

}

Stepest steepestDescent(double x0, double y0, double a, double b, double acc, int n)
{
    Stepest returned;
    Value v = Value();

    returned.x = x0;
    returned.y = y0;

    double alpha = 1;

    double value;

    int i = 0;
    while (true)
    {

        Gradient grad = gradient_of(returned.x, returned.y);

        alpha = golden_for_step(a, b, acc, v.gr, returned.x, returned.y);

        returned.x = returned.x + alpha * grad.dx;
        returned.y = returned.y + alpha * grad.dy;
        value = sqrt(pow(alpha * (grad.dx), 2) + pow(alpha * (grad.dy), 2));
        if (value < acc || i >= n) {
            break;

        }

        i++;
    }


    return returned;

}

double golden_for_step(double a, double b, double acc, double gr, double x, double y)
{
    int n = 0;
    double x1 = b - gr * (b - a);
    double x2 = a + gr * (b - a);

    Gradient grad = gradient_of(x, y);

    /*double fx1 = function(x + x1 * grad.dx, y + x1 * grad.dy);
    double fx2 = function(x + x2 * grad.dx, y + x2 * grad.dy);*/

    while (!(b - a < acc))
    {
        double fx1 = function(x + x1 * grad.dx, y + x1 * grad.dy);
        double fx2 = function(x + x2 * grad.dx, y + x2 * grad.dy);
        if (fx1 >= fx2) {

            b = x1;
            x2 = x1;
            x2 = a + gr * (b - a);
        }
        else{

            a = x2;
            x1= x2;
            x1 = b - gr * (b - a);
        }

        n++;
    }
    return (x2 + x1) / 2.0;

}