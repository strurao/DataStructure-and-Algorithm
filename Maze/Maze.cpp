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

	while (true)
	{
		// 입력

		// 로직

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

