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

// �߰���
vector<bool> discovered;

void CreateGraph_bfs()
{
	vertices_bfs.resize(6);

	// ���� ����Ʈ
	adjacent_bfs = vector<vector<int>>(6);
	adjacent_bfs[0] = { 1, 3 };
	adjacent_bfs[1] = { 0, 2, 3 };
	adjacent_bfs[3] = { 4 };
	adjacent_bfs[5] = { 4 };
	
	// ���� ���
	/*
	adjacent_bfs = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 }
	};
	*/
}

/*
�߰��� ������� �����ϰڴ� -> ���Լ��� ť
*/
void Bfs(int here) // ù ȣ�� �� here �� �������� ����
{
	queue<int> q;
	q.push(here);
	discovered[here] = true;
	
	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		// �湮 ����
		cout << "BFS Visited : " << here << endl;

		int size = adjacent_bfs[here].size();
		for (int i = 0; i < size; i++)
		{
			int there = adjacent_bfs[here][i];
			if (discovered[there])
				continue;
		
			q.push(there);
			discovered[there] = true;
		}
	}
}

int main()
{
	CreateGraph_bfs();
	discovered = vector<bool>(6, false);
	Bfs(0);
}

