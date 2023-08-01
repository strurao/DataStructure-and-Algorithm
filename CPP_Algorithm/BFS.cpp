#include <iostream>
using namespace std;
#include <queue>
#include <vector>

struct Vertex
{

};

vector<Vertex> vertices_bfs;
vector<vector<int>> adjacent_bfs;
vector<vector<int>> adjacent_bfs2;

// 발견한
vector<bool> discovered;

void CreateGraph_bfs()
{
	vertices_bfs.resize(6);

	// 인접리스트 ver
	/*
	adjacent_bfs = vector<vector<int>>(6);
	adjacent_bfs[0] = { 1, 3 };
	adjacent_bfs[1] = { 0, 2, 3 };
	adjacent_bfs[3] = { 4 };
	adjacent_bfs[5] = { 4 };
	*/

	// 인접행렬 ver
	adjacent_bfs2 = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 }
	};
}

/*
발견한 순서대로 접근하겠다 -> 선입선출 큐
*/
void Bfs(int here) // 첫 호출 시 here 에 시작점이 들어간다
{
	// ex) 누구에 의해서 발견되었는지?
	vector<int> parent(6, -1);
	// ex) 시작점에서 얼만큼 떨어져 있는지? (너비가 얼마나 되는지?)
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;
	
	//
	parent[here] = here;
	dist[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		// 방문 도장
		cout << "BFS Visited : " << here << endl;

		// 인접리스트 ver
		/*
		int size = adjacent_bfs[here].size();
		for (int i = 0; i < size; i++)
		{
			int there = adjacent_bfs[here][i];
			if (discovered[there])
				continue;
		
			q.push(there);
			discovered[there] = true;
		}
		*/

		// 인접행렬 ver
		for (int there = 0; there < 6; there++)
		{
			if (adjacent_bfs2[here][there] == 0)
				continue;
			if (discovered[there])
				continue;

			q.push(there);
			discovered[there] = true;
			// 예약을 함과 동시에
			parent[there] = here;
			dist[there] = dist[here] + 1;
		}
	}
}

/*
누락이 된 노드를 찾아서 방문하겠다.
모든 노드를 순회하겠다!
연결되지 않았다는 이유로 누락되는 노드가 없다.
*/
void BfsAll()
{
	discovered = vector<bool>(6, false);
	for (int i = 0; i < 6; i++)
		if (discovered[i] == false)
			Bfs(i);
}

/*
int main()
{
	CreateGraph_bfs();
	BfsAll();
}
*/
