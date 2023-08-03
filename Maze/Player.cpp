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

/*
BFS, 다익스트라는 목적지의 개념이 없다

채점
- 입구에서부터 얼마나 떨어져 있는지?
- 출구에서부터 얼마나 떨어져 있는지?
	F = G + H
	F = 최종 점수 (작을 수록 좋음)
	G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (cost)
	H = 목적지에서 해당 좌표까지 이동하는데 드는 비용
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
	Pos start = _pos; // 현재 내 위치
	Pos dest = _board->GetExitPos(); // 목적지. 단순히 나가는 용도로만 사용하지 않음.

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
		14, // 대각선
		14,
		14,
		14
	};

	const int32 size = _board->GetSize(); // 맵의 사이즈

	// best[y][x] -> 지금까지 (y,x) 에 대한 가장 좋은 비용 (작을 수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// ClosedList -> closed[y][x] -> (y,x) 에 방문을 했는지 여부
	// 발견은 우선순위 큐에 넣는 것, 방문은 정말 우수 판정되어 방문한 것.
	// Option) 사실 best 로만 판별 가능
	vector<vector<bool>> closed(size, vector<bool>(size, false)); // 어떤 좌표가 방문까지 끝냈는지?

	// 부모 추적 용도
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	// 1) 예약 시스템 구현
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 꼭 예외 처리 해줄것

	// OpenList : 지금까지 발견된 목록
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 초기값 설정 (시작 위치)
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서 더 빠른 경로로 인해서 이미 방문(closed)된 경우 skip
		if (closed[node.pos.y][node.pos.x])
			continue;
		// 기껏 등록했더니만 나보다 더 우수한 후보가 있다?
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착했으면 바로 종료
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// 갈 수 있는 지역은 맞는지 확인. 즉 간선이 있는지?
			if (CanGo(nextPos) == false)
				continue;
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 다음 좌표까지 가야하는 비용 계산. 이것이 최단거리인가? 에 따라 액션
			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			// 다른 경로에서 더 빠른 길을 찾았다면 skip
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약 진행
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

		// 시작점
		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x];
	}
	std::reverse(_path.begin(), _path.end());
}