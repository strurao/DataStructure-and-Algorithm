#include <iostream>
using namespace std;

class Node
{
public:
	Node(int data) : data(data) {}

public:
	int data;
	Node* prev = nullptr;
	Node* next = nullptr;
};

int main()
{
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);

	// [head]				   [tail]
	// [1]<->[2]<->[3]<->[4]<->[5] // ����� ���Ḯ��Ʈ
	n1->next = n2;
	n2->prev = n1;

	n2->next = n3;
	n3->prev = n2;

	n3->next = n4;
	n4->prev = n3;

	n4->next = n5;
	n5->prev = n4;

	Node* head = n1;
	Node* tail = n5;
}