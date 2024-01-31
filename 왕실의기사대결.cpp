#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>

int L, N, Q;
int A[50][50];
int dmgTotal;

struct KNIGHT {
	int r, c, h, w, k, m, d;
}K[40];

int que[1000];
int head, tail;
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int wallTouched(KNIGHT k) {
	for (int i = k.r; i < k.r + k.h; i++) {
		for (int j = k.c; j < k.c + k.w; j++) {
			if (A[i][j] == 2) return 1; // wall touch
		}
	}
	return 0;
}

int overlapChk(KNIGHT s, KNIGHT d) {
	for (int i = s.r; i < s.r + s.h; i++) {
		for (int j = s.c; j < s.c + s.w; j++) {
			if (i >= d.r && i < d.r + d.h && j >= d.c && j < d.c + d.w) return 1;
		}
	}
	return 0;
}

int moveKnightChk(int id, int d) {
	if (K[id].k <= 0) return 0;
	//bfs
	head = tail = 0;
	que[tail++] = id;
	K[id].m = 1;

	int cur;
	KNIGHT curKnight;

	while (head != tail) {
		cur = que[head++];
		curKnight = K[cur];

		curKnight.r += dr[d]; // curKnight의 값을 바꾸어 주었지만, K[cur] 의 값은 변하지 않았다.
		curKnight.c += dc[d]; // 밀려나는 knight를 모두 탐색을 할텐데, 그 중에 움직이지 못하는 기사가 있으면 모든 움직임을 무효로

		for (int i = 1; i <= N; i++) {
			if (curKnight.r < 1 || curKnight.c < 1 || curKnight.r + curKnight.h - 1 > L || curKnight.c + curKnight.w - 1 > L) return 0;
			if (wallTouched(curKnight)) return 0;
			if (i == cur) continue;
			if (K[i].k == 0) continue;
			if (K[i].m == 1) continue;
			if (overlapChk(curKnight, K[i])) {
				que[tail++] = i;
				K[i].m = 1;
			}
		}
	}
	return 1;
}

void getDmg(int id) {
	for (int i = K[id].r; i < K[id].r + K[id].h; i++) {
		for (int j = K[id].c; j < K[id].c + K[id].w; j++) {
			if (A[i][j] == 1 && K[id].k != 0) {
				K[id].k--;
				K[id].d++; // 마지막에 구해야 하는 값이 살아있는 기사의 데미지 총합이기 때문에 그렇다.
			}
		}
	}
}

void moveKnight(int id, int d) {
	for (int i = 1; i <= N; i++) {
		if (K[i].k <= 0) continue;
		if (K[i].m == 1) {
			K[i].r += dr[d];
			K[i].c += dc[d];
			if (id != i) {
				getDmg(i);
			}
		}
	}
}

void damageChk(int id, int d) {
	for (int i = 1; i <= N; i++) {
		if (K[i].k > 0) {
			dmgTotal += K[i].d;
		}
	}
}

int main() {
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d %d %d", &L, &N, &Q);
	for (int i = 1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			scanf(" %d", &A[i][j]);
		}
	}

	int r, c, h, w, k;

	for (int n = 1; n <= N; n++) {
		scanf(" %d %d %d %d %d", &r, &c, &h, &w, &k);
		K[n] = { r,c,h,w,k,0,0 };
	}

	int i, d;
	int ret;
	for (int q = 1; q <= Q; q++) {
		scanf(" %d %d", &i, &d);

		//sudo 실제로 동작하는 코드는 아니지만, 의미를 구별해서 임의로 작성해보는것(의사결정코드)
		ret = moveKnightChk(i, d);
		if (ret == 1) { // 다 조사해봤는데, 내가 기사.m에다가 움직여야 할 기사를 표시도 해뒀고, 얘네들 실제로도 움직이는게 맞아!
			moveKnight(i, d);
		}
		for (int j = 1; j <= N; j++) {
			K[j].m = 0;
		}
	}

	damageChk(i, d);

	printf("%d\n", dmgTotal);
}
