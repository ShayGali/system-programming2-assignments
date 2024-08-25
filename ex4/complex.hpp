// @author shay.gali@msmail.ariel.ac.il
#include <iostream>
#include <string>

using std::ostream;
using std::string;

/**
 * Represents a complex number.
 */
class Complex {
   private:
    double real;
    double imag;

   public:
    Complex(double real, double imag);

    double getReal();

    double getImag();

    /**
     * Checks if two complex numbers are equal.
     * Two complex numbers are equal if their real and imaginary parts are equal.
     * @param other The other complex number to compare with.
     */
    bool operator==(const Complex &other) const;

    /**
     * Returns a string representation of the complex number. (e.g. "1 + 2i", "3 - 4i", "5i", "6")
     */
    string to_str() const;

    /**
     * Compares two complex numbers. Although we dont define a total order for complex numbers, we define this an order based on the norm of the complex number.
     */
    bool operator<(const Complex &other);

    /**
     * Overloads the << operator to print the complex number.
     */
    friend ostream &operator<<(ostream &os, const Complex &complex);
};

/**
 * Converts a complex number to a string. (overload the std::to_string function for Complex class)
 */
string to_string(const Complex &complex);