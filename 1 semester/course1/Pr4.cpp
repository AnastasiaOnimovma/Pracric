#include <iostream>
#include <string>
#include<windows.h>
#include <fstream>
#include "header.h"

using namespace std;

/*Русккий: Win-1251*/

/*
 Задание 3- 3
 Задание 4- 2
*/
unsigned char Smaller(unsigned char c)  // В маленькие буквы 
{
    if ((c >= 0x41 && c <= 0x5A) || c >= 0xC0 && c <= 0xDF) c = c + 0x20;
    return c;
}
unsigned char Bigger(unsigned char c)  // В большие буквы 
{
    if ((c >= 0x61 && c <= 0x7A) || (c >= 0xE0 && c <= 0xFF)) c = c - 0x20;
    return c;
}
void directSearch(string& text, string& str_part, int& size, int& part_size) {
    int res = -1;
    cout << "Positions of substring: ";
    for (int i = 0; i < size - part_size + 1; ++i)
        for (int j = 0; j < part_size; ++j)
            if (str_part[j] != text[i + j])
                break;
            else if (j == part_size - 1) {
                res = i;
                cout << res << " ";
                break;
            }
    if (res == -1) cout << "no";
    cout << "\n";

}
void badChar(unsigned char str[], int size, int badchar[]) //шаблон- таблица
{
    int i;
    for (i = 0; i < 256; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}
void searchBM(string& text, string& str_part, int& size, int& part_size)
{
    int badchar[256];
    unsigned char text_copy[1024], str_part_copy[1024];
    bool flag = true;
    for (int i = 0; i < size; ++i) {
        text_copy[i] = text[i];
    }
    for (int i = 0; i < part_size; ++i) {
        str_part_copy[i] = str_part[i];
    }
    badChar(str_part_copy, part_size, badchar);
    int shift = 0;
    cout << "Positions of substring: ";
    while (shift <= (size - part_size))
    {
        int j = part_size - 1;
        while (j >= 0 && str_part_copy[j] == text_copy[shift + j])
            j--;
        if (j < 0)
        {
            cout << shift << " ";
            flag = false;
            shift += (shift + part_size < size) ? part_size - badchar[text_copy[shift + part_size]] : 1;
        }

        else
            shift += max(1, j - badchar[text_copy[shift + j]]);
    }
    if (flag) cout << "no";
    cout << "\n";
}
bool readFile(string& text) {
    ifstream File;
    File.open("C:\\Users\\Юля\\practice_example.txt", ios::binary);
    if (!File.is_open())
    {
        cout << "Can not open\n";
        return 0;
    }
    char Buf[1024];
    while (!File.eof()) // Читаем все строки из файла и выводим их на экран
    {
        File.getline(Buf, 1024);
    }
    text = string(Buf);
    cout << text << endl;
    File.close();

    return 1;
}


void Practice4()
{
    cin.ignore();
    string text, punct = ".,-—!?:;'\"()", numbers = "0123456789", end_sent = ".!?";
    string answer_1;
    cout << "Choose the input method: by yourseif(0), from file(1) ";
    getline(cin, answer_1);
    if (answer_1 == "0") {
        cout << "Enter a text: ";
        getline(cin, text);
    }
    else if (answer_1 == "1") readFile(text);
    else {
        cout << "Wrong number\n";
        menu();
    }
    cout << "\n";
    int size = text.length();
    cout << "Edited: ";
    for (int i = 0; i < size; ++i) {
        if (i < size - 1 && text[i] == ' ' && text[i] == text[i + 1]) {
            ++i;
        }
        if (i < size - 2 && text[i] == '.' && text[i] == text[i + 1] && text[i + 1] == text[i + 2]) {
            cout << "...";
            i += 3;
        }
        if (i < size - 1 && punct.find(text[i]) != -1 && text[i] == text[i + 1]) {
            ++i;
        }
        if (i == 0 || (i >= 2 && end_sent.find(text[i - 2]) != -1)) cout << Bigger(char(text[i]));
        else cout << Smaller(char(text[i]));

    }
    cout << "\nText without numbers: ";
    for (int i = 0; i < size; ++i) {
        if (numbers.find(text[i]) == -1) cout << text[i];
    }
    cout << "\nThe number of characters in each word: ";
    for (int i = 0, count = 0; i < size; ++i) {
        if (punct.find(text[i]) != -1) --count;
        if (text[i] == ' ') {
            if (count != 0) cout << count << " ";
            count = 0;
        }
        else if (text[i + 1] == '\0') {
            ++count;
            cout << count;
        }
        else
            ++count;

    }
    string str_part;
    cout << "\nEnter string: ";
    cin >> str_part;
    int part_size = str_part.length();
    int  answer = 1;
    while (answer) {
        cout << "Choose a search algorithm: Direct(0), Boyer Moore(1) ";
        cin >> answer;
        cin.sync();
        switch (answer) {
        case 0:
            directSearch(text, str_part, size, part_size);
            break;
        case 1:
            searchBM(text, str_part, size, part_size);
            break;
        default:
            cout << "Wrong number";
        }
        cout << "Enter sign numder to repeat and 0 to finish ";
        cin >> answer;
        cin.sync();
    }
    menu();

}