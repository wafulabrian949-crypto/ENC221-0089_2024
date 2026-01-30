#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // Create array of 20 integers (1-100)
    int numbers[20];
    srand(time(0));
    
    // Fill with random numbers 1-100
    for (int i = 0; i < 20; i++) {
        numbers[i] = rand() % 100 + 1;
    }
    
    // Create arrays for odd and even values
    int oddValues[20], evenValues[20];
    int oddCount = 0, evenCount = 0;
    
    // Separate odd and even values
    for (int i = 0; i < 20; i++) {
        if (numbers[i] % 2 == 0) {
            evenValues[evenCount] = numbers[i];
            evenCount++;
        } else {
            oddValues[oddCount] = numbers[i];
            oddCount++;
        }
    }
    
    // Display original array
    cout << "Original array: ";
    for (int i = 0; i < 20; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Display even values array
    cout << "Even values array: ";
    for (int i = 0; i < evenCount; i++) {
        cout << evenValues[i] << " ";
    }
    cout << endl;
    
    // Display odd values array
    cout << "Odd values array: ";
    for (int i = 0; i < oddCount; i++) {
        cout << oddValues[i] << " ";
    }
    cout << endl;
    
    return 0;
}