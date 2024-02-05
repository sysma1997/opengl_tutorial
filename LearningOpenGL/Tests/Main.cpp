#include <iostream>
#include <conio.h>

#include "SimpleWindow/SimpleWindow.h"
#include "Triangle/Triangle.h"
#include "Rectangle/Rectangle.h"

using namespace std;

int main() {
	cout << "Welcome to examples opengl learning.\n";

	while (true) {
		cout << "Select number to init example:\n\n";
		cout << "1 - Simple windows\n";
		cout << "2 - Triangle\n";
		cout << "3 - Rectangle\n";
		cout << "10 - Exit\n";
		cout << "Digit your option: ";
		
		int option = 0;
		cin >> option;
		cout << '\n';

		if (option == 1)
			simpleWindow();
		else if (option == 2)
			triangle();
		else if (option == 3)
			rectangle();
		else if (option == 10)
			break;

		system("cls");
	}

	cout << "Created by: SYSMA\n";

	return 0;
}