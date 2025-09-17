#include <iostream>
#include <memory> // for unique_ptr
using namespace std;

class Fraction
{
private:
	int m_numerator{ 0 };
	int m_denominator{ 1 };

public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator }, m_denominator{ denominator }
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{
		out << f1.m_numerator << '/' << f1.m_denominator;
		return out;
	}
};

void printFraction(std::unique_ptr<Fraction>& ptr)
{
	if (ptr)
		std::cout << *ptr << '\n';
	else
		std::cout << "No fraction\n";
}

int main()
{
	// auto* ptr{ new Fraction{ 3, 5 } };
    std::unique_ptr<Fraction> ptr = std::make_unique<Fraction>(3, 5); 

	printFraction(ptr);

	return 0;
}