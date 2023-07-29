#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node 
{
	// typedef int T;
	// using T = int; // template ���� �ٲ� ����

public:
	Node(int data) : data(data), prev(nullptr), next(nullptr){}

public:
	T data;
	Node* prev;
	Node* next;
};

template <typename T>
class List
{
public:
	List()
	{
		// dummy 
		_head = new Node<T>(0);
		_tail = new Node<T>(0);
		_head->next = _tail;
		_tail->prev = _head;
	}

	~List()
	{
		Node<T>* node = _head;
		while (node)
		{
			/*
			�Űܴٴϴ� cursor ����
			Node* nextNode = node->next;
			node = nextNode;
			*/
			Node<T>* deleteNode = node;
			node = node->next;
			delete deleteNode;
		}
	}
	
	/*
	�������� �Լ�

	Ư�� ��� ��ġ�� ������ �Ǿ����� ���� ���������� ������.
	���Ḯ��Ʈ�� Ư���� Ư�� ��� ��ġ�� ����Ǿ����� �ʴٸ� 
	����Ž���� �ؾ��ϹǷ� �ð����⵵�� O(N)�̱� �����̴�.
	*/
	Node<T>* GetNode(int index)
	{
		Node<T>* node = _head->next;
		if (node == _tail)
			return nullptr;

		for (int i = 0; i < index; i++)
		{
			if (node == _tail->prev)
				return nullptr;

			node = node->next;
		}

		return node;
	}

	void Print()
	{
		Node* node = _head->next; // cursor
		while (node != _tail)
		{
			cout << node->data << " ";
			node = node->next;
		}
		cout << endl;
	}

	// no dummy ver.
	// [head]    [tail]
	Node<T>* AddAtHead(int data)
	{
		Node<T>* node = new Node<T>(data);
		
		if (_head == nullptr)
		{
			_head = node;
			_tail = node;
		}
		else
		{
			Node<T>* nextNode = _head;
			node->next = nextNode;
			nextNode->prev = node;
			_head = node;
		}
	}

	//      [node]
	// [dummy]<->[nextNode]<->[2]<->[3]<->[dummy]
	// [head]                             [tail]
	Node<T>* AddAtHead_dummy(int data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* nextNode = _head->next;

		node->next = nextNode;
		nextNode->prev = node;
		_head->next = node;
		node->prev = _head;

		return node;
	}

	//                                 [node]
	// [dummy]<->[1]<->[2]<->[prevNode]<->[dummy]
	// [head]                             [tail]
	Node<T>* AddAtTail(int data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* prevNode = _tail->prev;

		prevNode->next = node;
		node->prev = prevNode;
		node->next = _tail;
		_tail->prev = node;

		return node;
	}

	//                   [node]
	// [dummy]<->[prevNode]<->[posNode]<->[3]<->[dummy]
	// [head]                                   [tail]
	void Insert(Node<T>* posNode, int data)
	{
		Node<T>* node = new Node<T>(data);
		Node<T>* prevNode = posNode->prev;

		prevNode->next = node;
		node->prev = prevNode;
		node->next = posNode;
		posNode->prev = node;
	}

	// [dummy]<->[prevNode]<->[node]<->[nextNode]<->[3]<->[dummy]
	// [head]                                             [tail]
	Node<T>* Remove(Node<T>* node)
	{
		Node<T>* prevNode = node->prev;
		Node<T>* nextNode = node->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		delete node;

		return nextNode;
	}

private:
	Node<T>* _head = nullptr;
	Node<T>* _tail = nullptr;
};

