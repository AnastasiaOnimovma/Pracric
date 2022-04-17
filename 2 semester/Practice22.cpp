#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;


struct Node{
	int val;
	Node *next;
	Node *prev;
};

int correctInput(string& answ) {

    string numbers = "-0123456789 ";
    for (int j = 0; j < answ.length(); j++) {
        if (numbers.find(answ[j]) == -1) {
            cout << "\x1b[32m" <<"Invalid input"<< "\x1b[0m"<<"\n";
            return  -1;
        }
    }
    return 0;

}
void printList(Node*& first) {
    Node* curr = first;
    while (curr) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << "\n\n";
}
void printArray(int* arr, const int& n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\n";
}
void deleteList(Node* &first)
{
    Node* next; 
    while (first)
    {
        next = first->next;
        delete first;
        first = next;;
    }
}

//получение
Node* listElemIndex(Node* curr, int index, bool err_msg = true) {		//по индексу
    while (curr && (index--))
        curr = curr->next;
    if (err_msg && !curr)
        cout << "\x1b[32m" << "List item not found"<< "\x1b[0m"<<"\n";
    return curr;
}
Node* listElemValue(Node* curr, int &value, bool err_msg = true) {		//по значению
    while(curr && curr->val != value)
        curr = curr->next;
    if (err_msg && !curr)
        cout << "\x1b[32m" <<"List item not found"<< "\x1b[0m" << "\n";
    return curr;
}
Node* takeElem(Node*& first, int &idx, bool print = false) {
    Node* curr = 0;
    cout << "Select input - by value(0) or by index(1) ";
    int value;
    string answer;
    cin >> answer;
    if (correctInput(answer) != 0) return curr;
    value = stoi(answer);
    if (value == 0) {
        cout << "Enter the value: ";
        cin >> answer;
        if (correctInput(answer) != 0) return curr;
        value = stoi(answer);
        curr = listElemValue(first, value);
        Node* idx_search = first;
        idx = 0;
        while (idx_search && idx_search != curr) {
            idx++;
            idx_search = idx_search->next;
        }        
    }
    else if (value == 1) {
        cout << "Enter the index: ";
        cin >> answer;
        if (correctInput(answer) != 0) return curr;
        idx = stoi(answer);
        curr = listElemIndex(first, idx);
    }
    else  cout << "\x1b[32m" << "Invalid input" << "\x1b[0m" << "\n";
    if (print && curr)
        cout << "Your elememnt is " << curr->val<<"\n";
    return curr;
}
void takeElemMain(int*& arr, const int& n, Node*& first) {
    system_clock::time_point begin = system_clock::now();
    int found, idx=-1;
    takeElem(first,idx, 1);
    system_clock::time_point end = system_clock::now();
    duration<double> time = end - begin;
    begin = system_clock::now();
    if (idx >= 0 && idx < n) {
        found = arr[idx];
        cout << found << "\n";
    }  
    end = system_clock::now();
    cout << "List: " << time.count() << " ms\n";
    cout << "Array: " << (end - begin).count() << " ms\n";
}

//создание
void createList(Node* &first, Node*& last, unsigned length) {		//случайный
    Node* curr = 0, * next = 0;
    deleteList(first);
    for (unsigned i = 0; i < length; ++i) {
        curr = new Node;
        curr->val = rand()%100;
        curr->next = next;
        if (next) {
            next->prev = curr;
        }
        else
            last = curr;
        next = curr;
    }
    curr->prev = nullptr;
    first = curr;
}
void createMain(Node*& first, Node*& last, int& n, int* &arr) {
    system_clock::time_point begin = system_clock::now();
    createList(first, last, n);
    system_clock::time_point end = system_clock::now();
    duration<double> time = end - begin;
    begin = system_clock::now();
    int* array = new int[n];
    Node* curr = first;
    for (int i = 0; i < n; ++i, curr = curr->next) {
        array[i] = curr->val;
    }
    delete []arr;
    arr = array;
    end = system_clock::now();
    cout << "List: " << time.count() << " ms\n";
    cout << "Array: " << (end - begin).count() << " ms\n";
}


//ввод
void pushFirst(Node* &curr,Node* &first, Node* &last) {
    curr->prev = nullptr;
    curr->next = nullptr;
    first = curr;
    last = curr; 
}
void pushLast(Node* &curr,Node* & last) {
    curr->prev = last;
    last->next = curr;
    last = curr;
    last->next = nullptr;
}
void enterList(Node*& first, Node*& last, int& n) {		//ввод с клавиатуры
    n = 0;
    Node* p;
    deleteList(first);
    string answer, number;
    cin.ignore();
    cout << "Enter elements: ";
    getline(cin, answer);
    if (correctInput(answer) != 0) return;
    for (int i = 0; i <= answer.length(); i++) {
        if (answer[i] != ' ' && answer[i] != '\0') {
            number += answer[i];
        }
        else {
            Node* p = new Node;
            n++;
            p->val = stoi(number);
            if (first == nullptr) {
                pushFirst(p,first, last);
            }
            else {
                pushLast(p,last);
            }
            number.erase(0, number.length());
            
        }
    }
    cout << "Done\n\n";
}
void enterArray(int* &arr,Node* first, int &n) {
    int* array = new int[n];
    Node* curr = first;
    string imitation;                       
    cout << "Simulating array input(doesn\'t matter, the numbers will not appear in the array): ";
    getline(cin,imitation);
    for (int i = 0; i < n && curr; ++i, curr = curr->next) {
        array[i] = curr->val;
    }
    delete []arr;
    arr = array;
}
void enterMain(Node* &first, Node* &last, int* &arr, int &n) {
    system_clock::time_point begin = system_clock::now();
    enterList(first, last, n);
    system_clock::time_point end = system_clock::now();
    duration<double> time = end - begin;
    begin = system_clock::now();
    enterArray(arr,first, n);
    end= system_clock::now();
    cout << "List: " << time.count() << " ms\n";
    cout << "Array: " << (end - begin).count() << " ms\n";
}

