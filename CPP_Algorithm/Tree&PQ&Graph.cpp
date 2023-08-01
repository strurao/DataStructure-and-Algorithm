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

template<typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:
	// O(logN) 트리 높이에 의존적이므로
	void push(const T& data)
	{
		// 우선 힙 구조부터 맞춰준다
		_heap.push_back(data);

		// 도장깨기 시작
		int now = static_cast<int>(_heap.size()) - 1;

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

////////////////////////////////////////////////
///////////////// 그래프 ///////////////////////
////////////////////////////////////////////////

// 직관적이지만 잘 사용되지 않는 방식이다
void CreateGraph_1()
{
	struct Vertex
	{
		// int data;
		vector<Vertex*> edges; // 간선
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

	// Q) 0->3 연결되어있나요?
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

// 인접 리스트 : 실제 연결된 노드들'만' 넣어준다
// 인접했다는 것은 곧 연결되어있다는 의미이다
// 지하철 노선도처럼 서로 드문 드문 연결되어있을 때 적절하다
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6); // 정점은 여기서 관리하고

	vector<vector<int>> adjacent; // 연결 여부는 이중 벡터에서 관리한다
	adjacent.resize(6);

	// adjacent[0].push_back(1);
	// adjacent[0].push_back(3);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// Q) 0->3 연결되어있나요?
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

// 인접 행렬 
// 페이스북처럼 서로 빽빽하게 연결되어 있는 경우에 적절하다
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	// 연결된 목록을 행렬로 관리 (2차원 표처럼)
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// adjacent[from][to] ?
	// 행렬을 이용한 그래프 표현
	// 메모리 소모 심하지만, 빠른 접근
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// Q) 0->3 연결되어있나요?
	bool connected = adjacent[0][3];

	// bool 대신 int로 구현한다면?
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

	/*
	결국 우리는 순회를 해야 한다 
	그래프 순회는 어떻게 해야할까? 트리는 재귀, 벡터는 쭉 선형탐색하면 된다.
	그래프는 트리처럼 계층적이지 않으므로 싸이클이 일어날 수 있다. 
	규칙이 필요하다.
	그래서 DFS, BFS 의 필요성이 대두된다.
	*/
//}
