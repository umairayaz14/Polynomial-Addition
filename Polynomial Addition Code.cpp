//Open in Visual Studio because libraries such as chrono have been used to find time which is not available in Dev C++

#include <iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<chrono>
using namespace::std;

class Array
{
	int** arr;
	int size1;
	int size2;
	int* sum;
	int count;

public:

	Array(int s1, int s2)
	{

		size1 = s1;
		size2 = s2;
		count = 0;
		arr = new int* [size1];
		for (int i = 0; i < size1; i++)
		{
			arr[i] = new int[size2];
		}
		sum = new int[size2];
		for (int z = 0; z < size2; z++)
		{
			sum[z] = 0;
		}
	}

	void insert(string name)
	{
		fstream example;
		example.open(name, ios::in);
		int data1;
		int data2;
		example >> data1;
		example >> data2;

		for (int i = 0; i < size1; i++)
		{
			for (int j = 0; j < size2; j++)
			{
				example >> arr[i][j];
				if (arr[i][j] != 0)
				{
					count++;
				}
			}
		}

		example.close();


	}

	void addition()
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int x = 0; x < size2; x++)
		{
			for (int z = 0; z < size1; z++)
			{
				sum[x] = sum[x] + arr[z][x];
			}
		}
		cout << endl;
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "time taken: " << elapsed.count() << "sec" << endl;
	}
	void display()
	{
		for (int i = 0; i < size1; i++)
		{
			for (int j = 0; j < size2; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}

	}
	void display1(string name)
	{
		fstream result("resultarray.txt", ios::out);
		cout << "Result: ";
		result << name << endl;
		for (int i = 0; i < size2; i++)
		{
			cout << sum[i] << " ";
			result << "Result : " << sum[i] << " ";

		}
		cout << endl;
		cout << "filename is: " << name << endl;
		cout << "no of non-zero coefficients: " << count << endl;
		cout << "no of polynomials: " << size1 << endl;
		cout << "no of variables: " << size2 << endl;
		cout << "data structure used: Array" << endl;
	}
};

class Linkedlist
{
	struct node {
		int num;
		int power;
		node* left;
		node* right;
	};
	node* root;
	node* traverse;
	node* header;
	int row;
	int coloumn;
	int varcount;
	int nocomp;
public:

	Linkedlist(int x, int y)
	{
		row = x;
		coloumn = y;
		root = NULL;
		traverse = NULL;
		header = NULL;
		varcount = 0;
	}

	void insert(string name)
	{
		int count = 0;
		int power = 0;
		int num, a, b;
		fstream example(name, ios::in);
		example >> a;
		example >> b;
		while (!example.eof())
		{
			example >> num;
			if (num != 0)
			{
				varcount++;
			}
			node* ptr = new node;
			ptr->num = num;
			ptr->left = NULL;
			ptr->right = NULL;
			if (root == NULL)
			{
				ptr->power = power;
				power++;
				root = ptr;
				traverse = root;
				header = root;
				count++;
			}
			else
			{
				if (count != coloumn)
				{
					ptr->power = power;
					traverse->left = ptr;
					power++;
					traverse = ptr;
					count++;
				}
				else
				{
					power = 0;
					count = 0;
					ptr->power = power;
					power++;
					count++;
					header->right = ptr;
					header = header->right;
					traverse = header;

				}
			}

		}
		example.close();
	}

	void display()
	{
		header = root;
		for (int i = 0; i < row; i++)
		{
			traverse = header;
			for (int j = 0; j < coloumn; j++)
			{
				cout << traverse->num << "x" << traverse->power << " ";
				traverse = traverse->left;
			}
			cout << endl;
			header = header->right;
		}
	}

	void add()
	{
		auto start = std::chrono::high_resolution_clock::now();
		node* rowt;
		node* colt;
		colt = root->right;
		rowt = root;
		header = root->right;
		for (int i = 0; i < (row - 1); i++)
		{
			for (int j = 0; j < coloumn; j++)
			{
				rowt->num = rowt->num + header->num;
				rowt = rowt->left;
				header = header->left;
				nocomp++;
			}
			header = colt->right;
			colt = colt->right;
			rowt = root;
			nocomp++;
		}
		delete root->right;
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "time taken: " << elapsed.count() << "sec";
	}

	void resultdisplay(string name)
	{
		fstream result("resultlinkedlist.txt", ios::out);
		result << name << endl;
		traverse = root;
		cout << endl << "Result: ";
		for (int i = 0; i < coloumn; i++)
		{
			cout << traverse->num << "x" << traverse->power << " ";
			result << "Result : " << traverse->num << " ";
			traverse = traverse->left;

		}
		result.close();
		cout << endl;
		cout << "filename is: " << name << endl;
		cout << "no of non-zero variables: " << varcount << endl;
		cout << "no of polynomials: " << row << endl;
		cout << "no of variables: " << coloumn << endl;
		cout << "data structure used: Linkedlist" << endl;
		cout << "no of comparisons: " << nocomp << endl;

	}
};

int main()
{
	fstream example;
	string fname;
	cout << "Enter file name: ";
	getline(cin, fname);
	int option;
	int nopoly1;
	int nopoly2;
	example.open(fname, ios::in);
	example >> nopoly1;
	example >> nopoly2;
	example.close();
	class Array a(nopoly1, nopoly2);
	class Linkedlist l(nopoly1, nopoly2);
	a.insert(fname);
	l.insert(fname);
	bool exit = true;
	while (exit)
	{
		cout << endl;
		cout << "Press 1 to display contents of the file," << endl;
		cout << "Press 2 to perform polynomial addition using array," << endl;
		cout << "Press 3 to perform polynomial addition using linked list," << endl;
		cout << "Press any other key to exit: ";
		cin >> option;
		cout << endl;
		switch (option)
		{
		case 1:
		{
			a.display();
			cout << endl;
			l.display();
			cout << endl;
			break;
		}

		case 2:
		{
			a.addition();
			a.display1(fname);
			cout << endl;
			break;
		}

		case 3:
		{

			l.add();
			l.resultdisplay(fname);
			cout << endl;

			break;
		}

		default:
		{
			exit = false;
		}
		}
	}
	return 0;
}

