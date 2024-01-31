#include <cstdio>

int N;
int A[30][30];
int score;

struct QUE {
	int y, x;
}que[1000];
int head, tail;
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int BFS(int y, int x, int g, int B[30][30]) {
	int ret = 1;
	head = tail = 0;

	int v = A[y][x];
	que[tail++] = { y,x };
	B[y][x] = g;

	QUE c;

	int ny, nx;

	while (head != tail) {
		c = que[head++];

		for (int i = 0; i < 4; i++) {
			ny = c.y + dy[i];
			nx = c.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
			if (A[ny][nx] != v) continue;
			if (B[ny][nx] != 0) continue;
			que[tail++] = { ny,nx };
			B[ny][nx] = g;
			ret++;
		}
	}

	return ret;
}

int calcPoint(int a, int b, int B[30][30], int gCnt[1000]) {
	//(그룹 a에 속한 칸의 수 + 그룹 b에 속한 칸의 수 ) x 
	// gCnt[a] x gCnt[b]
	//그룹 a를 이루고 있는 숫자 값 x 그룹 b를 이루고 있는 숫자 값 x 
	// vA, x vB
	//그룹 a와 그룹 b가 서로 맞닿아 있는 변의 수로 정의됩니다.
	// tCnt
	int vA = 0, vB = 0, tCnt = 0;
	int ny, nx;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (B[i][j] == a) { // a 그룹을 찾기
				vA = A[i][j];

				for (int k = 0; k < 4; k++) {
					ny = i + dy[k];
					nx = j + dx[k];
					if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
					if (B[ny][nx] == b) {
						vB = A[ny][nx];
						tCnt++;
					}
				}
			}
		}
	}

	return (gCnt[a] + gCnt[b]) * vA * vB * tCnt;
}

int getArtPoint() {
	int B[30][30] = { 0, };
	int gCnt[1000] = { 0, };

	int g = 1;
	int point = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (B[i][j] == 0) {
				gCnt[g] = BFS(i, j, g, B);
				g++;
			}
		}
	}
	g--;
	//g 만큼의 그룹

	for (int a = 1; a <= g; a++) {
		for (int b = a + 1; b <= g; b++) {
			point += calcPoint(a, b, B, gCnt);
		}
	}

	return point;
}

void rotateCross() {
	int T[30][30];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			T[i][j] = A[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		A[i][N / 2] = T[N / 2][N - 1 - i];
	}

	for (int j = 0; j < N; j++) {
		A[N / 2][j] = T[j][N / 2];
	}
}

void rotate90(int y, int x) {
	int T[15][15];
	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			T[i][j] = A[y + i][x + j];
		}
	}

	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			A[y + i][x + j] = T[N / 2 - 1 - j][i];
		}
	}
}

void rotateRemain() {
	rotate90(0, 0);
	rotate90(0, N / 2 + 1);
	rotate90(N / 2 + 1, 0);
	rotate90(N / 2 + 1, N / 2 + 1);
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf(" %d", &A[i][j]);
		}
	}

	score += getArtPoint();
	for (int i = 0; i < 3; i++) {
		rotateCross();
		rotateRemain();
		score += getArtPoint();
	}
	printf("%d\n", score);
}