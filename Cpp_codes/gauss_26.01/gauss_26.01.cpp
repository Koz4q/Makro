#include <iostream>
#include <math.h>
using namespace std;


float ReturnAddedAlpha(float x, float y, float a, float b)
{
    float Result;
    if (b != 1)//adding alpha to x
    {
        y = y + a;
    }
    else//adding alpha to y
    {
        x = x + a;
    }
    Result = ((2 - (pow(y, 2)) * pow(2.718, -sin(2 * x - 1)))); //OurFunction where alpha is already added (2-(y^2))*pow(2.718,-sin(2*x-1))
    return Result;
}


float GoldenSection(float x, float y, float c)
{

    float X1;
    float X2;
    float ValueX1;
    float ValueX2;
    float A;
    float B;
    float Epsilon;
    float alpha;



    A = -1;//start of the interval

    B = 1; //end of the interval
    Epsilon = 0.0001;//accuracy

    alpha = (sqrt(5) - 1) / 2;//golden ratio

     //calculating the x1 x2 values//
    X1 = A + (1 - alpha) * (B - A);
    X2 = A + alpha * (B - A);

    //calculating the f values for x1 x2//
    ValueX1 = ReturnAddedAlpha(x, y, X1, c);
    ValueX2 = ReturnAddedAlpha(x, y, X2, c);


    while ((B - A) > Epsilon)//stop condition
    {
        //golden section algorithm//
        if (ValueX1 < ValueX2)
        {
            B = X2;
            X2 = X1;
            X1 = A + (1 - alpha) * (B - A);//calculating new x1 value
            ValueX1 = ReturnAddedAlpha(x, y, X1, c);
            ValueX2 = ReturnAddedAlpha(x, y, X2, c);
        }
        else
        {
            A = X1;
            X1 = X2;
            X2 = A + alpha * (B - A);//calculating new x2 value
            ValueX1 = ReturnAddedAlpha(x, y, X1, c);
            ValueX2 = ReturnAddedAlpha(x, y, X2, c);
        }
        //end of golden section method//
    }
    //selecting the alpha of the minimum out of the values we got//
    if (ValueX1 < ValueX2)
    {
        return X1;
    }
    else
    {
        return X2;
    }
}
int main()
{
    float ThisIterationResult;
    float PreviousIterationResult;
    float x0 = 0;
    float y0 = 0;
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;
    float Eps = 0.0001f; //Accuracy of our Programm
    float a = 0;
    int iteration = 0;

    //Random Starting Variable
    x2 = 0.7; // starting point ------------------------------------------------------------
    y2 = 0.2;
    cout << "Iteration = " << iteration << " Step 1 " << endl << "x = " << x2 << endl << "y = " << y2 << endl;
    do
    {
        // previous iteration
        x0 = x2;
        y0 = y2;

        iteration++;
        a = GoldenSection(x0, y0, 1);//finding min of alpha

        x1 = x0 + a;//adding alpha to x
        y1 = y0;

        //checking to not pass our constraints
        if (x1 < -1) { x1 = -1; }//contrains ---------------------------------------------------------------

        else if (x1 > 1)//-----------------------
        {
            x1 = 1;
        }

        cout << "Step 2" << endl << "x = " << x1 << endl << "y = " << y1 << endl << endl;//show

        //iteration e=[0 1]
        iteration++;

        a = GoldenSection(x1, y1, 0);//finding min of alpha

        x2 = x1;

        y2 = y1 + a;//adding alpha to y

        //checking to not pass our constraints
        if (y2 < -1) { y2 = -1; }//-----------------------------------------------------------------------
        else if (y2 > 1) { y2 = 1; }//------------------------

        cout << "Iteration = " << iteration / 2 << " Step 1" << endl << "x = " << x2 << endl << "y = " << y2 << endl;//show

        PreviousIterationResult = (((2 - (pow(y0, 2)) * pow(2.718, -sin(2 * x0 - 1)))));//--------------  y = y0   x = x0
        ThisIterationResult = ((2 - (pow(y2, 2)) * pow(2.718, -sin(2 * x2 - 1))));//-------------------    y = y2   x = x2

    } while (abs(PreviousIterationResult - ThisIterationResult) > Eps);//stop condition for our function

    //show

    cout << endl << endl << "Minimum found for x =" << x2 << endl;

    cout << "Minimum found for y =" << y2 << endl;

    return 0;
}