#include <stdio.h>

int compare(char *shortt, char *longg, int short_len, int long_len);

int main()
{
	int pair;
	scanf("%d", &pair);
	while (pair != 0) {
		char sen1[100000], sen2[100000];
		scanf("%s%s", sen1, sen2); //printf("sen1: %s sen2: %s\n", sen1, sen2);
		int times;
		scanf("%d", &times); //printf("times: %d\n", times);
		while (times != 0) {
			int head1, tail1, head2, tail2;
			scanf("%d%d%d%d", &head1, &tail1, &head2, &tail2); //printf("%d %d %d %d\n", head1, tail1, head2, tail2);
			char *temp1, *temp2;
			temp1 = &sen1[head1];
			temp2 = &sen2[head2];
			int len1, len2;
			len1 = tail1 - head1 + 1;
			len2 = tail2 - head2 + 1;
			int ans;
			if (len1 < len2) {
				ans = compare(temp1, temp2, len1, len2); //compare(short, long);
			}
			else {
				ans = compare(temp2, temp1, len2, len1);
			}
			printf("%d\n", ans);
			times--;
		}
		pair--;
	}
	return 0;
}

int compare(char *shortt, char *longg, int short_len, int long_len) {
	int ans = 0;
	int value = 0, sum = 0;
	int i, j, k; //printf("short: %d\n", short_len);
/*	for (i = 0; i < short_len; i++) {
	    printf("%c", *(shortt+i));
	}
	printf("\n");
	for (i = 0; i < long_len; i++) {
	    printf("%c", *(longg+i));
	}
	printf("\n");*/
	for (i = 0; i < short_len; i++) {
		value += *(shortt + i) - 'a';
		sum += *(longg + i) - 'a';
	}
	if (sum == value) {
		int test = 0;
		for (k = 0; k < short_len; k++) {
			if (*(shortt + k) == *(longg + k)) {
				test++;
			}
			else
				break;
		}
		if (test == short_len)
			ans++;
	}
	
	for (i = 1; i <= long_len - short_len; i++) {
		sum = sum - (*longg - 'a') + (*(longg + short_len) - 'a');
		longg++;
		if (sum == value) {
			int test = 0;
			for (k = 0; k < short_len; k++) {
				if (*(shortt + k) == *(longg + k)) {
					test++;
				}
				else
					break;
			}
			if (test == short_len)
				ans++;
		}
	}
	return ans;
}