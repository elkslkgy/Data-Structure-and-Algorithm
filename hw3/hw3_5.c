#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *one;
	struct Node *zero;
	int end; //1 for end, 0 for not the end
};

void insert(struct Node *now, int num, int N, int bit);
int check(struct Node *now, int num, int bit);

int main()
{
	int t;
	scanf("%d", &t);
	int m, n;
	struct Node *now;
	while (t) {
		scanf("%d%d", &m, &n);
		now = (struct Node *)malloc(sizeof(struct Node));
		now->one = now->zero = NULL;
		now->end = 0;
		int a, b, c, d, N;
		while (m) {
			scanf("%d.%d.%d.%d/%d", &a, &b, &c, &d, &N);
			insert(now, (a << 24) + (b << 16) + (c << 8) + d, N, 31);
			m--;
		}
		while (n) {
			scanf("%d.%d.%d.%d", &a, &b, &c, &d);
			if (check(now, (a << 24) + (b << 16) + (c << 8) + d, 31))
				printf("TRUE\n");
			else
				printf("FALSE\n");
			n--;
		}
		t--;
	}
	return 0;
}

void insert(struct Node *now, int num, int N, int bit) {
	if (N <= 0) {
		now->end = 1;
		return;
	}
	int ans;
	ans = num >> bit & 1;
	if (ans) {
		if (now->one == NULL) {
			now->one = (struct Node *)malloc(sizeof(struct Node));
			//printf("1");
			now->one->end = 0;
			now->one->one = now->one->zero = NULL;
		}
		insert(now->one, num, N - 1, bit - 1);
		return;
	}
	if (now->zero == NULL) {
		now->zero = (struct Node *)malloc(sizeof(struct Node));
		//printf("0");
		now->zero->end = 0;
		now->zero->one = now->zero->zero = NULL;
	}
	insert(now->zero, num, N - 1, bit - 1);
	return;
}

int check(struct Node *now, int num, int bit) {
	if (now->end == 1)
		return 1;
	if (num >> bit & 1) {
		if (now->one == NULL)
			return 0;
		else
			return check(now->one, num, bit - 1);
	}
	if (now->zero == NULL)
		return 0;
	else
		return check(now->zero, num, bit - 1);
}