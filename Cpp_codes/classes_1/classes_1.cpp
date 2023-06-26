#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;
int main()
{
  
    long float c;
    long float y;
    cout << " The starting number: " ;
    cin >> c;

    cout << " The number we want to get: " ;
    cin >> y;
    
    while (c * c > y) {
        cout << " Incorrect values, please enter the correct values. " << endl;
        return 0;
   }
    while(c*c < y) {
        c = c + 0.0001;
       
        }
    if(true){
        cout << " Number " << c << " to the power of 2 = "<< y << endl;
    }
    
   

    return 0;



    /*long long int n, i, m = 0, flag = 0;
   cout << "Enter the Number : ";
   cin >> n;

   m = n / 2;

   for (i = 2; i <= m; i++)
   {
       if (n % i == 0 || n == 1)
       {
           cout << "Number is not Prime." << endl;
           flag = 1;
           break;
       }
   }
   if (flag == 0)
       cout << "Number is Prime." << endl;
  return 0;*/


  /* float x = 1000;

   float y;
       for(int i = 0;i < 8; i++){
           y = ((x + (1000 / x)) / 2);
           x = y;
           cout << "sqrt  = " << x << endl;


       };
   cout << "final sqrt  = " << x << endl;


   return 0; */
}