#include <stdio.h>

int array[200001][100] = {{0}};
int anti[200001][100] = {{0}};
int count1[200001] = {0};	//代表每個城市接幾個其他城市
int count2[200001] = {0};	//代表每個城市接幾個其他城市
int dis_1[200001][2] = {{0}};
//road[][0] color 0:white 1:gray 2:black
//road[][1] distance
int dis_n[200001][2] = {{0}};
//dis[][0] distance remember
//dis[][1] distance to n
int queue[200000];

int main()
{
	int total, city, link, add;
	int city_1, city_2;
	int i, j;
	scanf("%d", &total);
	while (total--) {
		scanf("%d%d%d", &city, &link, &add);
		for (i = 1; i <= city; i++) {
			for (j = 0; j < count1[i]; j++) array[i][j] = 0;
			count1[i] = 0;
			for (j = 0; j < count2[j]; j++) anti[i][j] = 0;
			count2[i] = 0;
		}
		for (i = 1; i <= city; i++) {
			dis_1[i][0] = dis_1[i][1] = dis_n[i][0] = dis_n[i][1] = 0;
		}
		while (link--) {
			scanf("%d%d", &city_1, &city_2);
			array[city_1][ count1[city_1] ] = city_2;
			anti[city_2][ count2[city_2] ] = city_1;
			count1[city_1]++;
			count2[city_2]++;
		}
		dis_1[1][0] = 1;
		int head, tail;	//head裡面會有東西 tail是空的，前一個才有東西
		head = tail = 0;
		queue[tail] = 1;	tail++;
		int now_city;
		while (head != tail) {
			now_city = queue[head];	head = (head + 1) % 200000;
			for (i = 0; i < count1[ now_city ]; i++) {
				int which_city = array[ now_city ][i];
				if (dis_1[ which_city ][0] == 0) {
					dis_1[ which_city ][0] = 1;
					dis_1[ which_city ][1] = dis_1[ now_city ][1] + 1;
					queue[tail] = which_city;	tail = (tail + 1) % 200000;
				}
			}
			dis_1[ now_city ][0] = 2;
		}
		dis_n[city][0] = 1;
		head = tail = 0;
		queue[tail] = city;	tail++;
		while (head != tail) {
			now_city = queue[head];	head = (head + 1) % 200000;
			for (i = 0; i < count2[ now_city ]; i++) {
				int which_city = anti[ now_city ][i];
				if (dis_n[ which_city ][0] == 0) {
					dis_n[ which_city ][0] = 1;
					dis_n[ which_city ][1] = dis_n[ now_city ][1] + 1;
					queue[tail] = which_city;	tail = (tail + 1) % 200000;
				}
			}
			dis_n[ now_city ][0] = 2;
		}
		while (add--) {
			scanf("%d%d", &city_1, &city_2);
			if ((dis_1[city_1][1] == 0 && city_1 != 1) || dis_n[city_2][1] == 0 && city_2 != city)
				printf("%d\n", dis_1[city][1]);
			else {
				int cost = dis_1[city_1][1] + 1 + dis_n[city_2][1];
				if (cost > dis_1[city][1]) printf("%d\n", dis_1[city][1]);
				else printf("%d\n", cost);
			}
		}
	}	
	return 0;
}