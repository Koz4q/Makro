#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;


void golden(int iteration1, double y1_x1, double y1_x2, double a, double x2, double b, double x1, double d, double gr);
void fibonacci(int iteration1, double y1_x1, double y1_x2, double a, double x2, double b, double x1);
double ret_function(double x);
int find_value_of_k(double t2);
double derr_value(double x);
void gradient(double t1, int k);
double* fib_seq(int size);


class Gradient {
public:
    double k;
    double x;
    double t1;
    double t2;
    
    Gradient(double input) {
        
        x = input;
        k = 1;
        
        t2 = 0.5;
        t1 = t2 * k;

    }

    double get_y() {
        return ((x * x * x) - (x * x) + 4 * x) / (2 * (x * x * x) + 5 * (x*x) - 2 * x + 1);
    }

    double get_y_derrivative() {
        return ((7*(x*x*x*x)-20*(x*x*x)-15*(x*x)-2*x+4)/((2*(x*x*x+5*(x*x)-2*x+1)* (2 * (x * x * x + 5 * (x * x) - 2 * x + 1)))));
    }
};


class Golden {
public:

    double a = -1;
    double b = 1;

    double gr = (sqrt(5) - 1) / 2;
    double d = gr * (b - a);

    double x1 = a + d;
    double x2 = b - d;

    double y1_x1 = ret_function(x1);
    double y1_x2 = ret_function(x2);

   

    int iteration1 = 1;
    
};

class Fibonacci {
public:

    double a = -1;
    double b = 1;
    double t = 1;//tolerance
    

    double* fib;
   
    Fibonacci(int n) {

        fib = fib_seq(n);
        
    }
    ~Fibonacci() {
        delete fib;
    }

    double fn(int n) {
        return fib[n];

    }

    double get_x1(int n) {
        return a + (fib[n] - (2 / fib[n]) * (b - a));
    }

    double get_x2(int n) {
        return a + (fib[n] - (1 / fib[n]) * b);
    }

};


int main()
{

    Gradient g = Gradient(0);
    Golden v;
    

    //f(x)
    cout << "Golden section method." << endl;
    golden(v.iteration1, v.y1_x1, v.y1_x2, v.a, v.x2, v.b, v.x1, v.d, v.gr);
    cout << endl;
    cout << "Fibonacci sequance method." << endl;
    v = Golden();
    fibonacci(v.iteration1, v.y1_x1, v.y1_x2, v.a, v.x2, v.b, v.x1);
    
    cout << "Golden section w init expantion/contraction" << endl;
    gradient(g.t2,find_value_of_k(g.t2));
    
    cout << find_value_of_k(g.t2) << endl;
}



void golden(int iteration1, double y1_x1, double y1_x2, double a, double x2, double b, double x1, double d, double gr)
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

        y1_x1 = ret_function(x1);
        y1_x2 = ret_function(x2);



        //cout << d << endl;
        if (d <= 0.0000001) {
            //cout << "Function f(x)" << endl;
            cout << "Best case found at iteration: " << iteration1 << "\nat point x = " << a << endl;
            cout << "Value of the function : " << y1_x1 << endl;
            cout << endl;

            break;
        }

        iteration1++;
    }
}

double ret_function(double x)
{
    return Gradient(x).get_y();
}

double derr_value(double x)
{
    return Gradient(x).get_y_derrivative();
}

int find_value_of_k(double t2) {
    int k = 1;
    double t1 = t2 * k;
    //f(t1)<=f(0)+0.5*f'(0)*t1   &&   f(t2)>=f(0)+0.5f'(0)*t2
    
    while (!((ret_function(t1) <= ret_function(0) + 0.5 * derr_value(0) * t1) && (ret_function(t2) >= ret_function(0) + 0.5 * derr_value(0) * t2)) || k == 0)
    {
        k--;
        t1 = t2 * k;
    }

    
    return k;
}

void gradient(double t2, int k)
{
    Golden g;
    double t1 = t2 * k;
    golden(g.iteration1, g.y1_x1, g.y1_x2, t1, g.x2, t2, g.x1, g.d, g.gr);

}

double* fib_seq(int size) {
    double* returned = new double[size];
    returned[0] = 1;
    returned[1] = 1;
    for (int i = 2; i < size; i++) {
        returned[i] = returned[i - 1] + returned[i - 2];
    }

    return returned;
}


void fibonacci(int iteration1, double y1_x1, double y1_x2, double a, double x2, double b, double x1)
{
    Fibonacci* f = new Fibonacci(21);
    int end = 20;
    double d;
    while (iteration1 < end) {

        if (y1_x1 < y1_x2) {

            a = x2;
        }
        else {
            b = x1;
        }

        d = (f->fn(end - iteration1)/ f->fn(end - iteration1 + 1)) * (b - a);
        x1 = a + d;
        x2 = b - d;

        y1_x1 = ret_function(x1);
        y1_x2 = ret_function(x2);



        //cout << d << endl;
        if (d <= 0.001) {
            //cout << "Function f(x)" << endl;
            cout << "Best case found at iteration: " << iteration1 << "\nat point x = " << a << endl;
            cout << "Value of the function : " << y1_x1 << endl;
            cout << endl;

            break;
        }

        iteration1++;
    }

    delete f;
}
