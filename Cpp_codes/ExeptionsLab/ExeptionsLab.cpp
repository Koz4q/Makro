#include <iostream>
#include <exception>

using namespace std;

class DivisionExeption : public exception {
public:
	 
};

class AreaExeption : public exception {
public:

};

class Person {
public:
	int age = 0;
	
};

class Mother : public Person {
public:

};

class Father : public Person {
public:

};

class Son : public Person {
public:

	Son(Mother m, Father f, int age) {
		if (m.age < age || f.age < age) {
			throw age;
		}
		
	}

};

class Bar {
public:
	int party(Person p) {
		if (p.age < 18) {
			throw p.age;
		};
	}
};

class Math {
public:
	
	double division(double a, double b) {
		if (b == 0) {
			throw new DivisionExeption;
		}

		cout<< "Division is equal to: " << (a / b) << endl;
	}

	float area_of_square(float a, float b) {
		if (a <= 0 || b <= 0) {
			throw new AreaExeption;
		}

		cout << "Area of square is equal to: " << (a * b) << endl;
	}
};



int main()
{
	Math m1;
	Father fa1;
	Mother mo1;
	Bar b1;
	cout << "Please enter the age of the parents: \nAge of the father: " ;
	cin >> fa1.age;
	cout << "Age of the mother: " ;
	cin >> mo1.age;
	
	try {
		Son s1(mo1, fa1, 10);
	}
	catch (int age) {
		cout << "Son cant be older than parents." << endl << endl;

	}

	Person p1;
	cout << "Please enter the age of person: ";
	cin >> p1.age;
		
	try {
		b1.party(p1);
	}
	catch(int age){
		cout << "You are not of legal age. Please come back in: " << (18 - age) << " years." << endl << endl;
		}
	



	try {
		m1.division(10, 0);
	}
		catch (DivisionExeption* d) {
			cout << "MyException caught." << endl;
			
		}
	

	try {
			m1.area_of_square(10, -1);
			
	}
		catch (AreaExeption* a) {
			cout << "MyException caught." << endl;

		}
		
		


	return 0;

}