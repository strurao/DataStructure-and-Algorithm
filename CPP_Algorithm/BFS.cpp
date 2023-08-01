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

	// ��������Ʈ ver
	/*
	adjacent_bfs = vector<vector<int>>(6);
	adjacent_bfs[0] = { 1, 3 };
	adjacent_bfs[1] = { 0, 2, 3 };
	adjacent_bfs[3] = { 4 };
	adjacent_bfs[5] = { 4 };
	*/

	// ������� ver
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
�߰��� ������� �����ϰڴ� -> ���Լ��� ť
*/
void Bfs(int here) // ù ȣ�� �� here �� �������� ����
{
	// ex) ������ ���ؼ� �߰ߵǾ�����?
	vector<int> parent(6, -1);
	// ex) ���������� ��ŭ ������ �ִ���? (�ʺ� �󸶳� �Ǵ���?)
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

		// �湮 ����
		cout << "BFS Visited : " << here << endl;

		// ��������Ʈ ver
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

		// ������� ver
		for (int there = 0; there < 6; there++)
		{
			if (adjacent_bfs2[here][there] == 0)
				continue;
			if (discovered[there])
				continue;

			q.push(there);
			discovered[there] = true;
			// ������ �԰� ���ÿ�
			parent[there] = here;
			dist[there] = dist[here] + 1;
		}
	}
}

/*
������ �� ��带 ã�Ƽ� �湮�ϰڴ�.
��� ��带 ��ȸ�ϰڴ�!
������� �ʾҴٴ� ������ �����Ǵ� ��尡 ����.
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
