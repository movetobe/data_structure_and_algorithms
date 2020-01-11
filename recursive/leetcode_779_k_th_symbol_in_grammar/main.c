#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k_th_grammar(int N, int K)
{
	if (N == 0) {
		return 0;
	}

	return (k_th_grammar(N - 1, K / 2) ^ (K % 2));
}

int kthGrammar(int N, int K)
{
	return k_th_grammar(N - 1, K - 1);
}
int main(void)
{
	int N = 0;
	int K = 0;

	scanf("%d %d", &N, &K);

	printf("%d\n", kthGrammar(N, K));
	return 0;
}
