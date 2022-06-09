#include <iostream>
#include <string>
#include "windows.h" 

using namespace std;

string operations = "+-*/";

struct Node {
	string symbol;
	Node* next;
};
struct Stack {
	Node* tail;
	Stack() : tail(nullptr) {}  //конструктор
	bool isEmpty() {
		if (tail == nullptr) return 1;
		return 0;
	}
	void output() {
		cout << "Steak: ";
		Node* curr = tail;
		if (!curr) {
			cout << "Empty";
		}
		while (curr) {
			cout << curr->symbol << " ";
			curr = curr->next;
		}
		cout << "\n";
	}
	string pop(bool print = 1) {
		if (tail == nullptr) return "the end";
		if (print) cout << tail->symbol << " ";
		string answer = tail->symbol;
		Node* p = new Node;
		p = tail;
		tail = tail->next;
		p->next = nullptr;
		delete p;
		return answer;
	}
	void push(string sym) {
		Node* p = new Node;
		p->symbol = sym;
		p->next = tail;
		tail = p;
	}
};

int prior(char c) {
	switch (c) {
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	default: return 0;
	}
}

bool correctInputInf(string& data) {
	bool flag_oper = 0, flag_bracket = 0;
	int count_num = 0, count_oper = 0;
	for (int i = 0; i < data.length(); ++i) {
		if (data[i] == ' ') data.erase(i, 1);
	}
	for (int i = 0; i < data.length(); ++i) {
		if (data[i] == '(') {
			if (!flag_oper && i != 0 || flag_bracket || operations.find(data[i + 1]) != -1) {
				return 0;
			}
			flag_bracket = 1;
		}
		else if (data[i] == ')') {
			if (!flag_bracket || flag_oper || i != data.length() - 1 && operations.find(data[i + 1]) == -1) {
				return 0;
			}
			flag_bracket = 0;
		}
		else if (data[i] >= '0' && data[i] <= '9' || data[i] == '.') {
			flag_oper = 0;
		}
		else if (operations.find(data[i]) != -1) {
			if (i == 0 || i == data.length() - 1) {
				return 0;
			}
			if (flag_oper) {
				return 0;
			}
			flag_oper = 1;
		}
		else if (data[i] == '\0') continue;
		else {
			return 0;;
		}
	}
	return 1;
}
bool correctInputPo(string& data) {
	int count_oper = 0, count_num = 0;
	for (int i = 0; i < data.length(); ++i) {
		if (operations.find(data[i]) != -1) {
			if (i == 0) {
				return 0;
			}
			count_oper++;
		}
		else if (data[i] == ' ') {
			if (operations.find(data[i - 1]) == -1)
				count_num++;
		}
		else if (data[i] >= '0' && data[i] <= '9') {
			if (i == data.length() - 1) {
				return 0;
			}
			continue;
		}
		else if (data[i] == '.' || data[i] == '\0')continue;
		else {
			return 0;
		}
	}
	if (count_oper != count_num - 1) {
		return 0;
	}
	return 1;
}
bool correctInputPre(string& data) {
	int count_oper = 0, count_num = 0;
	if (data[0] == ' ') data.erase(0, 1);
	for (int i = 0; i < data.length(); ++i) {
		if (operations.find(data[i]) != -1) {
			if (i == data.length() - 1) {
				return 0;
			}
			count_oper++;
		}
		else if (data[i] == ' ' || data[i] == '\0') {
			if (operations.find(data[i - 1]) == -1)
				count_num++;
		}
		else if (data[i] >= '0' && data[i] <= '9') {
			if (i == 0) {
				return 0;
			}
			continue;
		}
		else if (data[i] == '.')continue;
		else {
			return 0;
		}
	}
	if (count_oper != count_num - 1) {
		return 0;
	}
	return 1;
}

double action(double& value1, double& value2, string& oper) {
	switch (oper[0]) {
	case '+':
		return value1 + value2;
		break;
	case '-':
		return value1 - value2;
		break;
	case '*':
		return value1 * value2;
		break;
	case '/':
		return value1 / value2;
		break;
	default:
		break;
	}
}
void calculate(string& data, bool prefix) {
	if (prefix) {
		if (!correctInputPre(data)) {
			cout << "Invalid input\n";
			return;
		}
		for (int j = data.length() - 1, i = 0; j >= i; --j, ++i) {
			swap(data[j], data[i]);
		}
	}
	else {
		if (!correctInputPo(data)) {
			cout << "Invalid input\n";
			return;
		}
	}
	Stack numbers;
	string num;
	string  sym;
	double val_1, val_2;
	for (int i = 0; i <= data.length(); i++) {
		sym = data[i];
		if (operations.find(sym) != -1) {
			if (prefix) {
				val_1 = stod(numbers.pop(0));
				val_2 = stod(numbers.pop(0));
			}
			else {
				val_2 = stod(numbers.pop(0));
				val_1 = stod(numbers.pop(0));
			}

			numbers.push(to_string(action(val_1, val_2, sym)));
		}
		if (sym >= "0" && sym <= "9" || sym == ".") {
			num += sym;
		}
		if (sym == " ") {
			if (operations.find(data[i - 1]) != -1) continue;
			if (prefix) {
				for (int j = num.length() - 1, i = 0; j >= i; --j, ++i) {
					swap(num[j], num[i]);
				}
			}
			numbers.push(num);
			num.erase(0, num.length());
		}
	}
	numbers.pop();
	cout << "\n";
}

