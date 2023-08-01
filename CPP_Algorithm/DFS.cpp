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

// ���� �湮�� ���
// ���� ������ �湮�ߴ����� ��� �����ؾ� �Ѵ�. �� �κ��� Ʈ������ ū ������.
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);

	// ���� ����Ʈ
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };
	
	// ���� ���
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
	// �湮 ����
	visited[here] = true;
	cout << "DFS Visited : " << here << endl;

	// ��������Ʈ
	// ������ ���� �� üũ�ؼ�
	// �ð����⵵ O(V+E)
	/*
	int size = adjacent[here].size();
	for (int i = 0; i < size; i++)
	{
		int there = adjacent[here][i]; // ����Ǿ��ִٴ� ����� �̹� �湮�ߴ��������� ������ �ȵ�.
		if (visited[there] == false)
		{
			Dfs(there); // ����Լ�
		}
	}
	*/

	// �������
	// there �� �׻� 0������ �ִٰ� �����Ѵ�
	// �ð����⵵ O(V^2)
	for (int there = 0; there < 6; there++)
	{
		// ���� �ִ���
		if (adjacent2[here][there] == 0)
			continue;

		// ���� �湮���� ���� ���� ���ؼ� �湮
		if (visited[there] == false)
			Dfs(there);
	}
}

/* 
������ �� ��带 ã�Ƽ� �湮�ϰڴ�.
��� ��带 ��ȸ�ϰڴ�!
������� �ʾҴٴ� ������ �����Ǵ� ��尡 ����.
*/
void DfsAll()
{
	visited = vector<bool>(6, false);
	
	for (int i = 0; i < 6; i++)
		if (visited[i] == false)
			Dfs(i);
}

int main()
{
	CreateGraph();

	DfsAll();
}