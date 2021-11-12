#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
using namespace std;
using namespace chrono;
void start(int arr[], int& size);
void writeArray(int arr[], int& size) {
	for (int i = 0; i < size; ++i)
		cout << "\x1b[32m" << arr[i] << "\x1b[0m" << " ";     //управл€юща€ последовательность дл€ вывода зелЄным цветом
	cout << "\n\n";
	start(arr, size);
}
void createArray(int arr[], int& size) {
	int min_value = 1 - size, max_value = size - 1; //исключительно, чтобы дальнейша€ формула выгл€дела пон€тнее
	for (int i = 0; i < size; ++i)
		arr[i] = min_value + rand() % (max_value - min_value + 1); // ‘ормула дл€ получени€ случайного числа
	writeArray(arr, size);
}
void quickSort(int arr[], int& size, int first, int last) {
	int f = first, l = last, middle = arr[(f + l) / 2];
	do {
		while (arr[f] < middle)
			f++;
		while (arr[l] > middle)
			l--;
		if (f <= l) {
			swap(arr[f], arr[l]);
			f++;
			l--;
		}
	} while (f < l);
	if (first < l)
		quickSort(arr, size, first, l);
	if (f < last)
		quickSort(arr, size, f, last);

}
void findMaxMin(int arr[], int& size) {
	system_clock::time_point begin = system_clock::now();
	cout << "Minimum: " << arr[0] << "\nMaximum: " << arr[size - 1] << "\n";
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	cout << "Working time: " << time.count() << " ms\n";
	begin = system_clock::now();
	int max = -100, min = 100;
	for (int i = 0; i < size; i++) {
		max = arr[i] > max ? arr[i] : max;
		min = arr[i] < min ? arr[i] : min;
	}
	cout << "The unoptimized algorithm is completed\n";
	end = system_clock::now();
	time = end - begin;
	cout << "Working time (unoptimized): " << time.count() << " ms\n\n";
	start(arr, size);

}
void magicWithAverage(int arr[], int& size) {
	int average, count = 0;
	average = round((arr[0] + arr[size-1]) / 2);
	cout << "Average value = " << average << "\nIndexes: ";
	for (int i = 0; arr[i] <= average; ++i) {
		if (arr[i] == average) {
			cout << i << " ";
			count++;
		}
	}
	if (count == 0)
		cout << "no";
	cout << "\nQuantity: " << count << "\n\n";
	start(arr, size);
}
void findSmaller(int arr[], int& size) {
	int numb_a, quan_s = 0;							 // название сгенерировано по условию)))
	cout << "Enter a number to find the smaller ones: ";
	cin >> numb_a;
	for (int i = 0; arr[i] < numb_a && i < size; ++i)
		quan_s++;
	cout << "Quantity of smaller ones: " << quan_s << "\n\n";
	start(arr, size);
}
void findBigger(int arr[], int& size) {
	int numb_b, quan_b = 0;
	cout << "Enter a number to find the bigger ones: ";
	cin >> numb_b;
	for (int i = size - 1; i >= 0 && arr[i] > numb_b; --i)
		quan_b++;
	cout << "Quantity of bigger ones: " << quan_b << "\n\n";
	start(arr, size);

}
void binSearch(int arr[], int& size) {
	cout << "Enter a number: ";
	int required_num, left = 0, right = size - 1, middle;
	bool flag = false;
	cin >> required_num;
	cin.sync();
	system_clock::time_point begin = system_clock::now();
	while (left <= right) {
		middle = (left + right) / 2;
		if (required_num < arr[middle])
			right = middle - 1;
		else if (required_num > arr[middle])
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
		if (required_num == arr[i])
			break;
	}
	cout << "The unoptimized algorithm is completed\n";
	end = system_clock::now();
	time = end - begin;
	cout << "Working time (unoptimized): " << time.count() << " ms\n\n";
	start(arr, size);
}
void replaceElements(int arr[], int& size) {
	int index_1, index_2;
	cout << "Enter indexes: ";
	cin >> index_1 >> index_2;
	cin.sync();
	system_clock::time_point begin = system_clock::now();
	swap(arr[index_1], arr[index_2]);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	cout << "Working time: " << time.count() << " ms\n";
	writeArray(arr, size);

}
void start(int arr[], int& size) {
	unsigned option;
	system_clock::time_point begin, end;
	duration<double> time;
	cout << "What do you want? \n" \
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
		createArray(arr, size);
		break;
	case 2:
		begin = system_clock::now();
		quickSort(arr, size, 0, size - 1);
		end = system_clock::now();
		time = end - begin;
		cout << "Working time: " << time.count() << " ms\n";
		writeArray(arr, size);
		break;
	case 3:
		findMaxMin(arr, size);
		break;
	case 4:
		magicWithAverage(arr, size);
		break;
	case 5:
		findSmaller(arr, size);
		break;
	case 6:
		findBigger(arr, size);
		break;
	case 7:
		binSearch(arr, size);
		break;
	case 8:
		replaceElements(arr, size);
		break;
	case 9:
		break;
	}

}
int main() {
	srand(time(NULL)); // устанавливаем начальное значение дл€ рандома
	const int n = 100;
	int size = n;
	int arr[n];
	start(arr, size);
	return 0;
}
