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

void Bfs(int here) // ù ȣ�� �� here �� �������� ����
{

}

int main()
{

}

