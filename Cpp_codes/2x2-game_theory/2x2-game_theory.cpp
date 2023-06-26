#include <iostream>

using namespace std;

double max_returned, min_returned;
double value_of_the_game;
double money = 100000;

void draw_matrix(double matrix[2][2]) {
    cout << "2 x 2 zero sum game." << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << matrix[i][j] << " ";
            
        }
        cout << endl;
    }
    cout << endl;
}
void psafe_strategy(double matrix[2][2]) {
    double max_first, max_second, min_first, min_second;
    // checks the safe strategy for player 2
    if (matrix[0][0] < matrix[1][0]) {
        max_first = matrix[0][0];
    }
    else {
        max_first = matrix[1][0];
    }     
    if (matrix[0][1] < matrix[1][1]) {
        max_second = matrix[0][1];
    }
    else {
        max_second = matrix[1][1];
    }
    
    // checks the safe strategy for player 1
    if (matrix[0][0] > matrix[0][1]) {
        min_first = matrix[0][0];
    }
    else {
        min_first = matrix[0][1];
    }
    if (matrix[1][0] > matrix[1][1]) {
        min_second = matrix[1][0];
    }
    else {
        min_second = matrix[1][1];
    }
    
    // compare max values and choose lower one
    if (max_first > max_second) {
        max_returned = max_first;
    }
    else {
        max_returned = max_second;
    }

    // compare min values and choose larger one
    if (min_first > min_second) {
        min_returned = min_second;
    }
    else {
        min_returned = min_first;
    }
   
}

void mixed_strategy(double matrix[2][2]) {
    
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    double p1 = (d - c) / ((a + d) - (b + c));
    double p2 = 1 - p1;
    double q1 = (d - b) / ((a + d) - (b + c));
    double q2 = 1 - q1;

    value_of_the_game = ((a * d) - (b * c)) / ((a + d) - (b + c));
    cout << "Profit :" << (value_of_the_game / 100) * money <<"$" << endl;
    cout << "Player 2 should invest " << p1 * money << "$ in option 1 and " << p2 * money << "$ in option 2." << endl;
}


int main()
{
    
    double matrix[2][2] = { {-5,25},{0,20} };
    draw_matrix(matrix);
    psafe_strategy(matrix);
    if (min_returned == max_returned) {
        cout << "Saddle point exist at value : " << min_returned << endl;
    }
    else {
        cout << "Safe strategy for player 1 : " << min_returned << endl;
        cout << "Safe strategy for player 2 : " << max_returned << endl << endl;
        mixed_strategy(matrix);
        
    }
    
}
