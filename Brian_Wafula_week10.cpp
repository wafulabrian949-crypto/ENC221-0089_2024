#include <iostream>
#include <string>
using namespace std;

// Abstract base class (has pure virtual function)
class Employee {
protected:
    string firstName;
    char middleInitial;
    string lastName;
    
public:
    Employee(string fname, char initial, string lname)
        : firstName(fname), middleInitial(initial), lastName(lname) {}
    
    // Pure virtual function - makes class abstract
    virtual double calculatePay() const = 0;
    
    // Virtual destructor for proper cleanup
    virtual ~Employee() {}
    
    string getFullName() const {
        return firstName + " " + middleInitial + ". " + lastName;
    }
};

// Derived class: SalaryEmployee
class SalaryEmployee : public Employee {
private:
    double monthlySalary;
    
public:
    SalaryEmployee(string fname, char initial, string lname, double salary)
        : Employee(fname, initial, lname), monthlySalary(salary) {}
    
    double calculatePay() const override {
        return monthlySalary; // Fixed monthly salary
    }
};

// Derived class: HourlyEmployee
class HourlyEmployee : public Employee {
private:
    double hoursWorked;
    double hourlyRate;
    
public:
    HourlyEmployee(string fname, char initial, string lname, 
                   double hours, double rate)
        : Employee(fname, initial, lname), 
          hoursWorked(hours), hourlyRate(rate) {}
    
    double calculatePay() const override {
        return hoursWorked * hourlyRate; // Hours × Rate
    }
};

int main() {
    // Array of Employee pointers (polymorphism)
    Employee* employees[2];
    
    employees[0] = new SalaryEmployee("John", 'D', "Doe", 5000.0);
    employees[1] = new HourlyEmployee("Jane", 'M', "Smith", 160.0, 25.0);
    
    cout << "=== Employee Payroll ===" << endl;
    for (int i = 0; i < 2; i++) {
        cout << employees[i]->getFullName() 
             << " earns: $" << employees[i]->calculatePay() << endl;
    }
    
    // Clean up memory
    for (int i = 0; i < 2; i++) {
        delete employees[i];
    }
    
    return 0;
}