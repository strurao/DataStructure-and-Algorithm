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
		// TODO: 이동
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

	// 목적지
	Pos dest = _board->GetExitPos();

	/*for (int i = 0; i < 20; i++)
	{
		pos += Pos(1, 0);
		_path.push_back(pos);
	}*/

	_dir; // 내가 바라보는 방향
	pos; // 현재 좌표
	// 내가 바라보는 방향 기준 앞에 있는 좌표?
	Pos front[4] =
	{
		Pos(-1,0), //UP
		Pos(0,-1), //LEFT
		Pos(1,0), // DOWN
		Pos(0,1) // RIGHT
	};
	Pos next = pos + front[_dir];

	// 오른쪽 방향 90도 회전
	_dir = (_dir - 1) % DIR_COUNT;
	// 왼쪽 방향 90도 회전
	_dir = (_dir + 1) % DIR_COUNT;

	// 우수법으로 목적지를 찾을 때까지 
	while (pos != dest)
	{
		/*
		// 1. 현재 바라보는 방향을 기준으로, 오른쪽으로 갈 수 있는지 확인.
		int32 newDir;
		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전

			// 앞으로 한 보 전진

			// 좌표 기록
			_path.push_back(pos);
		}

		
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if ()
		{
			// 앞으로 한 보 전진

			// 좌표
			_path.push_back(pos);
		}

		else 
		{
			// 왼쪽 방향으로 90도 회전
		}
		*/
	}
}

void Player::CalculatePath_BFS()
{
	Pos pos = _pos;
	Pos dest = _board->GetExitPos(); // 목적지

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(+1, 0), // DOWN
		Pos(0, +1), // RIGHT
	};

	const int32 size = _board->GetSize();

	// discovered[y][x] 로 갈 수 있는가?
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// extra : parent[y][x] 는 Pos 에 의해 발견됨
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	// BFS 는 예약시스템. 선입선출 '큐'를 사용한다
	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos.y][pos.x] = pos; // 시작점은 나에게 발견된다

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();
		
		// 예외처리) 목적지 도착
		if (pos == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;
			// 이미 다른 경로에 의해 발견한 지역인지 확인
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos.y][nextPos.x] = pos; // 이 좌표는 pos 에 의해 발견되었다
		}
	}

	_path.clear();
	pos = dest; // 마지막 지점에 도달한 상태일 것. 한칸씩 뒤로 가며 어떻게 왔는지를 추적 후 저장

	while (true) {
		_path.push_back(pos);

		// 시작점
		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x]; // 뒤칸으로 계속 이동
	}

	// std::reverse(_path.begin(), _path.end());
	vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
	{
		temp[i] = _path[_path.size() - 1 - i];
	}
	_path = temp;
}