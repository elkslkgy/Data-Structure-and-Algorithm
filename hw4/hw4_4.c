#include <stdio.h>

int array[1000001][2];

int find_root(int player);
int go_through(int player);

int main()
{
	int total, robots, questions;
	char command;
	int player_1, player_2;
	char relation;
	int relate;
	int i, temp;
	scanf("%d", &total);
	while (total--) {
		scanf("%d%d", &robots, &questions);
		for (i = 1; i <= robots; i++) {
			array[i][0] = -1;
			array[i][1] = 0;
		}
		while (questions--) {
			scanf("\n%c", &command);
			if (command == 'R') {
				scanf("%d%d %c", &player_1, &player_2, &relation);
				if (relation == 'W') relate = 1;
				else if (relation == 'L') relate = 3;
				else if (relation == 'S') relate = 0;
				else if (relation == 'N') relate = 2;
				int root_1, root_2;	//代表第幾個機器人
				root_1 = find_root(player_1);
				root_2 = find_root(player_2);
				if (root_1 != root_2) {
					array[root_2][0] = root_1;
					temp = (relate - array[player_2][1] + array[player_1][1]) % 4;
					while (temp < 0) temp += 4;
					array[root_2][1] = temp;
					printf("O\n");
				}
				else {
					//判斷兩個玩家的結果對不對
					temp = (array[player_2][1] - array[player_1][1]) % 4;
					while (temp < 0) temp += 4;
					if (temp == relate) printf("O\n");
					else printf("X\n");
				}
			}
			else if (command == 'A') {
				scanf("%d%d", &player_1, &player_2);
				int root_1, root_2;	//代表第幾個機器人
				root_1 = find_root(player_1);
				root_2 = find_root(player_2);
				//printf("%d %d\n", array[player_1][1], array[player_2][1]);
				if (root_1 != root_2) printf("?\n");
				else {
					temp = (array[player_2][1] - array[player_1][1]) % 4;
					while (temp < 0) temp += 4;
					if (temp == 0) printf("S\n");
					else if (temp == 1) printf("W\n");
					else if (temp == 2) printf("N\n");
					else if (temp == 3) printf("L\n");
				}
			}
		}
	}
	return 0;
}

int find_root(int player)
{
	if (array[player][0] < 0) return player;
	else {
		array[player][1] = go_through(player);
		array[player][0] = find_root(array[player][0]);
		return array[player][0];
	}
}

int go_through(int player)
{
	if (array[player][0] < 0) return 0;
	else {
		return array[player][1] + go_through(array[player][0]);
	}
}