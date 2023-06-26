#include <iostream>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>

using namespace std;



char strcpy() {

    cout << " Please enter two strings. " << endl;
    char s1[25];
    char s2[25];
    char sum[50];

    cin >> s1 >> s2;


    for (int i = 0;i < 25;i++) {

        sum[i] = s1[i];

    }

    for (int i = 0;i < 25;i++) {

        sum[i+25] = s1[i];

    }
    return sum[50];
}
int main()
{

    cout << "Added string : " << strcpy() << endl;

    return 0;


}
