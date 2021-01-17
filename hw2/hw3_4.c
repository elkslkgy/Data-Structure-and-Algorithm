#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

int main()
{
    int num;
    scanf("%d", &num);
    char c; scanf("%c", &c); //put the trash '\n' after 2 into the trash can.
    int i, j;
    char sen[1000010], order[30];
    for (i = 0; i < num; i++) {
        //scanf("%[^\n]%c", sen); printf("%s\n", sen);
        //if (i != 0) printf("\n");
        gets(sen); //printf("%s\n", sen);
        int len = strlen(sen); //printf("%d\n", len);
        int alp[26] = {0};
        int max = 0;
        //printf("here0\n");
        for (j = 0; j < len; j++) {
            if (!isalpha(sen[j])) continue;
            char s;
            s = sen[j];
            alp[s - 'a']++;
            if (alp[s - 'a'] > max) {
                max = alp[s - 'a'];
                //printf("replace: %d %d\n", s - 'a', alp[s - 'a']);
            } //printf("%c %d\n", s, alp[s]);
        }
        //printf("here1\n");
        int k = 0, a; //printf("%d\n", k);
        for (j = max; j > 0; j--) {
            for (a = 'a'; a <= 'z'; a++) {
                //printf("max = %d\n", max);
                if (alp[a - 'a'] == j) {
                    order[k] = a;
                    k++;
                }
            }
        }
        //printf("here2\n");
        order[k] = '\0';//printf("%d\n", k);
        char newalp[26];
        int length = strlen(order); //printf("%d\n", length);
        for (j = 0; j < length; j++) {
            char s, ss;
            s = order[j];
            ss = order[length - j - 1];
            newalp[s - 'a'] = ss;
        }
        for (j = 0; j < len; j++) {
            if (sen[j] <= 'z' && sen[j] >= 'a') {
                sen[j] = newalp[sen[j] - 'a'];
            }
        }
        sen[len] = '\0';
        printf("%s\n", sen);
    }
    return 0;
}