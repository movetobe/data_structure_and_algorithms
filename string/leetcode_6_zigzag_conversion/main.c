#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert(char *s, int numRows)
{
	int row = 0, col = 0;
	int down = 1;
	int i, s_len = strlen(s);
	char **zigzag = calloc(1, sizeof(char *) * numRows);
	char *new_s = calloc(1, sizeof(char) * (s_len + 1));

	if (numRows <= 1) {
		memcpy(new_s, s, sizeof(char) * s_len);
		free(zigzag);
		return new_s;
	}

	for (i = 0; i < numRows; i++) {
		zigzag[i] = calloc(1, sizeof(char) * s_len);
	}

	for (i = 0; i < s_len; i++) {
		if (down) {
			zigzag[row][col] = s[i];
			row++;
			if (row >= numRows) {
				row -= 2;
				col++;
				down = 0;
			}
		} else {
			zigzag[row][col] = s[i];
			row--;
			col++;
			if (row < 0) {
				row += 2;
				col--;
				down = 1;
			}
		}
	}

	i = 0;
	for (row = 0; row < numRows; row++) {
		for (col = 0; col < s_len; col++) {
			if (zigzag[row][col]) {
				new_s[i] = zigzag[row][col];
				i++;
			}
		}
		free(zigzag[row]);
	}
	free(zigzag);

	return new_s;
}

int main(void)
{
	char s[1024] = {0};
	int numRows = 0;

	scanf("%s", s);
	scanf("%d", &numRows);

	printf("%s\n", convert(s, numRows));

	return 0;
}
