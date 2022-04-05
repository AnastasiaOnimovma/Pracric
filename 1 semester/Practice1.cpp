#include <iostream>
using namespace std;
void convertData(long long int value, int order, int &flag)
{
	unsigned long long int mask=1;
	if (order == 32) 
		mask = unsigned int(mask); // �������������� mask � ����������� �� ����������� �����
	mask <<= order - 1;	//���������� 1 � ������
	for (int i = 1; i <= order; i++)
	{
		putchar(value & mask ? '1' : '0');
		mask >>= 1;	
		if (i == 1)
			putchar(' ');
		if (flag==2 && i == 12) //������ ����� ����������� � ��������� double
			putchar(' ');
	    if (flag==1 && i==9) // ����������� ������ float
			putchar(' ');
	}
	cout << "\n";
	++flag;
}
int main() {
	setlocale(0, ""); //��� �������� �����
    cout<<"�����: "<<sizeof(int) << " " << sizeof(short int) << " " << sizeof(long int) << "\n";
    cout<<"������������: "<<sizeof(float) << " " << sizeof(double) << " " << sizeof(long double) << "\n";
    cout<<"����������: "<<sizeof(char) << "\n";
    cout<<"����������: "<<sizeof(bool) << "\n";
	int number_1,flag=0; //flag ����� ��� ��������� �������� � ������ �����
	cout << "������� ����� �����: ";
	cin >> number_1;
	convertData(number_1, sizeof(number_1)*8,flag);
	union {
		int tool_for_f;
		float number_2;
	};
	cout << "������� ������������ ����� (float): ";
	cin >> number_2; 
	convertData(tool_for_f, sizeof(number_2) * 8,flag);
	union {
		long long int tool_for_d;
		double number_3;
	};
	cout << "������� ������������ ����� (double): ";
	cin >> number_3;
	convertData(tool_for_d, sizeof(number_3) * 8,flag);
    return 0;
}