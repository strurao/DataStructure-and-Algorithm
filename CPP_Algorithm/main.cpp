#include <iostream>
using namespace std;
#include <vector>
#include <queue>

////////////////////////////////////////////////
////////////////// Ʈ�� ////////////////////////
////////////////////////////////////////////////

class Node
{
public:
	Node(const char* data):data(data){}

public:
	const char* data;
	vector<Node*> children;
};

Node* CreateTree()
{
	Node* root = new Node("R1 ���߽�");
	{
		Node* node = new Node("������");
		root->children.push_back(node);
		{
			Node* leaf = new Node("����");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("����");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("���丮");
			node->children.push_back(leaf);
		}
	}
	{
		Node* node = new Node("���α׷���");
		root->children.push_back(node);
		{
			Node* leaf = new Node("Ŭ��");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("����");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("����");
			node->children.push_back(leaf);
		}
	}
	{
		Node* node = new Node("��Ʈ");
		root->children.push_back(node);
		{
			Node* leaf = new Node("���");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("ĳ����");
			node->children.push_back(leaf);
		}
	}
	return root;
}

// ����(depth) : ��Ʈ���� � ��忡 �����ϱ� ���� ���ľ� �ϴ� ������ ����
void PrintTree(Node* root, int depth = 0)
{
	for (int i = 0; i < depth; i++)
		cout << "-";

	cout << root->data << endl;

	int size = root->children.size();
	for (int i = 0; i < size; i++) // �������� �������� : ������ size�� 0 �̹Ƿ� �˾Ƽ� ����ȴ�.
	{
		Node* node = root->children[i];
		PrintTree(node, depth + 1); 
	}
}

// ����
int GetHeight(Node* root)
{
	int ret = 1;

	int size = root->children.size();
	for (int i = 0; i < size; i++)
	{
		Node* node = root->children[i];
		int h = GetHeight(node) + 1; // ��Ʈ�� �����ϱ� ���� +1 �� ���ش�.

		if (ret < h)
			ret = h;
	}
	return ret;
}

////////////////////////////////////////////////
/////////////// �켱���� ť /////////////////////
////////////////////////////////////////////////

template<typename T>
class PriorityQueue
{
public:
	// O(logN) Ʈ�� ���̿� �������̹Ƿ�
	void push(const T& data)
	{
		// �켱 �� �������� �����ش�
		_heap.push_back)back(data);

		// ������� ����
		int now = static_cast<int>(_haep.size()) - 1;

		// ��Ʈ ������
		while (now > 0)
		{
			// �θ� ���� ���ؼ� �� ������ �й�
			int next = (now - 1) / 2; 

			if (_heap[now] < _heap[next])
				break;

			// ������ ��ü
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(logN) ���ġ ���� ���� Ʈ���� ���̿� �������̹Ƿ�
	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;

		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// ����ó�� : ������ ������ ��� 
			if (left >= (int)_heap.size())
				break;

			int next = now;

			// ���� ��
			if (_heap[next] < _heap[left])
				next = left;

			// �� �� ���ڸ� �����ʰ� ��
			if (right < _heap.size() && _heap[next] < _heap[right])
				next = right;

			// ����/������ �� �� ���� ������ ������ ����
			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(1)
	T& top()
	{
		return _heap[0];
	}

	// O(1)
	bool empty()
	{
		return _heap.empty();
	}

private:
	vector<T> _heap;

};



int main()
{
	/*
	Ʈ��
	Node* root = CreateTree();
	PrintTree(root);
	int h = GetHeight(root);
	cout << "h: " << h << endl;
	*/ 
	
	/*
	�켱���� ť
	PriorityQueue<int> pq;
	pq.push(10);
	pq.push(40);
	pq.push(30);
	pq.push(50);
	pq.push(20);
	int value = pq.top();
	pq.pop();
	*/

}