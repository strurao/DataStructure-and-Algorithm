#include <iostream>
using namespace std; 
#include <queue>
#include <vector>

struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<vector<int>> adjacent2;

// 내가 방문한 목록
// 내가 어디까지 방문했는지를 계속 추적해야 한다. 이 부분이 트리와의 큰 차이점.
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);

	// 인접 리스트
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };
	
	// 인접 행렬
	adjacent2 = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 }
	};

}

void Dfs(int here)
{
	// 방문 도장
	visited[here] = true;
	cout << "DFS Visited : " << here << endl;

	// 인접리스트
	// 인접한 길을 다 체크해서
	// 시간복잡도 O(V+E)
	/*
	int size = adjacent[here].size();
	for (int i = 0; i < size; i++)
	{
		int there = adjacent[here][i]; // 연결되어있다는 사실이 이미 방문했는지까지는 포함이 안됨.
		if (visited[there] == false)
		{
			Dfs(there); // 재귀함수
		}
	}
	*/

	// 인접행렬
	// there 는 항상 0번부터 있다고 가정한다
	// 시간복잡도 O(V^2)
	for (int there = 0; there < 6; there++)
	{
		// 길은 있는지
		if (adjacent2[here][there] == 0)
			continue;

		// 아직 방문하지 않은 곳에 한해서 방문
		if (visited[there] == false)
			Dfs(there);
	}
}

/* 
누락이 된 노드를 찾아서 방문하겠다.
모든 노드를 순회하겠다!
연결되지 않았다는 이유로 누락되는 노드가 없다.
*/
void DfsAll()
{
	visited = vector<bool>(6, false);
	
	for (int i = 0; i < 6; i++)
		if (visited[i] == false)
			Dfs(i);
}

/*
int main()
{
	CreateGraph();

	DfsAll();
}
*/

/*
C++에서 깊이 우선 탐색(Depth-First Search, DFS)을 구현할 때 인접 행렬과 인접 리스트를 사용할 수 있습니다. 
이 경우, 모든 정점의 쌍에 대해 간선의 존재 여부를 확인해야하므로 시간 복잡도는 다음과 같습니다. 

인접리스트:
인접 리스트로 구현했을 때의 시간복잡도는 O(V+E)입니다. 
여기서 V는 정점의 수고, E는 간선의 수입니다. 
인접 리스트는 각 정점을 연결하는 간선에만 구성되어 있으므로 실제 간선의 수에만 영향을 받는 복잡성이 발생합니다. 

인접행렬:
인접 행렬로 구현했을 때의 시간복잡도는 O(V^2)입니다. 
인접 행렬에서는 각 정점에서 모든 다른 정점으로의 연결 여부를 저장하므로 정점의 수 V에 대해 제곱의 복잡성이 발생합니다.

즉 이런 이유로 인접리스트는 희소 그래프(Sparse Graphs)에 더 적합하고, 
인접행렬은 밀집 그래프(Dense Graphs)에 더 적합합니다. 
이는 인접리스트는 간선의 수에 따라 복잡도에 영향을 받으나, 
인접행렬은 그래프의 복잡도에 상관없이 정점의 수에 관계된 복잡성이 발생하기 때문입니다.
*/