//вставка
void insertToList(Node*& first, Node*& last, const int &idx,const int &val) {
 
    Node* curr_1 = 0, * curr_2 = new Node;
    curr_2->val = val;
    if (idx == -1) {
        if(!first)
        pushFirst(curr_2,first, last);
        else {
            first->prev = curr_2;
            curr_2->next = first;
            curr_2->prev = nullptr;
            first = curr_2;
    }
     return;
    }
    curr_1 = listElemIndex(first, idx);
    if (!curr_1) return;;
    if (curr_1 == last){
        pushLast(curr_2,last);
    }
    else {
        curr_1->next->prev = curr_2;
        curr_2->next = curr_1->next;
        curr_1->next = curr_2;
        curr_2->prev = curr_1;

    }
}
void insertToArray(int* &arr, int &n,const int &idx, const int &value) {
    if (idx > n || idx<-1) return;
    int* arr_new=new int[++n];
    int i=0;
    for (i; i <= idx; ++i) {
        arr_new[i] = arr[i];
    }
    if (idx == -1) arr_new[i] = value;
    else arr_new[i] = value;
    for (++i; i < n; ++i) {
        arr_new[i] = arr[i - 1];
    }
    //?
    delete[]arr;
    arr = arr_new;
}
void insertMain(Node* &first, Node* &last, int* &arr, int &n) {
    int idx, val;
    string answer;
    if (!first) {
        cout << "the list is empty\n";
        idx = -1;
    }
    else {
        cout << "Enter the index after which to insert or \'-1\' to insert to the top: ";
        cin >> answer;
        if (correctInput(answer) != 0) return;
        idx = stoi(answer);
    }
    cout << "Enter the value of new element: ";
    cin >> answer;
    if (correctInput(answer) != 0) return;
    val = stoi(answer);
    system_clock::time_point begin = system_clock::now();
    insertToList(first, last, idx, val);
    system_clock::time_point end = system_clock::now();
    duration<double> time = end - begin;
    begin = system_clock::now();
    insertToArray(arr,n,idx,val);
    end = system_clock::now();
    cout << "List: " << time.count() << " ms\n";
    cout << "Array: " << (end - begin).count() << " ms\n";
}

//удаление
void deleteCurr( Node*& first, Node* &last, int &idx) {  
    Node* curr =0;
    curr = takeElem(first,idx);
    if (!curr) {
        cout << "\x1b[32m" << "List item not found"<< "\x1b[0m" << "\n";
        idx = -1;
        return;
    }
    if (curr==first) {
        if (!first->next) {
            first = nullptr;
            cout << "\x1b[32m" <<"List item deleted\nThe list is empty"<< "\x1b[0m" << "\n";
            return;
        }
        curr = first->next;
        delete first;
        curr->prev = nullptr;
        first = curr;
        cout << "\x1b[32m" <<"List item deleted"<< "\x1b[0m" << "\n";
        return;
    }
    if (curr==last) {
        curr = last->prev;
        delete last;
        curr->next = nullptr;
        last = curr;
        cout << "\x1b[32m" <<"List item deleted"<< "\x1b[0m" << "\n";
        return;
    }
    if (curr) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        cout << "\x1b[32m" << "List item deleted" << "\x1b[0m" << "\n";
        return;
    }
}
void deleteArray(int* &arr, int &n,const int &idx) {
    if (idx >= n || idx < 0) return;
    if (n == 0)return;
    int* arr_new = new int[--n];
    int i;
    for (i = 0; i < idx; ++i) {
        arr_new[i] = arr[i];
    }
    for (i=idx; i < n; ++i) {
        arr_new[i] = arr[i+1];
    }
    delete[]arr;
    arr = arr_new;

}
void deleteMain(int* &arr, int &n, Node*& first, Node*& last) {
    system_clock::time_point begin = system_clock::now();
    int idx = -2;
    deleteCurr(first, last,idx);
    system_clock::time_point end = system_clock::now();
    duration<double> time = end - begin;
    begin = system_clock::now();
    deleteArray(arr, n, idx);
    end = system_clock::now();
    cout << "List: " << time.count() << " ms\n";
    cout << "Array: " << (end - begin).count() << " ms\n";
}

