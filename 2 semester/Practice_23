#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

vector<int> parent, rang;

struct Edge {
	int u, v, weight;
	bool operator<(Edge const& other) {
		return weight < other.weight;
	}
};
void printGraph(vector<Edge>& graph, const int& n) {
	int e = floor(sqrt(n * 2)) + 1;
	int** arr = new int* [e];
	for (int i = 0; i < e; ++i)
		arr[i] = new int[e] {};
	int k = 0;
	for (int i = 0; i < e; i++) {
		for (int j = i; j < e; j++) {
			if (i == j) arr[i][j] = 0;
			else {
				arr[i][j] = graph[k].weight;
				arr[j][i] = arr[i][j];
				k++;
			}

		}
	}
	for (int i = 0; i < e; i++)
		for (int j = 0; j < e; j++) {
			if (arr[i][j] / 10 < 1) cout << " ";
			cout << arr[i][j];
			if (j == e - 1) cout << "\n";
			else cout << " ";
		}
	cout << "\n";
	for (int i = 0; i < e; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}
void enterGraph(vector<Edge>& graph, int& n) {
	cout << "Size: ";
	cin >> n;
	graph.resize(n * (n - 1) / 2);
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			graph[k].u = i;
			graph[k].v = j;
			cout << "Input " << i << "-" << j<<": ";
			cin>>graph[k].weight;
			k++;
		}
	}
	n = n * (n - 1) / 2;
	cout << "Your graph:\n";
	printGraph(graph, n);
}
void createGraph(vector<Edge> &graph, int &n) {
	n = 246+ rand() % (10);
	int k = 0;
	graph.resize(n * (n - 1) / 2);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			graph[k].u = i;
			graph[k].v = j;
			graph[k].weight = rand() % (100);
			if (i == 0 && graph[k].weight == 0) graph[k].weight == 1;
			k++;
		}
	}
	n = n * (n - 1) / 2;
	cout << "Graph was created\n";
}
void readGraph(vector<Edge>& graph, int& n)   {
	ifstream File;
	n = 4;
	graph.resize(n * (n - 1) / 2);
	File.open("C:\\Users\\Юля\\ex_graph.txt", ios::binary);
	if (!File.is_open())
	{
		cout << "Can not open\n";
		return;
	}
	char ch;
	int ignore = 1, read = 1, i = 0, j = 0, k = 0;
	while (!File.eof()) 
	{
		for (int e = 1; e <= ignore; e++) {
			File >> ch;
			i++;
			if (i % n == 0) {
				i = 0;
				j++;
			}
		}
		ignore++;
		for (int p = n - 1; p >= read; p--) {
			File >> graph[k].weight;
			graph[k].u = j;
			graph[k].v = i;
			k++;
			i++;
			if (i % n == 0) {
				i = 0;
				j++;
			}
		}
		read++;
	}
	n = n * (n - 1) / 2;
	File.close();
	printGraph(graph, n);
}


void Merge(vector<Edge> graph,int &n, int first, int last){ 
	int middle, start, final, j;
	int* mas = new int[n];
	middle = (first + last) / 2; 
	start = first; 
	final = middle + 1; 
	for (j = first; j <= last; j++) 
		if ((start <= middle) && ((final > last) || (graph[start].weight < graph[final].weight))){
			mas[j] = graph[start].weight;
			start++;
		}
		else{
			mas[j] = graph[final].weight;
			final++;
		}
	for (j = first; j <= last; j++) graph[j].weight = mas[j];
	delete[]mas;
};
void MergeSort(vector<Edge> &graph,int &n, int first, int last){ //n*logn
	if (first < last){
		MergeSort(graph,n, first, (first + last) / 2); 
		MergeSort(graph,n, (first + last) / 2 + 1, last); 
		Merge(graph,n, first, last); 
	}	
}
void Shell(vector<Edge> graph, int& n) { //от n*logn до n^2
	int d = n/2;
	d = d/2;
	int j;
	while (d>0) {
		for (int i = 0; i < n - d; i++) {
			j = i;
			while (j >= 0 && graph[j].weight > graph[j + d].weight) {
				swap(graph[j].weight, graph[j + d].weight);
				j--;
			}
		}
		d = d / 2;
	}
}
	
void make_set(int v) {
	parent[v] = v;
	rang[v] = 0;
}
int find_set(int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
		if (rang[a] < rang[b])
			swap(a, b);
		parent[b] = a;
		if (rang[a] == rang[b])
			rang[a]++;
	}
}
void Kraskal(vector<Edge>& graph, int& n, bool small=true) {
	int cost = 0;
	int ver = floor(sqrt(n * 2)) + 1;
	vector<vector<int>> result(ver, vector<int>(ver));
	parent.resize(ver);
	rang.resize(ver);
	for (int i = 0; i < ver; i++)
		make_set(i);
	system_clock::time_point begin = system_clock::now();
	Shell(graph, n);
	system_clock::time_point end = system_clock::now();
	cout << "Shellsort: "<< (end - begin).count()<<" ms\n";
	begin = system_clock::now();
	MergeSort(graph,n, 0, n - 1);
	end = system_clock::now();
	cout << "Merge: " << (end - begin).count() << " ms\n";
	begin = system_clock::now();
	sort(graph.begin(), graph.end());
	end = system_clock::now();
	cout << "Default sort: " << (end - begin).count() << " ms\n";
	for (Edge e : graph) {
		if (find_set(e.u) != find_set(e.v) && e.weight!=0) {
			cost += e.weight;
			result[e.u][e.v] = e.weight;
			result[e.v][e.u] = e.weight;
			union_sets(e.u, e.v);
		}
	}
	int par = parent[0];
	for (int i = 1; i < ver; i++) {
		if (parent[i] != par) {
			cout << "Not connected\n";
			return;
		}
	}
	if (small) {
		cout << "Minimum spanning tree:\n";
		cout.setf(ios::right);
		for (int i = 0; i < ver; i++) {
			for (int j = 0; j < ver; j++) {
				cout.width(3);
				cout << result[i][j];
			}
			cout << "\n";
		}
		cout.unsetf(ios::right);
	}
	cout <<"Weight: " << cost << "\n";
	result.clear();
} 

void menu(vector<Edge>& graph, int& n) {
	int answer;
	cout << "\x1b[31mWhat do you want?\x1b[0m \n" \
		"1. Kraskal's algorithm for n=10000\n" \
		"2. Kraskal's algorithm algorithm for small graphs\n" \
		"3. Finish\n" \
		"Enter the option number: ";
	cin >> answer;
	switch (answer) {
	case 1:
		createGraph(graph, n);
		Kraskal(graph, n,0);
		menu(graph,n);
		break;
	case 2:
		cout << "You can enter the graph(1) or read it from file(2) ";
		cin >> answer;
		if (answer == 1) enterGraph(graph, n);
		else if (answer == 2) readGraph(graph, n);
		else {
			cout << "Wrong number\n";
			menu(graph, n);
		}
		Kraskal(graph, n);
		menu(graph, n);
		break;
	case 3:
		break;
	default:
		cout << "Wrong number\n";
		menu(graph, n);
		break;
	}


}
int main() {
	srand(time(NULL));
	vector<Edge> graph;
	int n=0;
	menu(graph, n);
	graph.clear();
	return 0;
}
