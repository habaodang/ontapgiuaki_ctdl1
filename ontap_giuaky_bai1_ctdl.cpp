#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>// thu vien cho ham _getch
using namespace std;

struct Node
{
	int value;
	Node* next;
};

// khoi tao node rong
void init(Node*& head)
{
	head = NULL;
}

//tao mot node moi
Node* createNode(int x)
{
	Node* p = new Node;
	p->value = x;
	p->next = NULL;
	return p;
}

//duyet(xuat) danh sach
void displayNode(Node* head)
{
	for (Node* p = head; p != NULL; p = p->next)
		cout << p->value << " ";
}

// them vao cuoi danh sach
void addLast(Node*& head,int x)
{
	Node* newnode = createNode(x);
	Node* p = head;

	//truong hop head khong rong
	if (p != NULL)
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = newnode;
	}
	//truong hop head rong 
	else
	{
		head = newnode;
	}
}

//doc file và ghi vao node
void readInput(Node*& head)
{
	//doc file 
	ifstream f;
	f.open("input.txt");

	// lay dong 1 so luong phan tu
	int sl;
	string char_number;
	f >> sl;
	f.ignore();//xoa ki tu enter(xuong dong) tu cin o tren

	// lay dong 2 dong gia tri cac phan tu
	string line_number;
	getline(f, line_number);

	//khoi tao sstream dung de cat chuoi theo token ',' 
	stringstream ss(line_number);
	
	//thuc hien cat chuoi
	while (getline(ss, char_number, ',')) {
		int x = stoi(char_number);//chuyen char_number tu kieu char sang int
		//them vao cuoi danh sach
		addLast(head, x);
	}

	//dong file
	f.close();
}

//sap xep tang dan bubble sort 
void sortRise(Node* head)
{
	Node* p;
	for (p = head; p != NULL; p = p->next)
	{
		for (Node* q = p->next; q != NULL; q = q->next)
		{
			if (p->value > q->value) swap(p->value, q->value);
		}
	}
	head = p;
}

//sap xep giam dan bubble sort
void sortReduce(Node* head)
{
	Node* p;
	for (p = head; p != NULL; p = p->next)
	{
		for (Node* q = p->next; q != NULL; q = q->next)
		{
			if (p->value < q->value) swap(p->value, q->value);
		}
	}
	head = p;
}

// xoa node giai phong bo nho
void cleanNodes(Node*& head)
{
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}
void menu(Node*& head)
{
	//nhap lua chon
	char select;
	do
	{
		cout << "\n---------------------------" << endl;
		cout << "[1] Doc file" << endl;
		cout << "[2] Xuat danh sach" << endl;
		cout << "[3] Sap xep tang dan" << endl;
		cout << "[4] Sap xep giam dan" << endl;
		cout << "\n---------------------------" << endl;
		cout << "Nhap lua chon cua ban: ";
		select = _getch();//bat ki tu ban phim
		system("cls");
	} while (select < '1' || select>'4');

	//thuc hien menu
	switch (select) {
	case '1':
		readInput(head);
		cout << "Da doc du lieu tu file" << endl;
		break;
	case '2':
		cout << "Danh sach cua ban: " << endl;
		displayNode(head);
		break;
	case '3':
		sortRise(head);
		cout << "Da sap xep thanh cong" << endl;
		break;
	case '4':
		sortReduce(head);
		cout << "Da sap xep thanh cong" << endl;
		break;
	}
}
int main()
{
	Node* head;
	init(head);
	char select;
	do
	{
		menu(head);

		// tiep tuc chuong trinh
		cout << "\n----------------------" << endl;
		cout << "Tiep tuc nhan phim bat ky" << endl;
		cout << "De thoat nhan phim [0]" << endl;
		cout << "\n----------------------" << endl;
		cout << "Nhap lua chon cua ban: ";

		select = _getch();
		system("cls");
	} while (select!='0');

	cleanNodes(head);
	return 0;
}