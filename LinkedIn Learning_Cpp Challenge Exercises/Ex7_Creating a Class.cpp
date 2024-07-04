// Ex7: Complex Number Calculator using C++ Class
// Create a class to perform complex number calculations
// Overload operators for addition, subtraction, multiplication and division
// Write a function to print a complex number


#include"ExHeader.h"
#include"CommonHeader.h"

class Complex {
	
public: // Declare member variables
	float Re;
	float Im;

public: // Constructor
	Complex(float RealComponent = 0, float ImaginaryComponent = 0) {
		Re = RealComponent;
		Im = ImaginaryComponent;
	}

public: // Operator overloading
	Complex operator+ (const Complex& other) {
		Complex sum;
		sum.Re = Re + other.Re;
		sum.Im = Im + other.Im;

		return sum;
	}

	Complex operator- (const Complex& other) {
		Complex substract;
		substract.Re = Re - other.Re;
		substract.Im = Im - other.Im;

		return substract;
	}

	Complex operator* (const Complex& other) {
		Complex product;
		product.Re = Re * other.Re - Im * other.Im;
		product.Im = Re * other.Im + Im * other.Re;

		return product;
	}

	Complex operator/ (const Complex& other) {
		Complex division;
		float denominator = other.Re * other.Re + other.Im * other.Im;
		division.Re = (Re * other.Re + Im * other.Im) / denominator;
		division.Im = (Im * other.Re - Re * other.Im) / denominator;

		return division;
	}

public: // Member function
	void Print() {
		if (Im < 0) {
			std::cout << Re << " " << Im << "i" << std::endl;
			return;
		}
		std::cout << Re << " + " << Im << "i" << std::endl;
	}

};



void ComplexNumbers() {

	Complex A(10.0, 5.0), B(-2.0);

	std::cout << "Value of A: ";
	A.Print();
	std::cout << "Value of B: ";
	B.Print();

	std::cout << "A + B = ";
	(A + B).Print();
	std::cout << "A - B = ";
	(A - B).Print();
	std::cout << "A * B = ";
	(A * B).Print();
	std::cout << "A / B = ";
	(A / B).Print();

}