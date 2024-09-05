#define _CRT_SECURE_NO_WARNINGS
//git add, commit test 
#include <stdio.h>

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int main()
{
	int N, K;
	scanf("%d, %d", &N, &K);
	int W[100] = {0, };
	int V[100] = { 0, };
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &W[i], &V[i]);
	}
	int DP[100][100] = { 0, };

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < K; j++) {
			if (j - W[i] >= 0) DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - W[i]] + V[i]);
			else DP[i][j] = DP[i - 1][j];
		}
	}
	
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < K; j++) {
			printf("%3d", DP[i][j]);
		}
		printf("\n");
	}

	return 0;
}

