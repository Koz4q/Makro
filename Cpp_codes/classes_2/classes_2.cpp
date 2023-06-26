#include <iostream>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

int countletters(char t[], char letter){
    int count;
    count = 0;
    
    for (int i = 0;i < 100;i++) {

        if (t[i] == letter) {

            count++;

        };
    }
        return count;

}


int mystrlen(char t[])
{
    int i = 0;
    while (t[i] != 0) i++;
    return i;
}



void sum(char* n1, char* n2, char* result)
{
    int d1, d2, carry = 0, resdigit, len, i;
    len = mystrlen(n1);
    result[len] = 0;
    i = len - 1;
    while (i >= 0)
    {
        d1 = n1[i] - '0';
        d2 = n2[i] - '0';
        resdigit = d1 + d2 + carry;
        if (resdigit > 9)
        {
            resdigit -= 10;
            carry = 1;
        }
        else
            carry = 0;
        result[i] = resdigit + '0';

        i--;
    }
}

struct person {

    string name;
    int year;


};

int main(){

      /*  char t[] = "Hello, world!";

        printf("Number of occurences = %d \n", countletters(t, 'o'));

        return 0;
        */

    /*char number1[] = "03234";
    char number2[] = "08765";
    char res[10];
    sum(number1, number2, res);
    printf("Result = %s", res);*/

    person Team[5];

    
  

    return 0;
}

