#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _WORDBANK
	#define _WORDBANK ""
#endif

#ifndef _WORDBANK_LENGTH
	#define _WORDBANK_LENGTH 0
#endif

char *wordbank = "";
size_t wordbank_length = 0;

static int random_int(int start, int end) {
	int diff = 0, result = 0;

	diff = end - start;
	result = (rand() % diff) + start;

	return result;
}

static int word(char **text, int capitalize) {	
	int rc = 0, i = 0, l = 0;
	int start = 0, end = 0, length = 0;
	char *word = NULL;

	for (i = random_int(0, (int)wordbank_length), l = 0; i >= l; i--) {
		if (wordbank[i] == ' ') {
			break;
		}
	}

	start = i;

	for (i = start + 1, l = (int)wordbank_length; i < l; i++) {
		if (wordbank[i] == ' ' || wordbank[i] == '\0') {
			break;
		}
	}

	end = i;
	length = end - start;

	word = malloc(sizeof(char) * (length + 1));

	if (!word) {
		printf("Memory error\n");

		rc = 1;
		goto cleanup;
	}

	strncpy(word, wordbank + start + 1, (size_t)(length - 1));
	word[end - start] = '\0';

	if (capitalize == 1) {
		word[0] -= ' ';
	}

	*text = word;

cleanup:
	return rc;
}

static void usage(char *exec) {
	int length = 0;

	length = (int)strlen(exec) + 7;

	printf("Usage: %s [-w,--word (<count>)]\n", exec);
	printf("%*s [-s,--sentence (<count>)]\n", length, " ");
	printf("%*s [-p,--paragraph (<count>)]\n", length, " ");
	printf("%*s [-h]\n", length, " ");
}

int main(int argc, char *argv[]) {
	int rc = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0;
	int count = 1, capitalize = 0;
	char *exec = NULL, *action = NULL, *text = NULL;

	wordbank_length = _WORDBANK_LENGTH;

	if (wordbank_length == 0) {
		printf("Missing wordbank\n");

		rc = 1;
		goto cleanup;
	}

	wordbank = malloc(sizeof(char) * (wordbank_length + 1));

	if (!wordbank) {
		printf("Memory error\n");

		rc = 1;
		goto cleanup;
	}

	strcpy(wordbank, _WORDBANK);

	exec = argv[0];

	if (argc < 2) {
		usage(exec);

		rc = 1;
		goto cleanup;
	}

	action = argv[1];

	if (argc > 2) {
		count = atoi(argv[2]);
	}

	srand((unsigned int)time(NULL));

	if (strcmp(action, "-w") == 0 || strcmp(action, "--word") == 0) {
		for (i = 0, j = count; i < j; i++) {
			if (i != 0) {
				printf(" ");
			}

			if (word(&text, capitalize) != 0) {
				rc = 1;
				goto cleanup;
			}

			printf("%s", text);
		}

		printf("\n");
	} else if (strcmp(action, "-s") == 0 || strcmp(action, "--sentence") == 0) {
		for (i = 0, j = count; i < j; i++) {
			if (i != 0) {
				printf(" ");
			} else {
				capitalize = 1;
			}

			for (k = 0, l = random_int(10, 20); k < l; k++) {
				if (k != 0) {
					printf(" ");
				}

				if (word(&text, capitalize) != 0) {
					rc = 1;
					goto cleanup;
				}

				printf("%s", text);

				if (capitalize == 1) {
					capitalize = 0;
				}
			}

			printf(".");
			capitalize = 1;
		}

		printf("\n");
	} else if (strcmp(action, "-p") == 0 || strcmp(action, "--paragraph") == 0) {
		for (i = 0, j = count; i < j; i++) {
			if (i != 0) {
				printf("\n\n");
			}

			for (k = 0, l = random_int(3, 5); k < l; k++) {
				if (k != 0) {
					printf(" ");
				} else {
					capitalize = 1;
				}

				for (m = 0, n = random_int(10, 20); m < n; m++) {
					if (m != 0) {
						printf(" ");
					}

					if (word(&text, capitalize) != 0) {
						rc = 1;
						goto cleanup;
					}

					printf("%s", text);

					if (capitalize == 1) {
						capitalize = 0;
					}
				}

				printf(".");
				capitalize = 1;
			}
		}

		printf("\n");
	} else if (strcmp(action, "-h") == 0 || strcmp(action, "--help") == 0) {
		usage(exec);

		rc = 1;
		goto cleanup;
	} else {
		printf("Unknown action %s\n", action);

		rc = 1;
		goto cleanup;
	}

cleanup:
	if (text) {
		free(text);
	}

	if (wordbank) {
		free(wordbank);
	}

	return rc;
}