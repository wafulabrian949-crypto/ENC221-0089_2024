#include <iostream>

struct Fraction {
    int numerator;
    int denominator;
    
    // Constructor with default values
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) denominator = 1; // Prevent division by zero
    }
};

// Compare two fractions WITHOUT floating-point errors
bool isGreater(const Fraction& a, const Fraction& b) {
    return (a.numerator * b.denominator) > (b.numerator * a.denominator);
}

// Function that finds largest of three fractions
// Uses pass-by-reference for parameters
// Uses return-by-reference for result
Fraction& largestFraction(Fraction& f1, Fraction& f2, Fraction& f3) {
    // Compare using integer arithmetic only (no floating-point)
    if (!isGreater(f2, f1) && !isGreater(f3, f1)) {
        return f1;  // Return reference to f1
    } 
    else if (!isGreater(f1, f2) && !isGreater(f3, f2)) {
        return f2;  // Return reference to f2
    } 
    else {
        return f3;  // Return reference to f3
    }
}

int main() {
    // Create three fraction objects
    Fraction fraction1(1, 2);   // 1/2
    Fraction fraction2(3, 4);   // 3/4
    Fraction fraction3(2, 5);   // 2/5
    
    // Call function - returns reference to largest fraction
    Fraction& largest = largestFraction(fraction1, fraction2, fraction3);
    
    // Display result
    std::cout << "Largest fraction: " 
              << largest.numerator << "/" 
              << largest.denominator << std::endl;
    
    return 0;
}