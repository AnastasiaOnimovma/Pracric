#include <iostream>
#include<windows.h>
#include "header.h"
using namespace std;


void menu() {
	cout << "\x1b[33mChoose section :\x1b[0m \n" \
		"1. Data types and their internal representation in memory\n" \
		"2. Îne-dimensional static arrays\n" \
		"3. Pointers and multidimensional static arrays\n" \
		"4. Text strings as arrays of characters\n" \
		"5. Finish\n" \
		"Enter a number: ";
	int answer;
	cin >> answer;
	switch (answer) {
	case 1:
		Practice1();
		break;
	case 2:
		 Practice2();
		 break;
	case 3:
		Practice3();
		break;
	case 4:
		Practice4();
		break;
	case 5:
		break;

	}
}
int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu();
	return 0;
}