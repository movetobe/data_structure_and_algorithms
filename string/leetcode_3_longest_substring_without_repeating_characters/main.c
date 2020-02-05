#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LEN 256
int check_repeat(char *s, int start, int current, int *char_index)
{
	int new_start = -1;

	/* repeat */
	if (char_index[s[current]] >= start) {
		new_start = char_index[s[current]] + 1;
	}
	/* no repeat */

	return new_start;
}

int length_of_longest_substring(char *s)
{
	int start = 0, new_start = 0;
	int current = 0;
	int longest = 0;
	int char_index[MAX_CHAR_LEN];
	int s_len = strlen(s);
	int i = 0;

	if (s_len < 2) {
		return s_len;
	}

	for (i = 0; i < MAX_CHAR_LEN; i++) {
		char_index[i] = -1;
	}

	char_index[s[0]] = 0;
	for (current = 1; current < s_len; current++) {
		new_start = check_repeat(s, start, current, char_index);
		if (new_start >= 0) {
			longest = (current - start) > longest ? (current - start) : longest;
			start = new_start;
		} else {
			longest = (current - start + 1) > longest ? (current - start + 1) : longest;
		}
		char_index[s[current]] = current;
	}

	return longest;
}

int main(void)
{
	char s[1024] = {0};

	scanf("%s", s);

	printf("%d\n", length_of_longest_substring(s));

	return 0;
}
