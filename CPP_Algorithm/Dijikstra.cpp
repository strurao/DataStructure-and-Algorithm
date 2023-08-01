#include <iostream>
using namespace std;
#include <queue>
#include <vector>

// BFS : 먼저 찾은 노드부터 : Queue
// Dijikstra : 우선순위가 높은 노드부터 : PriorityQueue

struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent_dijikstra;

void CreateGraph_Dijikstr()
{
	vertices.resize(6);
	adjacent_dijikstra = vector<vector<int>>(6, vector<int>(6, -1));
	adjacent_dijikstra[0][1] = adjacent_dijikstra[1][0] = 15; // 양방향
	adjacent_dijikstra[0][3] = adjacent_dijikstra[3][0] = 35;
	adjacent_dijikstra[1][2] = adjacent_dijikstra[2][1] = +5;
	adjacent_dijikstra[1][3] = adjacent_dijikstra[3][1] = 10;
	adjacent_dijikstra[3][4] = adjacent_dijikstra[4][3] = +5;
	adjacent_dijikstra[5][4] = adjacent_dijikstra[4][5] = +5;
}

struct VertexCost
{
	VertexCost(int cost, int vertex) : cost(cost), vertex(vertex) { }

	/* greater / 더 작은 수 부터 나오는 오름차순 */
	bool operator<(const VertexCost& other) const
	{
		return cost < other.cost;
	}

	/* less / 내림차순 / std::priority_queue 의 default */
	bool operator>(const VertexCost& other) const
	{
		return cost > other.cost;
	}

	int cost; // 가중치라는 양념을 BFS 에 더한 것이 Dijikstra 이다~
	int vertex;
};

void Dijikstra(int here)
{
	priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> pq;

	vector<int> best(6, INT32_MAX); // 시작점에서 각 정점별까지의 베스트 케이스 (최단거리)

	vector<int> parent(6, -1); // 다익스트라에서 필요하다기보다는 경로 역추적을 위해

	pq.push(VertexCost(0, here)); // 0번 cost로 here

	best[here] = 0; // 시작점의 이동 cost는 0
	parent[here] = here; // 시작점 설정

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		VertexCost v = pq.top();
		pq.pop();

		int cost = v.cost;
		here = v.vertex;

		// 더 좋은(짧은) 경로를 뒤늦게 찾았다면 skip
		if (best[here] < cost)
			continue;

		// 방문
		cout << "Dijikstra 방문 : " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵
			if (adjacent_dijikstra[here][there] == -1)
				continue;

			// 더 좋은 경로를 과거에 찾았으면 스킵
			int nextCost = best[here] + adjacent_dijikstra[here][there];
			if (nextCost >= best[there])
				continue;

			// 지금까지 찾은 경로 중에서느 최선의 수치 = 갱신
			best[there] = nextCost;
			parent[there] = here; // 나중에 갱신될 수 있음
			pq.push(VertexCost(nextCost, there));
		}
	}
}

int main()
{
	CreateGraph_Dijikstr();
	Dijikstra(0);
}

/*
BFS, 다익스트라는 목적지의 개념이 없다.
*/