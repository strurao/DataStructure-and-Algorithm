#pragma once

class Node 
{
	// typedef int T;
	using T = int; // template 으로 바꿀 예정

public:
	Node(int data) : data(data), prev(nullptr), next(nullptr){}

public:
	T data;
	Node* prev;
	Node* next;
};

class List
{
public:
	List()
	{
		// dummy 
		_head = new Node(0);
		_tail = new Node(0);
		_head->next = _tail;
		_tail->prev = _head;
	}

	~List()
	{
		Node* node = _head;
		while (node)
		{
			/*
			옮겨다니는 cursor 역할
			Node* nextNode = node->next;
			node = nextNode;
			*/
			Node* deleteNode = node;
			node = node->next;
			delete deleteNode;
		}
	}
	
	// no dummy ver.
	// [head]		[tail]
	Node* AddAtHead(int data)
	{
		Node* node = new Node(data);
		
		if (_head == nullptr)
		{
			_head = node;
			_tail = node;
		}
		else
		{
			Node* nextNode = _head;
			node->next = nextNode;
			nextNode->prev = node;
			_head = node;
		}
	}

	//		[node]
	// [dummy]<->[nextNode]<->[2]<->[3]<->[dummy]
	// [head]						      [tail]
	Node* AddAtHead_dummy(int data)
	{
		Node* node = new Node(data);
		Node* nextNode = _head->next;

		node->next = nextNode;
		nextNode->prev = node;
		_head->next = node;
		node->prev = _head;
	}

private:
	Node* _head = nullptr;
	Node* _tail = nullptr;
};

