#include <iostream>
using namespace std;
#include <vector>
#include <queue>

////////////////////////////////////////////////
////////////////// 트리 ////////////////////////
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
	Node* root = new Node("R1 개발실");
	{
		Node* node = new Node("디자인");
		root->children.push_back(node);
		{
			Node* leaf = new Node("전투");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("경제");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("스토리");
			node->children.push_back(leaf);
		}
	}
	{
		Node* node = new Node("프로그래밍");
		root->children.push_back(node);
		{
			Node* leaf = new Node("클라");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("서버");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("엔진");
			node->children.push_back(leaf);
		}
	}
	{
		Node* node = new Node("아트");
		root->children.push_back(node);
		{
			Node* leaf = new Node("배경");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("캐릭터");
			node->children.push_back(leaf);
		}
	}
	return root;
}

// 깊이(depth) : 루트에서 어떤 노드에 도달하기 위해 거쳐야 하는 간선의 개수
void PrintTree(Node* root, int depth = 0)
{
	for (int i = 0; i < depth; i++)
		cout << "-";

	cout << root->data << endl;

	int size = root->children.size();
	for (int i = 0; i < size; i++) // 간접적인 기저사항 : 리프의 size는 0 이므로 알아서 종료된다.
	{
		Node* node = root->children[i];
		PrintTree(node, depth + 1); 
	}
}

// 높이
int GetHeight(Node* root)
{
	int ret = 1;

	int size = root->children.size();
	for (int i = 0; i < size; i++)
	{
		Node* node = root->children[i];
		int h = GetHeight(node) + 1; // 루트를 포함하기 위해 +1 을 해준다.

		if (ret < h)
			ret = h;
	}
	return ret;
}

////////////////////////////////////////////////
/////////////// 우선순위 큐 /////////////////////
////////////////////////////////////////////////

template<typename T>
class PriorityQueue
{
public:
	// O(logN) 트리 높이에 의존적이므로
	void push(const T& data)
	{
		// 우선 힙 구조부터 맞춰준다
		_heap.push_back)back(data);

		// 도장깨기 시작
		int now = static_cast<int>(_haep.size()) - 1;

		// 루트 노드까지
		while (now > 0)
		{
			// 부모 노드와 비교해서 더 작으면 패배
			int next = (now - 1) / 2; 

			if (_heap[now] < _heap[next])
				break;

			// 데이터 교체
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(logN) 재배치 과정 또한 트리의 높이에 의존적이므로
	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;

		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// 예외처리 : 리프에 도달한 경우 
			if (left >= (int)_heap.size())
				break;

			int next = now;

			// 왼쪽 비교
			if (_heap[next] < _heap[left])
				next = left;

			// 둘 중 승자를 오른쪽과 비교
			if (right < _heap.size() && _heap[next] < _heap[right])
				next = right;

			// 왼쪽/오른쪽 둘 다 현재 값보다 작으면 종료
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
	트리
	Node* root = CreateTree();
	PrintTree(root);
	int h = GetHeight(root);
	cout << "h: " << h << endl;
	*/ 
	
	/*
	우선순위 큐
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