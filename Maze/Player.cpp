#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	
	// CalculatePath();
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

void Player::CalculatePath()
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