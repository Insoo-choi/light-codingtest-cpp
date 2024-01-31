#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
// c���� input, output �� ����ϴ� �ڵ带 ��Ƶ� library
// scanf, printf

int N, M, V;
int L[1001][1001];
int Visited[1001];
/*
0100
1000
0000
0000
*/

void DFS(int c) {
	/*
	* 1. ����Լ��� ���ڷ� �Ѱ���� �� ���� �����ΰ�?
	* 2. �������� ��ȿ�� �˻�(=������ �ֳ���?) + �湮 �̷��� �˻�(=�湮�� ���� ���� �³���?)
	* 3. �ش� �����ͷ� �Ѿ�� DFS �� ��� ����
	* 4. �ʿ��, ����ġ�⸦ �����Ѵ�.
	*/
	printf("%d ", c);
	Visited[c] = 1;// 0: �� �湮, 1: �湮

	//2. ������ ��ȿ��, �湮�̷�
	for (int i = 1; i <= N; i++) {
		if (L[c][i] == 1 && Visited[i] == 0) {
			//3. ��� Ž���� �����ص� �Ǵ� �� : i
			DFS(i);
		}
	}
}

//�迭�� �̿��ؼ� ť�� �����Ѵ�.
//�������� ��ȿ���� ���� ť�� �����͸� �����Ѵ�.
//���� �����͸� Ž���Ѵ�.
//�ʿ信 ���� �����͸� ����ġ�� �Ѵ�.

int Que[10005]; // M < 10000;
int head, tail;
int BVisited[1005];
/*
* 0 1 2 3 4
* ����������
*   ^     ^
*   h     t
* head : data�� pop ������, �����Ͱ� ������ �� index
* tail : data�� push ������, �����Ͱ� ���� �� index
*/

void BFS() {
	//V
	Que[tail++] = V; // push();
	BVisited[V] = 1;

	int c;

	while (tail != head) { // Que ���� ������ ���� => tail - head = 0 => ���̻� Ž���� �����Ͱ� ����.
		c = Que[head++]; // pop();
		printf("%d ", c);

		for (int i = 1; i <= N; i++) {
			if (L[c][i] == 1 && BVisited[i] == 0) {
				// push();
				Que[tail++] = i;
				BVisited[i] = 1;
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &V);

	int s, e;
	for (int i = 0; i < M; i++) {
		scanf(" %d %d", &s, &e);
		L[s][e] = 1;
		L[e][s] = 1;
	}

	DFS(V);
	printf("\n");
	BFS();
}