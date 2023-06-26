#include<iostream>
#include<math.h>



using namespace std;


int choice(int number, int f[7][2])            //Algorytm wyszukujący odpowiednią liczbe  z f(i)
{
	int column = 0;
	while (column <= 6)
	{
		if (f[column][1] == number)
		{
			return(f[column][0]);
		}
		column++;
	}
}

int max(int tab[28][6], int number)               //Algorytm wyszukujący najwyższy wzrost.
{
	int row = 0;
	int greatest = 0;
	while (row <= 27)
	{
		if (tab[row][2] == number)
		{
			if (tab[row][5] >= greatest)
			{
				greatest = tab[row][5];
			}
		}
		row++;
	}
	return(greatest);
}
int main()
{
	int tab3[7][3];
	int tab2[28][6];
	int tab1[28][6];
	int tab0[7][6];

	// *********** DANE POCZĄTKOWE ***********

	int f1[7][2] = {
		{ 0, 0 },
		{ 17, 50 },
		{ 38, 100 },
		{ 50, 150 },
		{ 55, 200 },
		{ 60, 250 },
		{ 0, 300 },
	};
	int f2[7][2] = {
		{ 0, 0 },
		{ 25, 50 },
		{ 40, 100 },
		{ 48, 150 },
		{ 56, 200 },
		{ 62, 250 },
		{ 0, 300 },
	};
	int f3[7][2] = {
		{ 0, 0 },
		{ 20, 50 },
		{ 35, 100 },
		{ 52, 150 },
		{ 60, 200 },
		{ 68, 250 },
		{ 0, 300 },
	};
	int f4[7][2] = {
		{ 0, 0 },
		{ 30, 50 },
		{ 45, 100 },
		{ 50, 150 },
		{ 55, 200 },
		{ 68, 250 },
		{ 0, 300 },
	};

	// *****************TWORZENIE TABELI 1 ****************

	int row = 0;
	int column = 0;
	while (row <= 6)
	{
		tab3[row][column + 1] = f4[row][1];
		tab3[row][column] = 300 - tab3[row][column + 1];
		tab3[row][column + 2] = choice(tab3[row][column], f4);   //choice wybiera odpowiednią liczbe  z tablicy f(i)
		row++;
	}

	// **************DRUKOWANIE TABELI 1 ******************

	cout << "  TABLE 1\n" << endl;
	cout << "U3   X3   S3\n" << endl;

	row = 0;
	while (row <= 6)
	{
		cout << tab3[row][column] << "  ";
		if (tab3[row][column] < 10)                            //if po to by się dobrze drukowało 
			cout << " ";
		if (tab3[row][column] < 100)
			cout << " ";

		cout << tab3[row][column + 1] << "  ";
		if (tab3[row][column + 1] < 10)
			cout << " ";
		if (tab3[row][column + 1] < 100)
			cout << " ";

		cout << tab3[row][column + 2];
		cout << endl;
		row++;
	}
	if (tab3[row - 1][1] == 300)
	{
		cout << "------------" << endl;
	}

	//  ****** TWORZENIE TABELI 2 **************

	row = 0;
	int rowf = 0;
	int rowu = 0;
	column = 2;
	int count = 0;

	while (row <= 27)
	{
		tab2[row][column] = f3[rowf][1];
		tab2[row][column - 1] = f3[rowu][1];
		tab2[row][column - 2] = tab2[row][column - 1] - tab2[row][column];
		tab2[row][column + 1] = tab3[rowu][2];
		tab2[row][column + 2] = choice(tab2[row][column - 2], f3);                     //szuka odpowiedniej liczby w f
		tab2[row][column + 3] = tab2[row][column + 2] + tab2[row][column + 1];         //wzrost dla tego kroku 

		row++;
		rowu++;
		if (tab2[row - 1][1] == 300)
		{
			count++;
			rowu = count;
			rowf++;
		}
	}

	//********** DRUKOWANIE TABELI 2  ********

	cout << "\n  TABLE 2\n" << endl;
	cout << "U2   X3   X2   S3   f3   S2\n" << endl;
	row = 0;
	while (row <= 27)
	{
		cout << tab2[row][column - 2] << "  ";
		if (tab2[row][column - 2] < 10)
			cout << " ";
		if (tab2[row][column - 2] < 100)
			cout << " ";

		cout << tab2[row][column - 1] << "  ";
		if (tab2[row][column - 1] < 10)
			cout << " ";
		if (tab2[row][column - 1] < 100)
			cout << " ";

		cout << tab2[row][column] << "  ";
		if (tab2[row][column] < 10)
			cout << " ";
		if (tab2[row][column] < 100)
			cout << " ";

		cout << tab2[row][column + 1] << "  ";
		if (tab2[row][column + 1] < 10)
			cout << " ";
		if (tab2[row][column + 1] < 100)
			cout << " ";

		cout << tab2[row][column + 2] << "  ";
		if (tab2[row][column + 2] < 10)
			cout << " ";
		if (tab2[row][column + 2] < 100)
			cout << " ";

		cout << tab2[row][column + 3] << endl;
		row++;

		if (tab2[row - 1][1] == 300)
		{
			cout << "----------------------------" << endl;
		}

	}


	//************** TWORZENIE TABELI 3 ****************

	row = 0;
	rowf = 0;
	rowu = 0;
	column = 2;
	count = 0;

	while (row <= 27)
	{
		tab1[row][column] = f2[rowf][1];
		tab1[row][column - 1] = f2[rowu][1];
		tab1[row][column - 2] = tab1[row][column - 1] - tab1[row][column];
		tab1[row][column + 1] = max(tab2, tab1[row][column - 1]);                      //algoryst wyszukujący najwyzszy wzrost dla poprzedniego (przyszłego) kroku
		tab1[row][column + 2] = choice(tab1[row][column - 2], f2);                     //szuka odpowiedniej liczby w f
		tab1[row][column + 3] = tab1[row][column + 2] + tab1[row][column + 1];         //wzrost dla tego kroku 

		row++;
		rowu++;
		if (tab1[row - 1][1] == 300)
		{
			count++;
			rowu = count;
			rowf++;
		}
	}

	//********** DRUKOWANIE TABELI 3  ********

	cout << "\n  TABLE 3\n" << endl;
	cout << "U1   X2   X1   S2   f2   S1\n" << endl;
	row = 0;
	while (row <= 27)
	{
		cout << tab1[row][column - 2] << "  ";
		if (tab1[row][column - 2] < 10)
			cout << " ";
		if (tab1[row][column - 2] < 100)
			cout << " ";

		cout << tab1[row][column - 1] << "  ";
		if (tab1[row][column - 1] < 10)
			cout << " ";
		if (tab1[row][column - 1] < 100)
			cout << " ";

		cout << tab1[row][column] << "  ";
		if (tab1[row][column] < 10)
			cout << " ";
		if (tab1[row][column] < 100)
			cout << " ";

		cout << tab1[row][column + 1] << "  ";
		if (tab1[row][column + 1] < 10)
			cout << " ";
		if (tab1[row][column + 1] < 100)
			cout << " ";

		cout << tab1[row][column + 2] << "  ";
		if (tab1[row][column + 2] < 10)
			cout << " ";
		if (tab1[row][column + 2] < 100)
			cout << " ";

		cout << tab1[row][column + 3] << endl;
		row++;

		if (tab1[row - 1][1] == 300)
		{
			cout << "----------------------------" << endl;
		}
	}

	// ***********TWORZENIE TABELI 4 ************

	row = 0;
	rowf = 0;
	rowu = 0;
	column = 2;
	count = 0;

	while (row <= 6)
	{
		tab0[row][column] = f1[rowf][1];
		tab0[row][column - 1] = f1[rowu][1];
		tab0[row][column - 2] = tab0[row][column - 1] - tab0[row][column];
		tab0[row][column + 1] = max(tab1, tab0[row][column - 1]);                      //algoryst wyszukujący najwyzszy wzrost dla poprzedniego (przyszłego) kroku
		tab0[row][column + 2] = choice(tab0[row][column - 2], f1);                     //szuka odpowiedniej liczby w f
		tab0[row][column + 3] = tab0[row][column + 2] + tab0[row][column + 1];         //wzrost dla tego kroku 

		row++;
		rowu++;
		if (tab0[row - 1][1] == 300)
		{
			count++;
			rowu = count;
			rowf++;
		}
	}

	//********** DRUKOWANIE TABELI 4  ********

	cout << "\n  TABLE 4\n" << endl;
	cout << "U0   X1   X0   S1   f1   S0\n" << endl;
	row = 0;
	while (row <= 6)
	{
		cout << tab0[row][column - 2] << "  ";
		if (tab0[row][column - 2] < 10)                            //if po to by się dobrze drukowało 
			cout << " ";
		if (tab0[row][column - 2] < 100)
			cout << " ";

		cout << tab0[row][column - 1] << "  ";
		if (tab0[row][column - 1] < 10)
			cout << " ";
		if (tab0[row][column - 1] < 100)
			cout << " ";

		cout << tab0[row][column] << "  ";
		if (tab0[row][column] < 10)
			cout << " ";
		if (tab0[row][column] < 100)
			cout << " ";

		cout << tab0[row][column + 1] << "  ";
		if (tab0[row][column + 1] < 10)
			cout << " ";
		if (tab0[row][column + 1] < 100)
			cout << " ";

		cout << tab0[row][column + 2] << "  ";
		if (tab0[row][column + 2] < 10)
			cout << " ";
		if (tab0[row][column + 2] < 100)
			cout << " ";

		cout << tab0[row][column + 3] << endl;
		row++;

		if (tab0[row - 1][1] == 300)
		{
			cout << "----------------------------\n\n" << endl;
		}
	}

	// ************** SZUKANIE ROZWIĄZAŃ **********************

	int u0, row0, u1, row1, u2, row2, u3, row3;
	row0 = 0;
	row1 = 0;
	row2 = 0;
	row3 = 0;

	while (row0 <= 6)
	{
		if (tab0[row0][5] == max(tab0, 0))
		{
			u0 = tab0[row0][0];
			while (row1 <= 27)
			{
				if (tab1[row1][2] == tab0[row0][1])
				{
					if (tab1[row1][5] == max(tab1, tab1[row1][2]))
					{
						u1 = tab1[row1][0];
						while (row2 <= 27)
						{
							if (tab2[row2][2] == tab1[row1][1])
							{
								if (tab2[row2][5] == max(tab2, tab2[row2][2]))
								{
									u2 = tab2[row2][0];
									while (row3 <= 6)
									{
										if (tab3[row3][1] == tab2[row2][1])
										{
											u3 = tab3[row3][0];
											cout << "SOLUTION :   U0 = " << u0 << " , U1 = " << u1 << " , U2 = " << u2 << " , U3 = " << u3 << endl << endl;
										}
										row3++;
									}
								}
							}
							row3 = 0;
							row2++;
						}

					}
				}
				row2 = 0;
				row1++;
			}
		}
		row1 = 0;
		row0++;
	}

	getchar();
	return(0);
}