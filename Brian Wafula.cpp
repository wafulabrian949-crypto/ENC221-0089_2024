#include <iostream>
#include <string>
using namespace std;

class Roommate {
public:
    string name;
    int age;
    string studentId;
    string height;
    string nickName;
    string hobby;
    string course;
    string college;

    void displayInfo() {
        cout << " Roommate Information " << endl;
        cout << "--------------------------" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Student ID: " << studentId << endl;
        cout << "Height: " << height << endl;
        cout << "Nickname: " << nickName << endl;
        cout << "Hobby: " << hobby << endl;
        cout << "Course: " << course << endl;
        cout << "College: " << college << endl;
        cout << "--------------------------" << endl;
        cout << "That is my amazing friend!" << endl;
    }
};

int main() {
    Roommate my_roommate;
    
    my_roommate.name = "Gerald Asmin";
    my_roommate.age = 21;
    my_roommate.studentId = "ENC221-0088/2024";
    my_roommate.height = "180cm";
    my_roommate.nickName = "palsa";
    my_roommate.hobby = "dancing";
    my_roommate.course = "Geomatic Engineering";
    my_roommate.college = "COETEC";
    
    my_roommate.displayInfo();
    
    return 0;
}
