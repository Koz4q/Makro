#include <iostream>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;


void mySwap(int &a, int &b) {
   
    int tmp;
    tmp = a;
    a = b;
    b = tmp;

}


int main()
{
   /*
    char orig[] ="Please bring me some tea and coffe";
    
    cout << orig << endl;
    
    for (int i = 0;i < 100;i++) {

        while (orig[i] == 'a' && orig[i + 1] == 'n' && orig[i + 2] == 'd') {


            orig[i] = 'o';
            orig[i + 1] = 'r';
            orig[i + 2] = ' ';

        }

    }
    
    cout << orig << endl;
    */

    int n ;
    cout << "How many elements do you need: " ;
    cin >> n;
    cout << "OK, creating an array for " << n << " elements." << endl;
    int* t;
    t = new int[n];
    
    for (int i = 0;i < n;i++) {

        cout << " t[" << i << "]: ";
        cin >> t[i];
    }
    
    for (int i = 0; i < n;i++) {

        cout << t[i] << " ";

    }
    cout << endl;

    for (int i = 0, j = n - 1;i < j;i++, j--) {
        mySwap(t[i], t[j]);
    }
    
    for (int i = 0; i < n;i++) {

        cout << t[i] << " ";

    }
    cout << endl;

    return 0;
}

