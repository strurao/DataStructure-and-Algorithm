#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	
	// CalculatePath_RightHand();
	CalculatePath_AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;

	if (_sumTick >= Player::MOVE_TICK)
	{
		_sumTick = 0;
		// TODO: �̵�
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTyileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::CalculatePath_RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// ������
	Pos dest = _board->GetExitPos();

	/*for (int i = 0; i < 20; i++)
	{
		pos += Pos(1, 0);
		_path.push_back(pos);
	}*/

	_dir; // ���� �ٶ󺸴� ����
	pos; // ���� ��ǥ
	// ���� �ٶ󺸴� ���� ���� �տ� �ִ� ��ǥ?
	Pos front[4] =
	{
		Pos(-1,0), //UP
		Pos(0,-1), //LEFT
		Pos(1,0), // DOWN
		Pos(0,1) // RIGHT
	};
	Pos next = pos + front[_dir];

	// ������ ���� 90�� ȸ��
	_dir = (_dir - 1) % DIR_COUNT;
	// ���� ���� 90�� ȸ��
	_dir = (_dir + 1) % DIR_COUNT;

	// ��������� �������� ã�� ������ 
	while (pos != dest)
	{
		/*
		// 1. ���� �ٶ󺸴� ������ ��������, ���������� �� �� �ִ��� Ȯ��.
		int32 newDir;
		if (CanGo(pos + front[newDir]))
		{
			// ������ �������� 90�� ȸ��

			// ������ �� �� ����

			// ��ǥ ���
			_path.push_back(pos);
		}

		
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if ()
		{
			// ������ �� �� ����

			// ��ǥ
			_path.push_back(pos);
		}

		else 
		{
			// ���� �������� 90�� ȸ��
		}
		*/
	}
}

void Player::CalculatePath_BFS()
{
	Pos pos = _pos;
	Pos dest = _board->GetExitPos(); // ������

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(+1, 0), // DOWN
		Pos(0, +1), // RIGHT
	};

	const int32 size = _board->GetSize();

	// discovered[y][x] �� �� �� �ִ°�?
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// extra : parent[y][x] �� Pos �� ���� �߰ߵ�
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	// BFS �� ����ý���. ���Լ��� 'ť'�� ����Ѵ�
	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos.y][pos.x] = pos; // �������� ������ �߰ߵȴ�

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();
		
		// ����ó��) ������ ����
		if (pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = pos + front[dir];
			// �� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
				continue;
			// �̹� �ٸ� ��ο� ���� �߰��� �������� Ȯ��
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos.y][nextPos.x] = pos; // �� ��ǥ�� pos �� ���� �߰ߵǾ���
		}
	}

	_path.clear();
	pos = dest; // ������ ������ ������ ������ ��. ��ĭ�� �ڷ� ���� ��� �Դ����� ���� �� ����

	while (true) {
		_path.push_back(pos);

		// ������
		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x]; // ��ĭ���� ��� �̵�
	}

	// std::reverse(_path.begin(), _path.end());
	vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
	{
		temp[i] = _path[_path.size() - 1 - i];
	}
	_path = temp;
}

/*
BFS, ���ͽ�Ʈ��� �������� ������ ����

ä��
- �Ա��������� �󸶳� ������ �ִ���?
- �ⱸ�������� �󸶳� ������ �ִ���?
	F = G + H
	F = ���� ���� (���� ���� ����)
	G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (cost)
	H = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���
*/

struct PQNode
{
	PQNode(int32 f, int32 g, Pos pos) : f(f), g(g), pos(pos) { }
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int32 f; // f = g + h
	int32 g;
	Pos pos;
};

void Player::CalculatePath_AStar()
{
	Pos start = _pos; // ���� �� ��ġ
	Pos dest = _board->GetExitPos(); // ������. �ܼ��� ������ �뵵�θ� ������� ����.

	Pos front[] =
	{
		Pos(-1,0), // UP
		Pos(0,-1), // LEFT
		Pos(+1,0), // DOWN
		Pos(0,+1),  // RIGHT

		Pos(-1, -1), // UP_LEFT
		Pos(+1, -1), // DOWN_LEFT
		Pos(+1, +1), // DOWN_RIGHT
		Pos(-1, 1), // UP_RIGHT
	};

	int32 cost[] =
	{
		10, // UP
		10, // LEFT
		10, // DOWN
		10, // RIGHT
		14, // �밢��
		14,
		14,
		14
	};

	const int32 size = _board->GetSize(); // ���� ������

	// best[y][x] -> ���ݱ��� (y,x) �� ���� ���� ���� ��� (���� ���� ����)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// ClosedList -> closed[y][x] -> (y,x) �� �湮�� �ߴ��� ����
	// �߰��� �켱���� ť�� �ִ� ��, �湮�� ���� ��� �����Ǿ� �湮�� ��.
	// Option) ��� best �θ� �Ǻ� ����
	vector<vector<bool>> closed(size, vector<bool>(size, false)); // � ��ǥ�� �湮���� ���´���?

	// �θ� ���� �뵵
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	// 1) ���� �ý��� ����
	// 2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� �� ���� -> �� ���� ó�� ���ٰ�

	// OpenList : ���ݱ��� �߰ߵ� ���
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// �ʱⰪ ���� (���� ��ġ)
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		PQNode node = pq.top();
		pq.pop();

		// ������ ��ǥ�� ���� ��η� ã�Ƽ� �� ���� ��η� ���ؼ� �̹� �湮(closed)�� ��� skip
		if (closed[node.pos.y][node.pos.x])
			continue;
		// �ⲯ ����ߴ��ϸ� ������ �� ����� �ĺ��� �ִ�?
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// �湮
		closed[node.pos.y][node.pos.x] = true;

		// �������� ���������� �ٷ� ����
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// �� �� �ִ� ������ �´��� Ȯ��. �� ������ �ִ���?
			if (CanGo(nextPos) == false)
				continue;
			if (closed[nextPos.y][nextPos.x])
				continue;

			// ���� ��ǥ���� �����ϴ� ��� ���. �̰��� �ִܰŸ��ΰ�? �� ���� �׼�
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			// �ٸ� ��ο��� �� ���� ���� ã�Ҵٸ� skip
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// ���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode(g + h, g, nextPos));
			parent[nextPos.y][nextPos.x] = node.pos;
		}
	}

	_path.clear();
	Pos pos = dest;

	while (true)
	{
		_path.push_back(pos);

		// ������
		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x];
	}
	std::reverse(_path.begin(), _path.end());
}