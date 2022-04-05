#include <iostream>
#include <string>
#include<windows.h>
#include <conio.h>
#include <iomanip>   
using  namespace std;

struct Student
{
	string full_name;
	char sex;
	int group;
	int number_in_group;
	int ex_1, ex_2, ex_3;
	int test_1, test_2, test_3, test_4, test_5;
};

void menu(Student students[], int& quan);
void createStudent(Student students[], int& quan);
void changeNote(Student students[], int& quan);
void outputData(Student students[], int& quan);
void groupOfStudents(Student students[], int& quan);
void sexOfStudents(Student students[], int& quan);
void numberInGroupOfStudents(Student students[], int& quan);
void topOfStudents(Student students[], int& quan);
void exam_marks(Student students[], int& quan);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Student students[50] = {"Лученкова Валерия Дмитриевна",'Ж',1323,9,5,4,5,4,5,4,4,5,"Иванов Иван Иванович",'М',1234,8,5,3,4,5,4,3,5,4,
	"Янезнаев Анатолий Дамблдорович",'М',1323,23,3,3,3,4,4,5,3,4,"Кристиан Тревельян Грей",'М',0,1,5,5,5,5,5,5,5,5};
	students[4].full_name = "Ростова Наталья Ильична";
	students[4].sex = 'Ж';
	students[4].group = 1324;
	students[4].number_in_group = 8;
	students[4].ex_1 = 2;
	students[4].ex_2 = 2;
	students[4].ex_3 = 2;
	students[4].test_1 = 3;
	students[4].test_2 = 4;
	students[4].test_3 = 5;
	students[4].test_4 = 3;
	students[4].test_5 = 4;
	int quan = 4;
	menu(students, quan);
	return 0;
}
void menu(Student students[], int& quan) {
	int option;
	cout << "\x1b[31mВозможные действия:\x1b[0m \n" \
		"1. Создать запись\n" \
		"2. Внести изменения\n" \
		"3. Вывод всех данных\n" \
		"4. Вывод информации о группе\n" \
		"5. Вывод рейтинга студентов за последнюю сессию\n" \
		"6. Вывод количества студентов мужского и женского пола\n" \
		"7. Ранжирование по успеваемости \n" \
		"8. Вывод данных о студентах, имеющих определённый номер списке\n" \
		"9. Завершить\n" \
		"Введите число:  ";
	cin >> option;
	switch (option) {
	case 1:
		createStudent(students, ++quan);
		break;
	case 2:
		changeNote(students, quan);
		break;
	case 3:
		outputData(students, quan);
		break;
	case 4:
		groupOfStudents(students, quan);
		break;
	case 5:
		topOfStudents(students, quan);
		break;
	case 6:
		sexOfStudents(students, quan);
		break;
	case 7:
		exam_marks(students, quan);
		break;
	case 8:
		numberInGroupOfStudents(students, quan);
		break;
	case 9:
		break;
	}
}
void outputTheMain(Student &stud, int &count) {
	cout << count << setw(50) << stud.full_name << "   " << stud.sex << setw(10) << stud.group;
	cout << setw(12) << stud.number_in_group << setw(5) << stud.ex_1 << setw(4) << stud.ex_2 << setw(4) << stud.ex_3;
	cout << setw(4) << stud.test_1 << setw(4) << stud.test_2 << setw(4) << stud.test_3;
	cout << setw(4) << stud.test_4 << setw(4) << stud.test_5 << "\n";
}
void createStudent(Student students[], int &quan) {
	string name;
	cout << "Введите полное имя студента(ФИО): ";
	for (int i = 0; i <= 2; ++i) {
		cin >> name;
		students[quan].full_name += name+' ';
	}
	cout << "Введите пол (М,Ж): ";
	cin >> students[quan].sex;
	cout << "Введите номер группы: ";
	cin >> students[quan].group;
	cout << "Введите номер в группе: ";
	cin >> students[quan].number_in_group;
	cout << "Введите оценки за экзамены (н-р: 5 4 3): ";
	cin >> students[quan].ex_1;
	cin >> students[quan].ex_2;
	cin>> students[quan].ex_3;
	cout << "Введите оценки за зачёты (н-р: 3 3 4 4 5): ";
	cin >> students[quan].test_1;
	cin >> students[quan].test_2;
	cin >> students[quan].test_3;
	cin >> students[quan].test_4;
	cin >> students[quan].test_5;
	cout << "\n";
	menu(students, quan);
}
void changeNote(Student students[], int  &quan) {
	int numb, answer;
	string name;
	cout << "Введите порядковый номер студента(всего "<<quan+1<<" студентов): ";
	cin >> numb;
	do {
		cout << "Введите параметр для изменения\n1.ФИО\n2.Пол\n3.Группа\n4.Номер в группе\n5.Оценки сессии\n6.Оценки зачётной недели\n";
		cin >> answer;
		if (answer < 5)
			cout << "Новые данные: ";
		switch(answer) {
		case(1): 
			students[numb-1].full_name.clear();
			for (int i = 0; i <= 2; ++i) {
			cin >> name;
			students[numb-1].full_name += name + ' ';
		}
			break;
		case(2): 
			cin >> students[numb - 1].sex;
			break;
		case(3): 
			cin >> students[numb - 1].group;
			break;
		case(4): 
			cin >> students[numb - 1].number_in_group;
			break;
		case(5): 
			cout << "Введите номер экзамена: ";
			cin >> answer;
			cout << "Новые данные: ";
			if (answer == 1)
				cin >> students[numb - 1].ex_1;
			else if (answer == 2)
				cin >> students[numb - 1].ex_2;
			 else if (answer == 3)
				cin >> students[numb - 1].ex_3;
			break;
		case(6):
			cout << "Введите номер зачёта: ";
			cin >> answer;
			cout << "Новые данные: ";
			if (answer == 1)
				cin >> students[numb - 1].test_1;
			else if (answer == 2)
				cin >> students[numb - 1].test_2;
			else if (answer == 3)
				cin >> students[numb - 1].test_3;
			else if (answer == 4)
				cin >> students[numb - 1].test_4;
			else if (answer == 5)
				cin >> students[numb - 1].test_5;
			break;
		default:
			cout << "Неверный параметр";
		}
		cout << "Введите 0, чтобы закончить и любое другое число, чтобы продолжить ";
		cin >> answer;
	} while (answer);
	cout << "\n";
	menu(students, quan);
}
void outputData(Student students[],int &quan) {
	cout <<setw(50) << "ФИО" << " Пол" << setw(10) << "№ группы" << setw(12) << "№ в группе";
	cout << "  Эк1" << " Эк2" << " Эк3" << " Зч1" << " Зч2" << " Зч3" << " Зч4" << " Зч5"<<"\n";
	int count = 1;
	for (int i = 0; i <= quan; ++i) {
		outputTheMain(students[i],count);
		count++;
	}
	menu(students, quan);
}
void groupOfStudents(Student students[], int& quan) {
	cout << "Введите номер группы: ";
	int N,count=1;
	cin >> N;
	cout << setw(50) << "ФИО" << " Пол" << setw(10) << "№ группы" << setw(12) << "№ в группе";
	cout << "  Эк1" << " Эк2" << " Эк3" << " Зч1" << " Зч2" << " Зч3" << " Зч4" << " Зч5" << "\n";
	for (int i = 0; i <= quan; ++i) {
		if (students[i].group == N) {
			outputTheMain(students[i], count);
			count++;
		}
	}
	cout << "\n";
	menu(students, quan);
}
void sexOfStudents(Student students[], int &quan) {
	int girls = 0;
	for (int i = 0; i <= quan; ++i) {
		if (students[i].sex == 'Ж')
			girls++;
	}
	cout << "Количество студентов мужского пола - " << quan-girls+1 << ", женского - " << girls<<"\n\n";
	menu(students, quan);
}
void numberInGroupOfStudents(Student students[], int& quan) {
	cout << "Введите номер в группе: ";
	int k, count = 1;
	cin >> k;
	cout << setw(50) << "ФИО" << " Пол" << setw(10) << "№ группы" << setw(12) << "№ в группе";
	cout << "  Эк1" << " Эк2" << " Эк3" << " Зч1" << " Зч2" << " Зч3" << " Зч4" << " Зч5" << "\n";
	for (int i = 0; i <= quan; ++i) {
		if (students[i].number_in_group == k) {
			outputTheMain(students[i], count);
			count++;
		}
	}
	cout << "\n";
	menu(students, quan);
}
bool search(int arr[],int &quan, int &elem){
	for (int i = 0; i <= quan; ++i) {
		if (elem == arr[i])
			return 1;
	}
	return 0;
}
void topOfStudents(Student students[], int& quan) {
	cout << "Топ студентов\n";
	float max = 0.0;
	int the_best, j=0, arr[50];   //массив индексов
	int count=1;
	for (int z = 0; z < 50; z++)
		arr[z] = -1;
	cout << setw(50) << "ФИО" << " Пол" << setw(10) << "№ группы" << setw(12) << "№ в группе";
	cout << "  Эк1" << " Эк2" << " Эк3" << " Зч1" << " Зч2" << " Зч3" << " Зч4" << " Зч5" << "\n";
	for (int i=0; i<=quan;++i) {
		max = 0.0;
		for (int i = 0; i <= quan; ++i) {
			if (((students[i].ex_1 + students[i].ex_2 + students[i].ex_3) / 3.0) > max  && !(search(arr, quan, i))) {
				max = (students[i].ex_1 + students[i].ex_2 + students[i].ex_3) / 3;
				the_best = i;
			}
		}
		arr[j] = the_best;
		j++;
		outputTheMain(students[the_best], count);
		count++;	
	}
	cout << "\n";
	menu(students, quan);
}
void exam_marks(Student students[], int& quan) {
	int count = 1;
	cout << setw(50) << "ФИО" << " Пол" << setw(10) << "№ группы" << setw(12) << "№ в группе";
	cout << "  Эк1" << " Эк2" << " Эк3" << " Зч1" << " Зч2" << " Зч3" << " Зч4" << " Зч5" << "\n";
	cout << "Студенты, лишённые стипендии\n";
	for (int i = 0; i <= quan; ++i) {
		if (students[i].ex_1 <= 3 || students[i].ex_2 <= 3 || students[i].ex_3 <= 3 || students[i].test_1 <= 3 || students[i].test_2 <= 3 || students[i].test_3 <= 3 || students[i].test_4 <= 3 || students[i].test_5 <= 3)
		{
			outputTheMain(students[i], count);
			count++;
		}
	}
	count = 1;
	cout << "Студенты-\"хорошисты\"\n";
	for (int i = 0; i <= quan; ++i) {
		if ((students[i].ex_1 + students[i].ex_2 + students[i].ex_3 + students[i].test_1 + students[i].test_2 + students[i].test_3 + students[i].test_4 + students[i].test_5) / 8.0 != 5)
			if (students[i].ex_1 > 3 && students[i].ex_2 > 3 && students[i].ex_3 > 3 && students[i].test_1 > 3)
				if (students[i].test_2 > 3 && students[i].test_3 > 3 && students[i].test_4 > 3 && students[i].test_5 > 3)
				{
					outputTheMain(students[i], count);
					count++;
				}

	}
	count = 1;
	cout << "Студенты - \"отличники\"\n";
	for (int i = 0; i <= quan; ++i) {
		if ((students[i].ex_1 + students[i].ex_2 + students[i].ex_3 + students[i].test_1 + students[i].test_2 + students[i].test_3 + students[i].test_4 + students[i].test_5) / 8.0 == 5) {
			outputTheMain(students[i], count);
			count++;
		}
	}
	menu(students, quan);
}