#include <iostream>
using namespace std;
#include <queue>
#include <vector>

// BFS : ���� ã�� ������ : Queue
// Dijikstra : �켱������ ���� ������ : PriorityQueue

struct Vertex
{
	// int data;
};

vector<Vertex> vertices_dijikstra;
vector<vector<int>> adjacent_dijikstra;

void CreateGraph_Dijikstr()
{
	vertices_dijikstra.resize(6);
	adjacent_dijikstra = vector<vector<int>>(6, vector<int>(6, -1));
	adjacent_dijikstra[0][1] = adjacent_dijikstra[1][0] = 15; // ����ġ 15�� ����� ����
	adjacent_dijikstra[0][3] = adjacent_dijikstra[3][0] = 35;
	adjacent_dijikstra[1][2] = adjacent_dijikstra[2][1] = +5;
	adjacent_dijikstra[1][3] = adjacent_dijikstra[3][1] = 10;
	adjacent_dijikstra[3][4] = adjacent_dijikstra[4][3] = +5;
	adjacent_dijikstra[5][4] = adjacent_dijikstra[4][5] = +5;
}

struct VertexCost
{
	VertexCost(int cost, int vertex) : cost(cost), vertex(vertex) { }

	/* greater / �� ���� �� ���� ������ �������� */
	bool operator<(const VertexCost& other) const
	{
		return cost < other.cost;
	}

	/* less / �������� / std::priority_queue �� default */
	bool operator>(const VertexCost& other) const
	{
		return cost > other.cost;
	}

	int cost; // ����ġ��� ����� BFS �� ���� ���� Dijikstra �̴�~
	int vertex;
};

void Dijikstra(int here)
{
	priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> pq; // ����� ���� ������� �����ϵ��� ����

	vector<int> best(6, INT32_MAX); // ���������� �� ������������ ����Ʈ ���̽� (�ִܰŸ�)

	vector<int> parent(6, -1); // ���ͽ�Ʈ�󿡼� �ʿ��ϴٱ⺸�ٴ� ��� �������� ����

	pq.push(VertexCost(0, here)); // 0�� cost�� here

	best[here] = 0; // �������� �̵� cost�� 0
	parent[here] = here; // ������ ����

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		VertexCost v = pq.top();
		pq.pop();

		int cost = v.cost;
		here = v.vertex;

		// ���� ������ cost���� �ٸ� �ְ� �� ����(ª��) ��θ� ã�Ҿ��ٸ� ���� ���(skip)
		if (best[here] < cost)
			continue;

		// ������� �Դٸ� ��Ƴ��� ��. ������ �ڴʰԶ� ��ġ������� ���� �� �ִ�. �湮 ����!
		// if (best[here] >= cost)
		cout << "Dijikstra �湮 : " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			// ������� �ʾ����� ��ŵ
			if (adjacent_dijikstra[here][there] == -1)
				continue;

			// �� ���� ��θ� ���ſ� ã������ ��ŵ
			// there ���� �̵��ϴµ� �ҿ�Ǵ� ��� : nextCost
			int nextCost = best[here] + adjacent_dijikstra[here][there]; // 15 + 10
			if (nextCost >= best[there])
				continue;

			// ���ݱ��� ã�� ��� �߿����� �ּ��� ��ġ = ����
			// if ( nextCost < best[there] )
			best[there] = nextCost;
			parent[there] = here; // ���߿��� �� ���� ��찡 �ִٸ� ���ŵ� �� ���� // 35 -> 15+10
			pq.push(VertexCost(nextCost, there)); // ���� ���� ������ �켱���� ť. �ּڰ��� �������ش�.
		}
	}
}

/*
int main()
{
	CreateGraph_Dijikstr();
	Dijikstra(0);
}
*/
/*
BFS, ���ͽ�Ʈ��� �������� ������ ����.
*/