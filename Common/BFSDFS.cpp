/*
 * Created by ThaoTT9
 */

#include "BFSDFS.h"
#include <string>
#include <chrono>

namespace {
#define MAX_N 100
#define MAX_M 100
	int N = 0, M = 0;
	int matrix[MAX_N + 1][MAX_M + 1];
	int startX = 0;
	int startY = 0;
#define MAX_COST 10000
	int dx[4] = { 1, -1, 0, 0 }; // xuong, trai, phai, tren
	int dy[4] = { 0, 0, 1, -1 };


	int buff[MAX_N + 1][MAX_M + 1];

	int queue[100000][2];
	int  front, rear;
	int count = 0;
	int targetX = -1, targetY = -1;
	float minCost = MAX_COST;
	int  fruit = -1;

	bool visited[MAX_N][MAX_M];
	int direction[100000];
	int top = -1;
	int targetDirection[100000];
	int topDirection = -1;
}

int endX, endY;
void init() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			matrix[i][j] = 0;
		}
	}
}

int lengthMyElephant;

void push(int x, int y) {
	++rear;
	queue[rear][0] = x;
	queue[rear][1] = y;
}
int popX() {
	++front;
	return queue[front][0];
}
int popY() {
	return queue[front][1];
}

int point;
bool visited1[MAX_N][MAX_M];
int _queue[100000][2];
int isCheckExit(int _startX, int _startY, int _targetX, int _targetY, bool ignoreTarget) {
	int _front = -1, _rear = -1;
	int visit[MAX_N + 1][MAX_M + 1];
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			visit[i][j] = MAX_COST;
		}
	}
	++_rear;
	_queue[_rear][0] = _startX;
	_queue[_rear][1] = _startY;
	visit[_startX][_startY] = 0;
	while (_front != _rear) {
		++_front;
		int x = _queue[_front][0];
		int y = _queue[_front][1];
		for (int v = 0; v < 4; v++) {
			int tx = x + dx[v];
			int ty = y + dy[v];

			if (1 <= tx && tx <= N && 1 <= ty && ty <= M && visit[tx][ty] == MAX_COST) {
				if (matrix[tx][ty] != -1) {
					if (visit[x][y] + 1 < visit[tx][ty]) {
						visit[tx][ty] = visit[x][y] + 1;
						++_rear;
						_queue[_rear][0] = tx;
						_queue[_rear][1] = ty;
					}
					
					if (ignoreTarget && matrix[tx][ty] >= 1) {
						point = matrix[tx][ty];
						return visit[tx][ty];
					}
				}
				if (tx == _targetX && ty == _targetY) {
					return visit[x][y] + 1;
				}
			}
		}
	}
	return MAX_COST;
}

int _targetX = -1, _targetY = -1;
void BFS() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			buff[i][j] = MAX_COST;
		}
	}
	_targetX = -1;
	_targetY = -1;
	minCost = MAX_COST;
	fruit = -1;
	targetX = -1;
	targetY = -1;
    front = -1;
    rear = -1;
	push(startX, startY);
	buff[startX][startY] = 0;
	int intBreak = 5;
	int tbMin = MAX_COST;
	float tb = 0;
    
    while (front != rear && intBreak > 0) {
		int x = popX();
		int y = popY();
		for (int v = 0; v < 4; v++) {
			int tx = x + dx[v];
			int ty = y + dy[v];

			if (1 <= tx && tx <= N && 1 <= ty && ty <= M) {
				if (matrix[tx][ty] != -1 && buff[tx][ty] == MAX_COST) {
					if (buff[x][y] + 1 < buff[tx][ty]) {
						buff[tx][ty] = buff[x][y] + 1;
						push(tx, ty);
					}
				}
				if (matrix[tx][ty] != -1 && matrix[tx][ty] != 0) {
					float cost = (float)buff[tx][ty] / matrix[tx][ty];
					
					if (cost <= minCost && fruit < matrix[tx][ty]) {
						point = 0;
						int nextCost = isCheckExit(tx, ty, endX, endY, true);
						point = matrix[tx][ty] + point;
						int totalCost = buff[tx][ty] + nextCost;
						tb = (float)totalCost / point;
						//if (isCheckExit(tx, ty, endX, endY, false) != MAX_COST && tbMin > tb) {
						int costToEnd = isCheckExit(tx, ty, endX, endY, false);
						//if (true || tbMin > tb) {
						intBreak--;
						if (costToEnd != MAX_COST && tbMin > tb) {
							targetX = tx;
							targetY = ty;
							minCost = cost;
							fruit = matrix[tx][ty];
							tbMin = tb;
						}
					}

				}

			}
		}//for
	}
}

