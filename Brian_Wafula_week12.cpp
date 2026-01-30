#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward declarations
class Student;
class Course;

// Course Class
class Course {
private:
    string courseCode;
    string courseName;
    int creditHours;
    vector<Student*> enrolledStudents; // Association: Course has Students
    
public:
    Course(string code, string name, int credits)
        : courseCode(code), courseName(name), creditHours(credits) {}
    
    string getCode() const { return courseCode; }
    string getName() const { return courseName; }
    int getCredits() const { return creditHours; }
    
    void enrollStudent(Student* student);
    void displayEnrolled() const;
};

// Student Class
class Student {
private:
    string studentID;
    string studentName;
    vector<Course*> registeredCourses; // Association: Student has Courses
    
public:
    Student(string id, string name) : studentID(id), studentName(name) {}
    
    string getID() const { return studentID; }
    string getName() const { return studentName; }
    
    void registerCourse(Course* course) {
        registeredCourses.push_back(course);
        course->enrollStudent(this); // Bidirectional association
    }
    
    void displaySchedule() const {
        cout << "\nStudent: " << studentName << " (" << studentID << ")" << endl;
        cout << "Registered Courses:" << endl;
        for (Course* course : registeredCourses) {
            cout << "  - " << course->getCode() 
                 << ": " << course->getName() 
                 << " (" << course->getCredits() << " credits)" << endl;
        }
    }
};

// Course method implementations (dependency on Student)
void Course::enrollStudent(Student* student) {
    enrolledStudents.push_back(student);
}

void Course::displayEnrolled() const {
    cout << "\nCourse: " << courseCode << " - " << courseName << endl;
    cout << "Enrolled Students:" << endl;
    for (Student* student : enrolledStudents) {
        cout << "  - " << student->getName() 
             << " (" << student->getID() << ")" << endl;
    }
}

int main() {
    // Create courses
    Course c1("CSCI101", "Introduction to Programming", 3);
    Course c2("MATH201", "Calculus I", 4);
    Course c3("ENG101", "English Composition", 3);
    
    // Create students
    Student s1("S1001", "Alice Johnson");
    Student s2("S1002", "Bob Smith");
    
    cout << "=== Course Registration System ===\n" << endl;
    
    // Register students for courses
    s1.registerCourse(&c1);
    s1.registerCourse(&c2);
    
    s2.registerCourse(&c1);
    s2.registerCourse(&c3);
    
    // Display student schedules
    s1.displaySchedule();
    s2.displaySchedule();
    
    // Display course enrollments
    c1.displayEnrolled();
    c2.displayEnrolled();
    c3.displayEnrolled();
    
    return 0;
}