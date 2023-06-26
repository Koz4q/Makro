#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

class Equilibrium
{
public:
	int value_for_player_a;
	int	value_for_player_b;
	int	row;
	int	col;
	bool feasibility;

	Equilibrium(int value_for_player_a, int value_for_player_b, int row, int col)
	{
		this->value_for_player_a = value_for_player_a;
		this->value_for_player_b = value_for_player_b;
		this->row = row;
		this->col = col;
		this->feasibility = true;
	}
};

int maximum(int a, int b, int c) {
	return max({ a, b, c });
	
}

bool is_max_col(int col, int row, int matrix[3][3]) {
	int val = matrix[row][col];
	int val_max = maximum(matrix[0][col], matrix[1][col], matrix[2][col]);
	return val == val_max;
}

bool is_max_row(int col, int row, int matrix[3][3]) {
	int val = matrix[row][col];
	int val_max = maximum(matrix[row][0], matrix[row][1], matrix[row][2]);
	return val == val_max;

}

void draw_matrix(int arr[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void nash_eq(int matrix_a[3][3],int matrix_b[3][3]) {
	list<Equilibrium> equ_list;
	for (int row = 0;row < 3;row++) {
		for (int col = 0;col < 3;col++) {
			if (is_max_col(col, row, matrix_a)) {
				if (is_max_row(col, row, matrix_b)) {
					cout << "Nash equilibrium (at point): " << "(" << row+1 << "," << col+1 << ")" << endl;
					Equilibrium equ = Equilibrium(matrix_a[row][col],matrix_b[row][col],row,col);
					equ_list.push_back(equ);
					
				}
			}
		}
	}

	for (auto equilibirium = equ_list.begin(); equilibirium != equ_list.end(); equilibirium++) {
		for (auto check = equ_list.begin(); check != equ_list.end(); check++) {
			if (equilibirium != check && (*equilibirium).value_for_player_a <= (*check).value_for_player_a &&
				(*equilibirium).value_for_player_b <= (*check).value_for_player_b) {
				(*equilibirium).feasibility = false;
			}
		}
	}
	cout << endl;
	
	for (auto equilibirium = equ_list.begin(); equilibirium != equ_list.end(); equilibirium++) {
		if ((*equilibirium).feasibility) {
			cout << "Feasible solutions: " << "(" << (*equilibirium).row+1 << "," << (*equilibirium).col+1 << ")" << endl;
		}
	}
		

}

int main()
{
	int matrix_a[3][3] = { {1,1,1},{1,1,1},{1,1,1} };
	int matrix_b[3][3] = { {1,1,1} ,{1,1,1},{1,1,1} };
	cout << "A matrix:" << endl;
	draw_matrix(matrix_a);
	cout << "B matrix:" << endl;
	draw_matrix(matrix_b);
	nash_eq(matrix_a, matrix_b);


	return 0;

}