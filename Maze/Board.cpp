#include "pch.h"
#include "Board.h"
#include "Player.h"

const char* TILE = "��";

Board::Board() {}

Board::~Board() {}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;
	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{
			ConsoleColor color = GetTileColor(Pos(y, x));
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}

		cout << endl;
	}
}

// Binary Tree �̷� ���� �˰�����
// - Mazes For Programmers
void Board::GenerateMap()
{
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	// �������� ���� Ȥ�� �Ʒ��� ���� �մ� �۾�
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			// WALL �̶�� skip 
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// ��ǥ ����
			if (y == _size - 2 && x == _size - 2)
				continue;

			// �ϴ� ����: �������� �ձ�
			if (y == _size - 2)
			{
				_tile[y][x + 1] = TileType::EMPTY;
				continue;
			}

			// ������ ����: �ϴ����� �ձ�
			if (x == _size - 2)
			{
				_tile[y + 1][x] = TileType::EMPTY;
				continue;
			}

			// ��������
			const int32 randValue = ::rand() % 2;
			if (randValue == 0)
				_tile[y][x + 1] = TileType::EMPTY;
			else
				_tile[y + 1][x] = TileType::EMPTY;
		}
	}
}

TileType Board::GetTyileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= _size)
		return TileType::NONE;
	if (pos.y < 0 || pos.y >= _size)
		return TileType::NONE;

	return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::PURPLE;

	if (GetExitPos() == pos) // Ż�ⱸ 
		return ConsoleColor::RED;

	TileType tileType = GetTyileType(pos);
	switch(tileType)
	{
		// �� �� �ִ� ����
		case TileType::EMPTY:
			return ConsoleColor::WHITE;
		// �����ִ� ��
		case TileType::WALL:
			return ConsoleColor::SKYBLUE;
	}

	return ConsoleColor::SKYBLUE; 
}