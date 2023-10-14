#include<iostream>
#include<fstream>
using namespace std;

template<class T>
struct node
{
	T val;
	node<T>* next = NULL;
};
template<class T>
class stack
{
	int size = 0;
	node<T>* Top = NULL;
public:
	void push(T a)
	{
		if (Top == NULL)
		{
			Top = new node<T>;
			Top->val = a;
			size++;
		}
		else
		{
			node<T>* temp = new node<T>;
			temp->val = a;
			temp->next = Top;
			Top = temp;
			size++;
		}
	}
	void pop()
	{
		if (Top->next != NULL)
		{
			node<T>* temp = Top;
			Top = Top->next;
			temp = NULL;
			delete temp;
			size--;
		}
		else
		{
			Top = NULL;
			size--;
		}
	}
	int sizeofstack()
	{
		return size;
	}
	void clear()
	{
		while (!isEmpty())
		{
			pop();
		}
	}
	bool isEmpty()
	{
		if (size == 0)
			return true;
		return false;
	}
	node<int>* Peek()
	{
		if (Top == NULL)
		{
			node<T>* temp = NULL;
			return temp;
		}
		return Top;
	}

};

template <class T>
struct Node
{
	T data;
	Node* next = NULL;
};

template <class T>
class list {
public:
	Node<T>* head = NULL;
	list()
	{
		head = NULL;
	}
	void insert(T a)
	{
		if (head == NULL)
		{
			head = new Node<T>;
			head->data = a;
		}
		else
		{
			Node<T>* curr = head;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = new Node<T>;
			curr = curr->next;
			curr->data = a;
		}
	}
};

struct Var
{
	bool flag = false;
	int timer = -1;
	int lower = -1;
};

int total = 0;
class Graph
{
	int nodes;
	list<int>* list_nodes;
	Var* list_scc;
	int time;
	int SCC_Total = 0;
	stack<int> store_scc;

public:

	Graph(int a)
	{
		nodes = a;
		list_nodes = new list<int>[a];
		list_scc = new Var[a];
		time = 0;
	}
	void AddNode(int a1, int a2)
	{
		list_nodes[a1].insert(a2);
	}
	void Initialize(int a)
	{
		time++;
		list_scc[a].lower = time;
		list_scc[a].timer = time;
		list_scc[a].flag = true;
		store_scc.push(a);
	}
	void Stack_Removal(int a)
	{
		int t3 = list_scc[a].lower;
		int t4 = list_scc[a].timer;
		int temp;
		total = 0;
		if (t3 == t4)
		{
			while (store_scc.Peek()->val != a)
			{
				temp = store_scc.Peek()->val;
				list_scc[temp].flag = false;
				store_scc.pop();
				total++;
			}
			temp = store_scc.Peek()->val;
			list_scc[temp].flag = false;
			store_scc.pop();
			total++;
			if (total > SCC_Total)
			{
				SCC_Total = total;
			}
		}
	}
	void Time_Setter(int a, int temp)
	{
		int t2 = list_scc[temp].lower;
		int t3 = list_scc[a].lower;
		if (t3 < t2)
		{
			list_scc[a].lower = t3;
		}
		else
		{
			list_scc[a].lower = t2;
		}
	}
	void help(int a)
	{
		Initialize(a);
		int temp;
		Node<int>* curr = list_nodes[a].head;
		while (curr != NULL)
		{
			temp = curr->data;
			int t1 = list_scc[temp].timer;
			if (t1 == -1)
			{
				help(temp);
				Time_Setter(a, temp);
			}
			else if (list_scc[temp].flag == true)
			{
				int t3 = list_scc[a].lower;
				if (t3 < t1)
				{
					list_scc[a].lower = t3;
				}
				else
				{
					list_scc[a].lower = t1;
				}
			}
			curr = curr->next;
		}
		Stack_Removal(a);
		curr = NULL;
		delete curr;
	}
	void SCC()
	{
		cout << "SCC Counter" << endl;
		for (int i = 0; i < nodes; i++)
		{
			if (list_nodes[i].head == NULL)
			{
				continue;
			}
			if (list_scc[i].flag == false)
				help(i);
		}
	}
	int get_SCC()
	{
		return SCC_Total;
	}
	void Get_Percentage_SCC()
	{
		cout << "Total Strongly Connected Components : " << SCC_Total << endl;
	}
};

int main()
{
	string file = "web-Google.txt";
	ifstream obj;
	int a1, a2;
	int count;
	int len = -1;
	obj.open(file);
	if (obj.is_open())
	{
		while (!obj.eof())
		{
			obj >> count;
			if (count > len)
				len = count;
		}
	}
	obj.close();
	cout << len << endl;
	len++;
	Graph g(len);
	obj.open(file);
	if (obj.is_open())
	{
		while (!obj.eof())
		{
			obj >> a1 >> a2;
			g.AddNode(a1, a2);
		}
	}
	obj.close();
	g.SCC();
	g.Get_Percentage_SCC();
}

