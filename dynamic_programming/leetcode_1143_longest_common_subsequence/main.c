#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * x1, ..., xn is the first string,
 * y1, ..., ym is the second string,
 * z1, ..., zp is the lcs
 * if xi == yj == zk -> zk is lcs of xi and yj
 * else if zk = xi -> zk is lcs of xi and yj-1
 * else if zk = yj -> zk is lcs of xi - 1 and yj
 * lcs[i][j] = lcs[i - 1][j - 1] + 1 if xi == yj
 * lcs[i][j] = max{lcs[i][j - 1], lcs[i - 1][j]} if xi != yj
 */
int longest_common_subsequence(char *text1, char *text2)
{
	int len1 = strlen(text1);
	int len2 = strlen(text2);
	int i, j;
	int **lcs = calloc(1, sizeof(int *) * (len1 + 1));
	int longest = 0;

	for (i = 0; i <= len1; i++) {
 		lcs[i] = calloc(1, sizeof(int) * (len2 + 1));
	}
	for (i = 0; i <= len1; i++) {
		for (j = 0; j <= len2; j++) {
			if ((i == 0) || (j == 0)) {
				lcs[i][j] = 0;
			} else if (text1[i - 1] == text2[j - 1]) {
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			} else {
				lcs[i][j] = (lcs[i - 1][j] > lcs[i][j - 1] ? lcs[i - 1][j] : lcs[i][j - 1]);
			}

			longest = (longest < lcs[i][j] ? lcs[i][j] : longest);
		}
	}

	for (i = 0; i <= len1; i++) {
		free(lcs[i]);
	}
	free(lcs);

	return longest;
}

int main(void)
{
	char text1[1024] = {0};
	char text2[1024] = {0};

	scanf("%s", text1);
	scanf("%s", text2);

	printf("%d\n", longest_common_subsequence(text1, text2));

	return 0;
}
