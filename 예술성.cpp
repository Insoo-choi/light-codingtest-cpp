#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>

int N;
int A[30][30]; // ���������� ����� ������ ��� �ʱⰪ�� �ڵ����� 0���� �ʱ�ȭ�� ���ݴϴ�.
int score; // score = 0;

struct QUE {
	int y, x;
}que[1000];

int head, tail;
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0, 1, 0,-1 };

int BFS(int y, int x, int g, int B[30][30]) { // return ���� �׷� g�� cnt gCnt
	int cnt = 1;
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
			cnt++;
		}
	}
	return cnt;
}

int calcPoint(int a, int b, int B[30][30], int gCnt[1000]) {
	// (�׷� a�� ���� ĭ�Ǽ� + �׷� b�� ���� ĭ�Ǽ�) x
	// gCnt[a] x gCnt[b]
	// �׷� a �� �̷�� �ִ� ���ڰ� x �׷� b�� �̷�� �ִ� ���� �� x
	// vA x vB A�迭�� ����ִ�.
	// �׷� a�� b�� ���� �´�� �ִ� ���� ��
	// tCnt

	int vA = 0, vB = 0, tCnt = 0;
	int ny, nx;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (B[i][j] == a) {
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
	int ret = 0;
	int B[30][30] = { 0, }; // �迭 ��ü�� 0���� �ʱ�ȭ �Ѵ�.
	int gCnt[1000] = { 0, };

	int g = 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (B[i][j] == 0) {
				gCnt[g] = BFS(i, j, g, B); // group�� �� ���������
				g++;
			}
		}
	}
	g--; // group count

	for (int a = 1; a <= g; a++) {
		for (int b = a + 1; b <= g; b++) {
			ret += calcPoint(a, b, B, gCnt);
			//a:1     2   3
			//b:2,3,4 3,4 4
		}
	}

	return ret;
}

void rotateCross() {
	int T[30][30];

	for (int i = 0; i < N; i++) { // T���ٰ� A ���� �� �������ش�.
		for (int j = 0; j < N; j++) {
			T[i][j] = A[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		A[i][N / 2] = T[N / 2][N - 1 - i];
	}

	for (int j = 0; j < N; j++) {// 5/2 = 2
		A[N / 2][j] = T[j][N / 2];
	}
}

void rotate90(int y, int x) {
	int T[15][15];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			T[i][j] = A[i + y][j + x];
		}
	}

	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			A[i + y][j + x] = T[N / 2 - 1 - j][i];
		}
	}
}

void rotateRemain() {
	rotate90(0,0);
	rotate90(0,N/2+1);
	rotate90(N/2+1,0);
	rotate90(N/2+1,N/2+1);

}


int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf(" %d", &A[i][j]);
		}
	}

	//sudo �ڵ�� ���Ƿ� �ۼ��غ���.
	//�ǻ� ���� �ڵ�

	score += getArtPoint(); // �ʱ�����
	for (int i = 0; i < 3; i++) {
		rotateCross();
		rotateRemain();
		score += getArtPoint(); // ȸ���� ���� �� �� ȸ���� ����
	}
	printf("%d\n", score);
}