#include "pch.h"
#include <iostream>
#include "List.h"
#include "Vector.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
	::srand(static_cast<uint32>(time(nullptr))); // 랜덤 seed 값 설정

	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;

	while (true)
	{
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;

		// 입력

		// 로직
		player.Update(deltaTick);

		// 렌더링
		board.Render();
	}

	/*
	양방향 연결리스트
	List list;

	list.AddAtTail(1);
	Node* node = list.AddAtTail(2);
	// 이렇게 특정 노드의 위치를 기억할 때 중간 삽입,삭제가 빠르다고 할 수 있다.
	list.AddAtTail(3);
	list.Print();

	list.Remove(node);
	list.Print();
	*/

}

