#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lp[i][j] = lp[i + 1][j - 1] + 1 if s[i + 1] == s[j - 1]
 * else lp[i][j] = lp[i + 1][j - 1]
 * lp[i][i] = 1;
 * lp[i][i + 1] = 2 if s[i] == s[i + 1]
 */
char *longestPalindrome(char *s)
{
	int i = 0;
	int j = 0;
	int len = strlen(s);
	int **lp = calloc(1, sizeof(int *) * len);
	char *lp_str = NULL;
	int start = 0;
	int lp_len = 0;

	for (i = 0; i < len; i++) {
		lp[i] = calloc(1, sizeof(int) * len);
	}

	for (i = (len - 1); i >= 0; i--) {
		for (j = i; j < len; j++) {
			if (i == j) {
				lp[i][j] = 1;
				continue;
			}
			if (((i + 1) == j) && (s[i] == s[j])) {
				lp[i][j] = 2;
				continue;
			}
			if (s[i] == s[j]) {
				lp[i][j] = lp[i + 1][j - 1] + 2;
			} else if ((i + 1) < j) {
				lp[i][j] = lp[i + 1][j - 1];
			}
		}
	}

	for (i = 0; i < len; i++) {
		for (j = i; j < len; j++) {
			if ((lp[i][j] > lp_len) && (lp[i][j] == (j - i + 1))) {
				lp_len = j - i + 1;
				start = i;
			}
		}
	}
	lp_str = calloc(1, sizeof(char) * lp_len);
	for (i = start, j = 0; j < lp_len; i++, j++) {
		lp_str[j] = s[i];
	}

	return lp_str;
}

int main(void)
{
	char s[1024] = {0};

	scanf("%s", s);

	printf("%s\n", longestPalindrome(s));

	return 0;
}
