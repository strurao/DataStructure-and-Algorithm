#include <iostream>
#include "List.h"

int main()
{
	{
		// 양방향 연결리스트
		List list;

		list.AddAtTail(1);
		Node* node = list.AddAtTail(2);
		// 이렇게 특정 노드의 위치를 기억할 때 중간 삽입,삭제가 빠르다고 할 수 있다.
		list.AddAtTail(3);

		list.Print();

		list.Remove(node);

		list.Print();
	}

}

