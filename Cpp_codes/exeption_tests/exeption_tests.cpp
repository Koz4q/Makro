#include <iostream>
#include <exception>
using namespace std;

class MyException : public exception {

};

class MyClass {
public:
	double exception(double parameter1, double parameter2) {
		if (parameter2 == 0) {
			throw new MyException;
		}

		return (parameter1 / parameter2);
	}
};
int main() {
	MyClass object;
	try {
		object.exception(5, 0);
	}
	catch (MyException* me) {
		cout << "MyException caught." << endl;


	}
}