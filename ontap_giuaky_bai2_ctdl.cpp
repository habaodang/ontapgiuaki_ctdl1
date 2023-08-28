#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

//khoi tao cau truc cay
struct Node {
	int key;
	Node* left;
	Node* right;
};

//khoi tao root rong
void init(Node*& root)
{
	root = NULL;
}

#define MAX 100
struct Stack {
	Node* a[MAX];
	int top;
};

void initStack(Stack& s)
{
	s.top = -1;
}

void push(Stack& s, Node *x)
{
	s.a[++s.top] = x;
}

Node* pop(Stack& s)
{
	return s.a[s.top--];
}

bool isEmpty(Stack s)
{
	return s.top < 0;
}
//tao mot node cay rong
Node* createNode(int x)
{
	Node* p = new Node;
	p->key = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}


//them mot node vao cay
void addTree(Node*& root,int x)
{
	// truong hop cay rong
	if (root == NULL)
	{
		root = createNode(x);
	}
	//truong hop cay khong rong
	else
	{
		Node* parent = NULL;
		Node* p = root;

		//tim vi tri de them
		while (p != NULL && p->key != x)
		{
			parent = p;//luu lai node truoc do de thuc hien gan 
			if (x > p->key)
			{
				//neu x lon hon thi doi sang phai
				p = p->right;
			}
			else
			{
				// neu x be hon thi doi sang trai
				p = p->left;
			}
		}

		//thuc hien them
		if (p == NULL)
		{
			p = createNode(x);


			if (x > parent->key)
			{
				// node can them nam ben phai
				parent ->right=p;
			}
			else
			{
				//node can them nam ben trai
				parent->left = p;
			}

		}
	}
}


// doc du lieu tu file 
void readInput(Node*& root)
{
	ifstream f;
	f.open("input.txt");

	// lay dong gia tri tu file luu vao line_values
	string char_number;
	string line_values;
	getline(f, line_values);

	// thuc hien cat chuoi line_values theo dau ',' va them vao trong root
	stringstream ss(line_values);
	while (getline(ss,char_number,','))
	{
		int x = stoi(char_number);// chuyen char_number tu string sang int
		addTree(root, x);
	}

	f.close();
}

//tim kiem trong cay
Node* search(Node* root,int x)
{
	Node* p = root;

	while (p != NULL && p->key != x)
	{
		if (x > p->key)
			// neu x lon hon root thi doi sang phai
			p = p->right;
		else
			// neu x lon hon root thi doi sang trai
			p = p->left;
	}
	return p;

}

void LNRStack(Node* root,Stack &s)
{
	if (root != NULL)
	{
		Node* p = root;
		while (true)
		{
			while (p!= NULL)
			{
				push(s, p);
				p = p->left;
			}

			if (!isEmpty(s))
			{
				Node* r = pop(s);
				cout << r->key << "\t";
				if (r->right != NULL)
					p = r->right;
			}
			else
				break;
		}
	}
}


void NLRStack(Node* root, Stack& s)
{
	if (root != nullptr)
	{
		Node* p = root;
		push(s, p);

		while (!isEmpty(s))
		{
			Node* r = pop(s);
			cout << r->key << "\t";
			if (r->right != NULL)
				push(s, r->right);
			if (r->left != NULL)
				push(s, r->left);
		}
	}
}

void LRNStack(Node* root, Stack& s)
{
	if (root != NULL)
	{
		Node* p = root;
		Stack output;
		initStack(output);
		push(s,p);

		while (!isEmpty(s))
		{
			Node* r = pop(s);
			push(output, r);

			if (r->left != NULL)
				push(s, r->left);
			if (r->right != NULL)
				push(s, r->right);
		}

		while (!isEmpty(output))
		{
			Node* l = pop(output);
			cout << l->key << "\t";
		}
	}
}

//duyet cay bang de quy 
void LNR(Node* root)
{
	if (root != NULL)
	{
		LNR(root->left);
		cout << root->key << "\t";
		LNR(root->right);
	}
}

// xoa node trong cay
void deleteNode(Node*& root, int x)
{
	Node* p = root;
	Node* parent = NULL;

	// tim vi tri can xoa
	while (p != NULL && p->key != x)
	{
		parent = p;
		if (p->key > x)
			p = p->left;
		else
			p = p->right;
	}

	// thuc hien xoa neu tim thay (p khac null)
	if (p != NULL)
	{
		// nut can xoa co 2 cay con
		if (p->left != NULL && p->right != NULL) 
		{

			// tim node thay the trai nhat cua cay con phai
			Node* temp = p->right;

			while (temp->left != NULL)
			{
				parent = temp;
				temp = temp->left;// doi sang trai den khi nao tim duoc node trai nhat
			}

			p->key = temp->key;// cap nhap vi tri node can xoa thanh gia tri node thay the
			p = temp; // cap nhap lai p = temp de xoa node the mang 
			// node the mang duoc xoa tuong tu nhu laf truong hop la node la hoac co mot node
		}

		// xoa node co mot con va xoa node la
		Node* r = NULL;

		// xoa node co mot con
		if (p->left == NULL)
			r = p->right;
		else
			r = p->left;

		if (parent == NULL) // nut can xoa la nut goc
			root = r;
		else
			// xoa node la
			if (parent->key > p->key)
				parent->left = r;
			else
				parent->right = r;

		delete p;
	}
}

void menu(Node*& root,Stack &s)
{
	//nhap lua chon
	char select;
	do
	{
		cout << "\n---------------------------" << endl;
		cout << "[1] Doc file" << endl;
		cout << "[2] LNR" << endl;
		cout << "[3] NLR" << endl;
		cout << "[4] LRN" << endl;
		cout << "[4] xoa node" << endl;
		cout << "\n---------------------------" << endl;
		cout << "Nhap lua chon cua ban: ";
		select = _getch();//bat ki tu ban phim
		system("cls");
	} while (select < '1' || select>'5');

	//thuc hien menu
	switch (select) {
	case '1':
		readInput(root);
		cout << "Da doc du lieu tu file" << endl;
		break;
	case '2':
		cout << "Danh sach cua ban: " << endl;
		LNRStack(root, s);
		break;
	case '3':
		cout << "Danh sach cua ban: " << endl;
		NLRStack(root, s);
		break;
	case '4':
		cout << "Danh sach cua ban: " << endl;
		LRNStack(root, s);
		break;
	case '5':
		int x; cout << "nhap gia tri muon xoa: "; cin >> x;
		deleteNode(root, x);
		cout << "da xoa thanh cong" << endl;
		break;
	}
}

int main()
{
	Node* root;
	Stack s;
	initStack(s);
	init(root);
	char select;
	do
	{
		menu(root,s);

		// tiep tuc chuong trinh
		cout << "\n----------------------" << endl;
		cout << "Tiep tuc nhan phim bat ky" << endl;
		cout << "De thoat nhan phim [0]" << endl;
		cout << "\n----------------------" << endl;
		cout << "Nhap lua chon cua ban: ";

		select = _getch();
		system("cls");
	} while (select != '0');
	return 0;
}