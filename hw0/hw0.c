#include <stdio.h>
int main ()
{
	int num;
	scanf("%d", &num);
	int i;
	for (i = 0; i < num; i++) {
		int temp;
		scanf("%d", &temp);
		int j;
		for (j = 0; j < temp; j++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}