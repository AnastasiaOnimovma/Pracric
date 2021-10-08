#include <iostream>
using namespace std;
int data(long long int value, int order, int flag)
{
	unsigned long long int mask=1;
	if (order == 32) 
		mask = unsigned int(mask); // преобразование mask в зависимости от размерности числа
	mask <<= order - 1; //перемещаем 1 в начало
	for (int i = 1; i <= order; i++)
	{
		putchar(value & mask ? '1' : '0');
		mask >>= 1;	
		if (i == 1)
			putchar(' ');
		if (flag==2 && i == 12) //пробел между экспонентой и мантиссой double
			putchar(' ');
	    if (flag==1 && i==9) // аналогичный пробел float
			putchar(' ');
	}
	cout << "\n";
	return ++flag;
}
int main() {
	setlocale(0, ""); //для русского языка
    cout<<"Öåëûå: "<<sizeof(int) << " " << sizeof(short int) << " " << sizeof(long int) << "\n";
    cout<<"Âåùåñòâåííûå: "<<sizeof(float) << " " << sizeof(double) << " " << sizeof(long double) << "\n";
    cout<<"Ñèìâîëüíûé: "<<sizeof(char) << "\n";
    cout<<"Ëîãè÷åñêèé: "<<sizeof(bool) << "\n";
	int number_1,flag=0; //flag нужен для отделения разрядов у разных типов
	cout << "Ââåäèòå öåëîå ÷èñëî: ";
	cin >> number_1;
	flag= data(number_1, sizeof(number_1)*8,flag);
	union {
		int tool_for_f;
		float number_2;
	};
	cout << "Ââåäèòå âåùåñòâåííîå ÷èñëî (float): ";
	cin >> number_2; 
	flag= data(tool_for_f, sizeof(number_2) * 8,flag);
	union {
		long long int tool_for_d;
		double number_3;
	};
	cout << "Ââåäèòå âåùåñòâåííîå ÷èñëî (double): ";
	cin >> number_3;
	flag=data(tool_for_d, sizeof(number_3) * 8,flag);
    return 0;
}
