#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char operation, choice;
    
    do {
        cout << "\n=== Simple Calculator ===" << endl;
        cout << "Enter first number: ";
        cin >> num1;
        
        cout << "Enter operator (+, -, *, /): ";
        cin >> operation;
        
        cout << "Enter second number: ";
        cin >> num2;
        
        cout << "\nResult: ";
        
        switch(operation) {
            case '+':
                cout << num1 << " + " << num2 << " = " << (num1 + num2) << endl;
                break;
            case '-':
                cout << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
                break;
            case '*':
                cout << num1 << " * " << num2 << " = " << (num1 * num2) << endl;
                break;
            case '/':
                if (num2 != 0) {
                    cout << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
                } else {
                    cout << "Error! Division by zero." << endl;
                }
                break;
            default:
                cout << "Error! Invalid operator." << endl;
        }
        
        cout << "\nDo you want to perform another calculation? (y/n): ";
        cin >> choice;
        
    } while(choice == 'y' || choice == 'Y');
    
    cout << "\nThank you for using the calculator!" << endl;
    
    return 0;
}