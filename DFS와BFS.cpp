#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
// c언어에서 input, output 을 담당하는 코드를 담아둔 library
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
	* 1. 재귀함수의 인자로 넘겨줘야 할 것은 무엇인가?
	* 2. 데이터의 유효성 검사(=간선이 있나요?) + 방문 이력을 검사(=방문을 안한 점이 맞나요?)
	* 3. 해당 데이터로 넘어가서 DFS 를 계속 진행
	* 4. 필요시, 가지치기를 진행한다.
	*/
	printf("%d ", c);
	Visited[c] = 1;// 0: 미 방문, 1: 방문

	//2. 데이터 유효성, 방문이력
	for (int i = 1; i <= N; i++) {
		if (L[c][i] == 1 && Visited[i] == 0) {
			//3. 계속 탐색을 진행해도 되는 점 : i
			DFS(i);
		}
	}
}

//배열을 이용해서 큐를 구현한다.
//데이터의 유효성에 따라 큐에 데이터를 저장한다.
//다음 데이터를 탐색한다.
//필요에 따라 데이터를 가지치기 한다.

int Que[10005]; // M < 10000;
int head, tail;
int BVisited[1005];
/*
* 0 1 2 3 4
* ㅁㅁㅁㅁㅁ
*   ^     ^
*   h     t
* head : data를 pop 했을때, 데이터가 나오게 될 index
* tail : data를 push 했을때, 데이터가 들어가게 될 index
*/

void BFS() {
	//V
	Que[tail++] = V; // push();
	BVisited[V] = 1;

	int c;

	while (tail != head) { // Que 안의 데이터 갯수 => tail - head = 0 => 더이상 탐색할 데이터가 없음.
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