//обмен
void exchangeCurr(Node* &first,Node* &last,const int& index_1, const int& index_2) { //индексы
 
    Node* p_1, * p_2;
    Node* p_mem = new Node;
    p_1 = listElemIndex(first, index_1);
    p_2 = listElemIndex(first, index_2);
    if (!p_1 || !p_2) return;
    if (p_1->next == p_2) {
        p_mem->next = p_2->next;
        p_2->next = p_1;
        p_2->prev = p_1->prev;
        p_1->next = p_mem->next;
        p_1->prev = p_2;
        if (p_1->next != nullptr) {
            p_1->next->prev = p_1;
        }
        if (p_2->prev != nullptr) {
            p_2->prev->next = p_2;
        }
    }
    else if (p_2->next == p_1) {
        p_mem->next = p_1->next;
        p_1->next = p_2;
        p_1->prev = p_2->prev;
        p_2->next = p_mem->next;
        p_2->prev = p_1;
        if (p_2->next != nullptr) {
            p_2->next->prev= p_2;
        }
        if (p_1->prev != nullptr) {
            p_1->prev->next = p_1;
        }
    }
    else {
        if (p_1 != first)
            p_1->prev->next = p_2;
        p_mem->next = p_2->next;
        p_2->next = p_1->next;
        if (p_2 != first)
            p_2->prev->next = p_1;
        p_1->next = p_mem->next;
        p_mem->prev = p_2->prev;
        p_2->prev = p_1->prev;
        p_1->prev = p_mem->prev;
        if (p_1->next != nullptr)
            p_1->next->prev = p_1;
        if (p_2->next != nullptr)
            p_2->next->prev = p_2;
    }
    if (p_1->prev == nullptr)
        first = p_1;
    if (p_2->prev == nullptr)
        first = p_2;
}
void exchangeMain(int*& arr, const int& n, Node*& first, Node*& last) {
    int index_1, index_2;
    string answer;
    system_clock::time_point begin = system_clock::now();
    cout << "Enter the indexes of the elements: ";
    cin >> answer;
    if (correctInput(answer) != 0) return;
    index_1 = stoi(answer);
    cin >> answer;
    if (correctInput(answer) != 0) return;
    index_2 = stoi(answer);
    if (index_1 < 0 || index_2 < 0) {
        cout << "\x1b[32m" << "Invalid indexes" << "\x1b[0m" << "\n";
        return;
    }
    exchangeCurr(first, last, index_1,index_2);
    system_clock::time_point end = system_clock::now();
    duration<double> time = end - begin;
    begin = system_clock::now();
    if (index_1 < n && index_2 <n) 
        swap(arr[index_1], arr[index_2]);
    end = system_clock::now();
    cout << "List: " << time.count() << " ms\n";
    cout << "Array: " << (end - begin).count() << " ms\n";
}

//начало
void menu(Node*& first, Node*& last, int* &arr, int &n) {

    int option;
    string answer;
    cout << "\x1b[31mWhat do you want?\x1b[0m \n" \
        "1. Create a random list\n" \
        "2. Create list by yourself\n" \
        "3. Insert the element\n" \
        "4. Delete element\n" \
        "5. Exhange elements\n" \
        "6. Take element\n" \
        "7. Print array\n" \
        "8. Finish\n" \
        "Enter the option number: ";
    cin >> answer;
    if (correctInput(answer) != 0)
        return;
    option=stoi(answer);
    cout << "\n";
    switch (option) {
    case 1:
        cout << "Enter the size: ";
        cin >> answer;
        if (correctInput(answer) == 0) {
            n = stoi(answer);
            createMain(first, last, n, arr);
            printList(first);
        }
        menu(first, last,arr,n);
        break;
    case 2:
        enterMain(first, last,arr,n);
        menu(first, last,arr,n);
        break;
    case 3:
        insertMain(first, last, arr, n);
        printList(first);
        menu(first, last,arr,n);
        break;
    case 4:
        if (!first) {
            cout <<"\x1b[32m" <<"The list is empty"<< "\x1b[0m" << "\n";
        }
        else {
            deleteMain(arr,n,first, last);
            printList(first);
        }
        menu(first, last,arr,n);
        break;
    case 5:
        if (!first) {
            cout << "\x1b[32m" << "The list is empty" << "\x1b[0m" << "\n";
        }
        else {
            exchangeMain(arr, n, first, last);
            printList(first);
        }
        menu(first, last,arr,n);
        break;
    case 6:
        if (!first) {
            cout << "\x1b[32m" << "The list is empty" << "\x1b[0m" << "\n";
        }
        else
            takeElemMain(arr, n, first);
        menu(first, last,arr,n);
        break;
    case 7:
        printArray(arr, n);
        menu(first, last, arr, n);
        break;
    case 8:
        deleteList(first);
        delete[]arr;
        break;
    default:
        cout << "\x1b[32m" << "Invalid option" << "\x1b[0m" << "\n";
        menu(first, last, arr, n);
        break;
    }
    
}
 
int main() {
    srand(time(NULL));
    int n = 0;
    Node* first = nullptr;
    Node* last = nullptr;
    int* arr = new int[1];
    menu(first, last, arr,n);
	return 0;
}
