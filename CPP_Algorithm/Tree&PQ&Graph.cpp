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

template<typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:
	// O(logN) Ʈ�� ���̿� �������̹Ƿ�
	void push(const T& data)
	{
		// �켱 �� �������� �����ش�
		_heap.push_back(data);

		// ������� ����
		int now = static_cast<int>(_heap.size()) - 1;

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

////////////////////////////////////////////////
///////////////// �׷��� ///////////////////////
////////////////////////////////////////////////

// ������������ �� ������ �ʴ� ����̴�
void CreateGraph_1()
{
	struct Vertex
	{
		// int data;
		vector<Vertex*> edges; // ����
	};

	vector<Vertex> v;
	v.resize(6); // size
	// v.reserve(6); // capacity

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// Q) 0->3 ����Ǿ��ֳ���?
	bool connected = false;

	int size = v[0].edges.size();
	for (int i = 0; i < size; i++)
	{
		Vertex* vertex = v[0].edges[i];
		if (vertex == &v[3])
		{
			connected = true;
		}
	}
}

// ���� ����Ʈ : ���� ����� ����'��' �־��ش�
// �����ߴٴ� ���� �� ����Ǿ��ִٴ� �ǹ��̴�
// ����ö �뼱��ó�� ���� �幮 �幮 ����Ǿ����� �� �����ϴ�
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6); // ������ ���⼭ �����ϰ�

	vector<vector<int>> adjacent; // ���� ���δ� ���� ���Ϳ��� �����Ѵ�
	adjacent.resize(6);

	// adjacent[0].push_back(1);
	// adjacent[0].push_back(3);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// Q) 0->3 ����Ǿ��ֳ���?
	bool connected = false;

	int size = adjacent[0].size();
	for (int i = 0; i < size; i++)
	{
		int vertex = adjacent[0][i];
		if (vertex == 3)
		{
			connected = true;
		}
	}
}

// ���� ��� 
// ���̽���ó�� ���� �����ϰ� ����Ǿ� �ִ� ��쿡 �����ϴ�
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	// ����� ����� ��ķ� ���� (2���� ǥó��)
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// adjacent[from][to] ?
	// ����� �̿��� �׷��� ǥ��
	// �޸� �Ҹ� ��������, ���� ����
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// Q) 0->3 ����Ǿ��ֳ���?
	bool connected = adjacent[0][3];

	// bool ��� int�� �����Ѵٸ�?
	vector<vector<int>> adjacent2 =
	{
		{-1, 15, -1, 35, -1, -1},
		{15, -1, +5, 10, -1, -1},
		{-1, +5, -1, -1, -1, -1},
		{-1, -1, -1, +5, -1, +5},
		{-1, -1, -1, -1, +5, -1},
	};
}


//int main()
//{
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

	/*
	�ᱹ �츮�� ��ȸ�� �ؾ� �Ѵ� 
	�׷��� ��ȸ�� ��� �ؾ��ұ�? Ʈ���� ���, ���ʹ� �� ����Ž���ϸ� �ȴ�.
	�׷����� Ʈ��ó�� ���������� �����Ƿ� ����Ŭ�� �Ͼ �� �ִ�. 
	��Ģ�� �ʿ��ϴ�.
	�׷��� DFS, BFS �� �ʿ伺�� ��εȴ�.
	*/
//}
