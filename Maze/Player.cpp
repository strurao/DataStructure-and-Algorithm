#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	
	// CalculatePath_RightHand();
	CalculatePath_BFS();
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