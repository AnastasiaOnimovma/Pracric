#include <iostream>
#include "windows.h" 
#include "header.h"
using namespace std;

/* ЛОГИКА ПРОГРАММЫ

Если n- размерность кв. матрицы, а i- порядковый номер элемента, то
i+1  - движение по строке,
i+n - движение по столбцу
i + (n / 2) - перемещение с соседнюю по горизонтали четверть
Аналогично производятся все остальные перемещения между четвертями - чисто математически


*/



int getRandomNumber(int min, int max) {
    int num = min + rand() % (max - min + 1); // Формула для получения случайного числа
    return num;
}
void writeArray(int** arr, int& size) {
    for (int* s = arr[0], *f = s + (size * size - 1), count = 1; s <= f; ++s, count++) {
        if (*s / 10 < 1) cout << " ";
        cout << *s;
        if (count % size == 0) cout << "\n";
        else cout << " ";
    }
    cout << "\n";
}
void clearScreen(int& size)                   // чуть более удобный, чем мог бы быть, вывод
{
    for (int n = 0; n < 50; n++)
        cout << "\n";

}
void moveLikeSpiral(int** arr, int& size, int* ptr) {            //при желании можно было уложиться с меньшим количеством циклов, однако его не было
    for (int* i = *arr, *f = i + (size * size - 1); i <= f; ++i) {
        *i = 0;
    }
    ptr = *arr;
    int turn;           // отображает количество элементов в строке/столбце спирали(постоянно уменьшается до  момента заполнения спирали)
    turn = size - 1;

    while (turn >= 1) {
        for (int i = 0; i <= turn; i++) {             // заполнение движением влево
            *ptr = getRandomNumber(1, size * size);
            writeArray(arr, size);
            Sleep(500);
            clearScreen(size);
            ptr = ptr + 1;
        }
        ptr = ptr - 1 + size;
        turn--;
        for (int i = 0; i <= turn; i++) {              //вниз
            *ptr = getRandomNumber(1, size * size);
            writeArray(arr, size);
            Sleep(500);
            clearScreen(size);
            ptr = ptr + size;
        }
        ptr = ptr - size - 1;
        for (int i = 0; i <= turn; i++) {               //вправо
            *ptr = getRandomNumber(1, size * size);
            writeArray(arr, size);
            Sleep(500);
            clearScreen(size);
            ptr = ptr - 1;
        }
        ptr = ptr + 1 - size;
        turn--;
        for (int i = 0; i <= turn; i++) {               //вверх
            *ptr = getRandomNumber(1, size * size);
            writeArray(arr, size);
            Sleep(500);
            clearScreen(size);
            ptr = ptr - size;
        }
        ptr = ptr + size + 1;
    }
    writeArray(arr, size);
}
void moveLikeSnake(int** arr, int& size, int* ptr) {
    for (int* i = *arr, *f = i + (size * size - 1); i <= f; ++i) {
        *i = 0;
    }
    ptr = *arr;
    for (int i = 0, f = size - 1; i <= f; ++i) {
        for (int s = 0, k = size - 1; s <= k; s++) {      // заполнение по направлениям: вверх и вниз
            *ptr = getRandomNumber(1, size * size);
            writeArray(arr, size);
            Sleep(500);
            clearScreen(size);
            if (ptr >= *arr + size && *(ptr - size) == 0)
                ptr = ptr - size;
            else ptr = ptr + size;
        }
        ptr = ptr - size + 1;
        *ptr = getRandomNumber(1, size * size);

    }
    writeArray(arr, size);
}
void changeInCircleA(int** arr, int& size, int* ptr) {
    ptr = *arr;
    int temp_1, temp_2;                        // для замены переменных
    for (int i = 1, f = (size / 2) * (size / 2); i <= f; ++i) {
        temp_1 = *(ptr + (size / 2));           // 2 и 1 четверти (аналогично координатным)
        *(ptr + (size / 2)) = *ptr;
        ptr = ptr + (size / 2);

        temp_2 = *(ptr + size * (size / 2));        //1 и 4 четверти
        *(ptr + size * (size / 2)) = temp_1;
        ptr = ptr + size * (size / 2);

        temp_1 = *(ptr - (size / 2));               //4 и 3 четвети
        *(ptr - (size / 2)) = temp_2;
        ptr = ptr - (size / 2);

        *(ptr - size * (size / 2)) = temp_1;       // 3 и 2 четверти
        ptr = ptr - size * (size / 2);

        if (i % (size / 2) == 0 && i != f) ptr = ptr + (size / 2) + 1;
        else ptr = ptr + 1;
    }
    writeArray(arr, size);
}
void changeDiagonallyB(int** arr, int& size, int* ptr) {
    ptr = *arr;
    for (int i = 1, f = size * size / 2; i <= f; ++i) {
        if (i % size <= (size / 2) && i % size != 0) {        // 2 и 4 четверти (аналогично координатным)
            swap(*ptr, *(ptr + (size / 2) * (size + 1)));
        }
        else {                                                  // 1 и 3 четверти
            swap(*ptr, *(ptr + (size / 2) * (size + 1) - size));
        }
        ptr = ptr + 1;
    }
    writeArray(arr, size);
}
void changeVerticallyC(int** arr, int& size) {
    for (int* s = *arr, *f = s + (size * size / 2 - 1); s <= f; ++s) {
        swap(*s, *(s + size * size / 2));
    }
    writeArray(arr, size);
}
void changeHorizontallyD(int** arr, int& size, int* ptr) {
    ptr = *arr;
    for (int i = 1, f = size * size / 2; i <= f; ++i) {
        swap(*ptr, *(ptr + size / 2));
        if (i % (size / 2) == 0 && i != f) ptr = ptr + (size / 2) + 1; //пермещение указателя в пределах четверти на строку ниже
        else ptr = ptr + 1;
    }
    writeArray(arr, size);

}

