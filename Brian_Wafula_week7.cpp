#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    int age;
    int serviceYear;
    double salary;

public:
    // Parameterized constructor
    Employee(string empName, int empAge, int empServiceYear, double empSalary)
        : name(empName), age(empAge), serviceYear(empServiceYear), salary(empSalary) {
        cout << "Employee object created: " << name << endl;
    }
    
    // Destructor
    ~Employee() {
        cout << "Employee object destroyed: " << name << endl;
    }
    
    // Accessor functions (getters)
    string getName() const {
        return name;
    }
    
    int getAge() const {
        return age;
    }
    
    int getServiceYear() const {
        return serviceYear;
    }
    
    double getSalary() const {
        return salary;
    }
};

int main() {
    // Create Employee objects
    Employee emp1("John Smith", 35, 8, 55000.50);
    Employee emp2("Sarah Johnson", 28, 3, 42000.75);
    
    // Access data using getter functions
    cout << "Employee 1 Details:" << endl;
    cout << "Name: " << emp1.getName() << endl;
    cout << "Age: " << emp1.getAge() << endl;
    cout << "Service Years: " << emp1.getServiceYear() << endl;
    cout << "Salary: $" << emp1.getSalary() << endl;
    
    cout << "\nEmployee 2 Details:" << endl;
    cout << "Name: " << emp2.getName() << endl;
    cout << "Age: " << emp2.getAge() << endl;
    cout << "Service Years: " << emp2.getServiceYear() << endl;
    cout << "Salary: $" << emp2.getSalary() << endl;
    
    return 0;
}