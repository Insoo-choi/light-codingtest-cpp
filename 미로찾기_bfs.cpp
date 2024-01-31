#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
int N, M;
int A[105][105];

/*
1. 배열을 이용해서 큐를 구현한다.
2. 데이터의 유효성에 따라 큐에 데이터를 저장한다.
3. 다음 데이터를 탐색한다.
4. 필요에 따라 데이터를 가지치기 한다.
*/

struct pos {
	int y, x, c;
};

pos Que[100 * 100 + 100];
int head, tail;
int V[105][105];

/*
    ^
   <0>
	v
*/
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

void BFS() {
	Que[tail++] = { 1,1,1 };
	V[1][1] = 1;

	pos cur;
	while (head != tail) {
		cur = Que[head++];
		if (cur.x == M && cur.y == N) {
			printf("%d\n", cur.c);
			return;
		}
		// cur.y, cur.x, cur.c;
		int ny, nx;
		for (int i = 0; i < 4; i++) {
			ny = cur.y + dy[i];
			nx = cur.x + dx[i];
			if (ny < 1 || ny > N || nx <1 || nx >M)continue;
			if (A[ny][nx] != 1) continue;
			if (V[ny][nx] != 0) continue;

			Que[tail++] = { ny,nx,cur.c + 1 };
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	/*
	101111 trim
	101010
	101011
	111011
	*/
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf(" %1d", &A[i][j]);
		}
	}

	BFS();
}