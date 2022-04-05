#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include "header.h"

using namespace std;
using namespace chrono;

void start(int array[], int& size);

void writeArray(int array[], int& size) {
	for (int i = 0; i < size; ++i)
		cout << "\x1b[32m" << array[i] << "\x1b[0m" << " ";     //управл€юща€ последовательность дл€ вывода зелЄным цветом
	cout << "\n\n";
	start(array, size);
}
void createArray(int array[], int& size) {
	int min_value = 1 - size, max_value = size - 1; //исключительно, чтобы дальнейша€ формула выгл€дела пон€тнее
	for (int i = 0; i < size; ++i)
		array[i] = min_value + rand() % (max_value - min_value + 1); // ‘ормула дл€ получени€ случайного числа
	writeArray(array, size);
}
void quickSort(int array[], int& size, int first, int last) {
	int f = first, l = last, middle = array[(f + l) / 2];
	do {
		while (array[f] < middle)
			f++;
		while (array[l] > middle)
			l--;
		if (f <= l) {
			swap(array[f], array[l]);
			f++;
			l--;
		}
	} while (f < l);
	if (first < l)
		quickSort(array, size, first, l);
	if (f < last)
		quickSort(array, size, f, last);

}
void findMaxMin(int array[], int& size) {
	system_clock::time_point begin = system_clock::now();
	cout << "Minimum: " << array[0] << "\nMaximum: " << array[size - 1] << "\n";
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	cout << "Working time: " << time.count() << " ms\n";
	begin = system_clock::now();
	int max = -100, min = 100;
	for (int i = 0; i < size; i++) {
		max = array[i] > max ? array[i] : max;
		min = array[i] < min ? array[i] : min;
	}
	cout << "The unoptimized algorithm is completed\n";
	end = system_clock::now();
	time = end - begin;
	cout << "Working time (unoptimized): " << time.count() << " ms\n\n";
	start(array, size);

}
void magicWithAverage(int array[], int& size) {
	int average, count = 0;
	average = round((array[0] + array[size - 1]) / 2);
	cout << "Average value = " << average << "\nIndexes: ";
	for (int i = 0; array[i] <= average; ++i) {
		if (array[i] == average) {
			cout << i << " ";
			count++;
		}
	}
	if (count == 0)
		cout << "no";
	cout << "\nQuantity: " << count << "\n\n";
	start(array, size);
}
void findSmaller(int array[], int& size) {
	int numb_a, quan_s = 0;							 // название сгенерировано по условию)))
	cout << "Enter a number to find the smaller ones: ";
	cin >> numb_a;
	for (int i = 0; array[i] < numb_a && i < size; ++i)
		quan_s++;
	cout << "Quantity of smaller ones: " << quan_s << "\n\n";
	start(array, size);
}
void findBigger(int array[], int& size) {
	int numb_b, quan_b = 0;
	cout << "Enter a number to find the bigger ones: ";
	cin >> numb_b;
	for (int i = size - 1; i >= 0 && array[i] > numb_b; --i)
		quan_b++;
	cout << "Quantity of bigger ones: " << quan_b << "\n\n";
	start(array, size);

}
void binSearch(int array[], int& size) {
	cout << "Enter a number: ";
	int required_num, left = 0, right = size - 1, middle;
	bool flag = false;
	cin >> required_num;
	cin.sync();
	system_clock::time_point begin = system_clock::now();
	while (left <= right) {
		middle = (left + right) / 2;
		if (required_num < array[middle])
			right = middle - 1;
		else if (required_num > array[middle])
			left = middle + 1;
		else {
			flag = true;
			break;
		}
	}
	if (flag)
		cout << "Exist\n";
	else
		cout << "Not exist\n";
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	cout << "Working time: " << time.count() << " ms\n";
	begin = system_clock::now();         //алгоритм перебора(*)
	for (int i = 0; i < size; ++i) {
		if (required_num == array[i])
			break;
	}
	cout << "The unoptimized algorithm is completed\n";
	end = system_clock::now();
	time = end - begin;
	cout << "Working time (unoptimized): " << time.count() << " ms\n\n";
	start(array, size);
}
void replaceElements(int array[], int& size) {
	int index_1, index_2;
	cout << "Enter indexes: ";
	cin >> index_1 >> index_2;
	cin.sync();
	system_clock::time_point begin = system_clock::now();
	swap(array[index_1], array[index_2]);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	cout << "Working time: " << time.count() << " ms\n";
	writeArray(array, size);

}
void start(int array[], int& size) {
	unsigned option;
	system_clock::time_point begin, end;
	duration<double> time;
	cout << "\x1b[31mWhat do you want?\x1b[0m \n" \
		"1. Create an array\n" \
		"2. Sort array\n" \
		"3. Find the maximum and minimum (only after 2)\n" \
		"4. Output the average value (only after 2)\n" \
		"5. Print the number smaller than the entered value (only after 2)\n" \
		"6. Print the number bigger than the entered value (only after 2)\n" \
		"7. Find out if there is a number in the array\n" \
		"8. Change array elements\n" \
		"9. Finish\n" \
		"Enter the option number: ";
	cin >> option;
	cin.sync();
	cout << "\n";
	switch (option) {
	case 1:
		createArray(array, size);
		break;
	case 2:
		begin = system_clock::now();
		quickSort(array, size, 0, size - 1);
		end = system_clock::now();
		time = end - begin;
		cout << "Working time: " << time.count() << " ms\n";
		writeArray(array, size);
		break;
	case 3:
		findMaxMin(array, size);
		break;
	case 4:
		magicWithAverage(array, size);
		break;
	case 5:
		findSmaller(array, size);
		break;
	case 6:
		findBigger(array, size);
		break;
	case 7:
		binSearch(array, size);
		break;
	case 8:
		replaceElements(array, size);
		break;
	case 9:
		menu();
		break;
	}

}
void Practice2() {
	const int n = 100;
	int size = n;
	int array[n];
	start(array, size);
}