static int dfsCalledCount = 0;
void DFS(int x, int y) {
    dfsCalledCount++;
	visited[x][y] = true;
	if (x != targetX || y != targetY) {
		for (int v = 0; v < 4; v++) {
			int tx = x + dx[v];
			int ty = y + dy[v];
			if (1 <= tx && tx <= N && 1 <= ty && ty <= M && visited[tx][ty] == false && buff[tx][ty] == buff[x][y] + 1) {
				++top;
				direction[top] = v;
				DFS(tx, ty);
				--top;
			}
		}
	}
	else {
		//cout << "Den dich" << ":" << top << endl;
		topDirection = ++top;
		for (int i = 0; i < topDirection; i++) {
			targetDirection[i] = direction[i];
		}

	}
}

void initialize() {
	top = -1;
	topDirection = -1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			visited[i][j] = false;
		}
	}
//    for (int i = 0; i < 100000; i++) {
//        targetDirection[i] = -1;
//    }
    memset(targetDirection, 0xFF, 100000);
}


/*
 * Wrapper Class
 */

BFSDFS::BFSDFS() {

}

BFSDFS::~BFSDFS() {
	;
}

void BFSDFS::initMatrix(int64_t n, int64_t m)
{
	N = (int)n;
	M = (int)m;
	init();
}

void BFSDFS::updatePlayerMatrix(Message msgData)
{
    // get our elephants length
    lengthMyElephant = (int)msgData.players[msgData.ourTeamIndex].length;

    // get our elephants end
    endX = (int)msgData.players[msgData.ourTeamIndex].segments[lengthMyElephant - 1].x;
    endY = (int)msgData.players[msgData.ourTeamIndex].segments[lengthMyElephant - 1].y;

    // get all elephants
    for (int i = 0; i < msgData.participants; i++) {
        for (int j = 0; j < msgData.players[i].length; j++) {
            CPoint seg = msgData.players[i].segments[j];
            matrix[seg.x][seg.y] = -1;
        }
    }
}

void BFSDFS::setStartXY(int64_t x, int64_t y)
{
	startX = (int)x;
	startY = (int)y;
}

void BFSDFS::updateFoodMatrix(Food foods[], int64_t stock)
{
	for (int64_t i = 0; i < stock; i++)
	{
		matrix[foods[i].coordinate.x][foods[i].coordinate.y] = foods[i].type;
	}
}

#pragma mark ----------------------------

std::string BFSDFS::nextMove()
{
    //timing BFS
    auto check0 = std::chrono::high_resolution_clock::now();
	BFS();
    auto check1 = std::chrono::high_resolution_clock::now();
    
	/*std::cout << "(" << targetX << "," << targetY << ") = " << matrix[targetX][targetY] << " - fruit:" << fruit << std::endl;*/
	initialize();
	int dir = 0;
    dfsCalledCount = 0;
	if (targetX == -1 && targetY == -1) {
		for (int v = 0; v < 4; v++) {
			int tx = startX + dx[v];
			int ty = startY + dy[v];
			if (1 <= tx && tx <= N && 1 <= ty && ty <= M && matrix[tx][ty] != -1) {
				if (isCheckExit(tx, ty, endX, endY, false) != MAX_COST) {
					dir = v;
					break;
				}
			}
		}
	}
	else {
		DFS(startX, startY);
		dir = targetDirection[0];
	}
    auto check2 = std::chrono::high_resolution_clock::now();

	std::string move = "3";
	switch (dir)
	{
		case 2: move = "3"; break;
		case 1: move = "2"; break;
		case 0: move = "4"; break;
		case 3: move = "1"; break;
	}
    
    int move2 = targetDirection[1];
    switch (move2) {
        case 2: move.append("3"); break;
        case 1: move.append("2"); break;
        case 0: move.append("4"); break;
        case 3: move.append("1"); break;
    }
    
    std::chrono::duration<double, std::milli> elapsed1 = check1 - check0;
    std::chrono::duration<double, std::milli> elapsed2 = check2 - check1;
    printf("[debug]---- BFS-->DFS %f %f dfsCalledCount %d\n",
           elapsed1.count(), elapsed2.count(), dfsCalledCount);

	return move;
}









