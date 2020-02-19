#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_decode(char *s, int index, int *cache)
{
	int count = 0;

	/* end position */
	if (index == strlen(s)) {
		return 1;
	}
	if (index > strlen(s)) {
		return 0;
	}

	if (cache[index] > 0) {
		return cache[index];
	}
	/* options */
	if (s[index] > '0') {
		count += num_decode(s, index + 1, cache);
	}
	if ((s[index] == '1') || ((s[index] == '2') && (index + 1 < strlen(s)) && (s[index + 1] <= '6'))) {
		count += num_decode(s, index + 2, cache);
	}
	cache[index] = count;
	return count;
}
int numDecodings(char *s)
{
	int num = 0;
	int *cache = calloc(1, sizeof(int) * strlen(s));

	if (strlen(s) > 0) {
		num = num_decode(s, 0, cache);
	}
	free(cache);
	return num;
}

int main(void)
{
	char s[1024] = {0};

	scanf("%s", s);

	printf("%d\n", numDecodings(s));

	return 0;
}