void convertToPoPN(string& data, bool print = 1) {
	Stack steak;
	string note;
	if (!correctInputInf(data)) {
		cout << "Invalid input\n";
		return;
	}
	string sym;
	for (int i = 0; i <= data.length(); ++i) {
		if (data[i] == ' ') data.erase(i, 1);
	}
	for (int i = 0; i < data.length(); i++) {
		sym = data[i];
		if (sym >= "0" && sym <= "9" || sym == ".") {
			note += sym;
			if (sym == "." || data[i + 1] == '.' || data[i + 1] >= '0' && data[i + 1] <= '9') continue;
			note += " ";
			if (print) {
				cout << "\nString: " << note << "\n";
				steak.output();
				Sleep(500);
			}
		}
		if (sym == "(") {
			steak.push(sym);
			if (print) {
				cout << "\nString: " << note << "\n";
				steak.output();
				Sleep(500);
			}
			continue;
		}
		if (sym == ")") {
			while (steak.tail->symbol != "(") {
				note += steak.pop(0);
				note += " ";
			}
			steak.pop(0);
			if (print) {
				cout << "\nString: " << note << "\n";
				steak.output();
				Sleep(500);
			}
			continue;
		}
		if (operations.find(sym) != -1) {

			if (steak.isEmpty() || prior(steak.tail->symbol[0] < prior(sym[0]))) {
				steak.push(sym);
				if (print) {
					cout << "\nString: " << note << "\n";
					steak.output();
					Sleep(500);
				}
			}
			else {
				while (!steak.isEmpty() && prior(steak.tail->symbol[0]) >= prior(sym[0])) {
					note += steak.pop(0);
					note += " ";
				}
				steak.push(sym);
				if (print) {
					cout << "\nString: " << note << "\n";
					steak.output();
					Sleep(500);
				}
			}
		}
	}
	if (print) {
		cout << "\nString: " << note << "\n";
		steak.output();
		Sleep(500);
	}
	while (!steak.isEmpty()) {
		note += steak.pop(0);
		note += " ";
	};
	if (print) {
		cout << "\nResult: ";
	}
	cout << note << "\n";
	data = note;
}
void convertToPrePN(string& data) {
	if (!correctInputInf(data)) {
		cout << "Invalid input\n";
		return;
	}
	string note;
	for (int j = data.length() - 1; j >= 0; --j) {
		if (data[j] == '(') {
			note += ')';
		}
		else if (data[j] == ')') {
			note += '(';
		}
		else if (data[j] == ' ') continue;
		else {
			note += data[j];
		}
	}
	cout << "Inverted string: " << note << "\n" << "Algorithm: ";
	convertToPoPN(note, 0);
	data.erase(0, data.length());
	for (int j = note.length() - 1; j >= 0; --j) {
		data += note[j];
	}
	data += '\0';
	cout << "Result: " << data << "\n";
}

void menu(string& data) {
	int option;
	cout << "\x1b[31mWhat do you want?\x1b[0m \n" \
		"1. Conversion to a reverse Polish notation(automatic correctness check of the infix entry)\n" \
		"2. Conversion to a Polish prefix notation(automatic correctness check of the infix entry)\n" \
		"3. Calculation of an expression written in reverse Polish notation\n" \
		"4. Calculation of an expression written in prefix Polish notation\n" \
		"5. Checking for the correctness of the entered expression\n" \
		"6. Finish\n" \
		"Enter the option number: ";
	cin >> option;
	switch (option) {
	case 1:
		data.erase(0, data.length());
		cin.ignore();
		getline(cin, data);
		convertToPoPN(data);
		menu(data);
		break;
	case 2:
		data.erase(0, data.length());
		cin.ignore();
		getline(cin, data);
		convertToPrePN(data);
		menu(data);
		break;
	case 3:
		if (!correctInputPo(data)) {
			cout << "You should to enter new reverse(postfix) note: ";
			cin.ignore();
			getline(cin, data);
			data += '\0';
		}
		else {
			cout << "Do you want to enter new reverse(postfix) note? (\'no\'=0) ";
			cin >> option;
			if (option) {
				data.erase(0, data.length());
				cin.ignore();
				getline(cin, data);
				data += '\0';
			}
		}
		calculate(data, 0);
		menu(data);
		break;
	case 4:
		if (!correctInputPre(data)) {
			cout << "You should to enter new prefix note: ";
			cin.ignore();
			getline(cin, data);
			data += '\0';
		}
		else {
			cout << "Do you want to enter new prefix note? (\'no\'=0) ";
			cin >> option;
			if (option) {
				data.erase(0, data.length());
				cin.ignore();
				getline(cin, data);
				data += '\0';
			}
			else
				cin.ignore();
		}
		calculate(data, 1);
		menu(data);
		break;
	case 5:
		cout << "What kind of notation you want to check(1-infix,2-prefix, 3-postfix)? ";
		cin >> option;
		cout << "Enter the expression: ";
		data.erase(0, data.length());
		cin.ignore();
		getline(cin, data);
		data += '\0';
		switch (option) {
		case 1:
			if (correctInputInf(data)) {
				cout << "Correct\n";
			}
			else {
				cout << "Not correct\n";
			}
			break;
		case 2:
			if (correctInputPre(data)) {
				cout << "Correct\n";
			}
			else {
				cout << "Not correct\n";
			}
			break;
		case 3:
			if (correctInputPo(data)) {
				cout << "Correct\n";
			}
			else {
				cout << "Not correct\n";
			}
			break;
		default:
			cout << "Invalid input\n";
		}
		menu(data);
		break;
	case 6:
		break;
	}

}
int main() {
	string data = "";
	menu(data);
	return 0;
}
