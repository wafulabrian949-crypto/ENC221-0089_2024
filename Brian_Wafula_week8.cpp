#include <iostream>
using namespace std;

class Square {
protected:
    double side;
    
public:
    // Constructor
    Square(double s = 1.0) : side(s) {
        cout << "Square created with side: " << side << endl;
    }
    
    // Destructor
    ~Square() {
        cout << "Square destroyed" << endl;
    }
    
    // Accessor for side
    double getSide() const {
        return side;
    }
    
    // Method to calculate area
    double getArea() const {
        return side * side;
    }
    
    // Method to calculate perimeter
    double getPerimeter() const {
        return 4 * side;
    }
};

class Cube : public Square {
public:
    // Constructor calls base class constructor
    Cube(double s = 1.0) : Square(s) {
        cout << "Cube created" << endl;
    }
    
    // Destructor
    ~Cube() {
        cout << "Cube destroyed" << endl;
    }
    
    // Override getArea() for surface area
    double getArea() const {
        return 6 * (side * side);  // Surface area of cube
    }
    
    // New method for cube volume
    double getVolume() const {
        return side * side * side;
    }
};

int main() {
    // Test Square
    Square square1(5.0);
    cout << "Square area: " << square1.getArea() << endl;
    cout << "Square perimeter: " << square1.getPerimeter() << endl;
    
    // Test Cube
    Cube cube1(4.0);
    cout << "\nCube side: " << cube1.getSide() << endl;
    cout << "Cube surface area: " << cube1.getArea() << endl;
    cout << "Cube volume: " << cube1.getVolume() << endl;
    cout << "Cube base perimeter: " << cube1.getPerimeter() << endl;
    
    return 0;
}