void Practice3()
{
    int size, answer=1;
    cout << "Enter the size: ";
    cin >> size;
    int** arr = new int* [size];
    for (int i = 0; i < size; ++i)
        arr[i] = new int[size] {};
    int* ptr = *arr;
    while (answer) {
        cout << "Task 1. Choose the option of filling the array: a(0), b(1) ";
        cin >> answer;
        switch (answer) {
        case 0:
            moveLikeSpiral(arr, size, ptr);
            break;
        case 1:
            moveLikeSnake(arr, size, ptr);
            break;

        }
        cout << "Enter sign numder to repeat and 0 to finish ";
        cin >> answer;
    }
    answer = 1;
    while (answer) {
        cout << "Task 2. Choose the option of cnanging the array: a(0), b(1), c(2), d(3) ";
        cin >> answer;
        switch (answer) {
        case 0:
            changeInCircleA(arr, size, ptr);
            break;
        case 1:
            changeDiagonallyB(arr, size, ptr);
            break;
        case 2:
            changeVerticallyC(arr, size);
            break;
        case 3:
            changeHorizontallyD(arr, size, ptr);
            break;
        }
        cout << "Enter sign numder to repeat and 0 to finish ";
        cin >> answer;
    }

    cout << "Task 3" << "\n";
    int flag = true;                           //bubble sort
    while (flag) {
        flag = false;
        for (int* s = *arr, *f = s + (size * size - 1); s < f; ++s) {
            if (*s > *(s + 1)) {
                swap(*s, *(s + 1));
                f--;
                flag = true;
            }
        }
    }
    writeArray(arr, size);

    int number;
    answer = 1;
    while (answer) {
        cout << " Task 4. Choose a command: addition(0) subtraction(1) multiplication(2) division(3) ";
        cin >> answer;
        cout << "Enter a number: ";
        cin >> number;
        cin.sync();
        for (int* s = *arr, *f = s + (size * size - 1); s <= f; ++s) {
            switch (answer) {
            case 0:
                *s = *s + number;
                break;
            case 1:
                *s = *s - number;
                break;
            case 2:
                *s = *s * number;
                break;
            case 3:
                *s = *s / number;
                break;
            }
        }
        writeArray(arr, size);
        cout << "Enter sign numder to repeat and 0 to finish ";
        cin >> answer;
    }
    
    delete[] arr;
    menu();
}