#include <stdio.h>
#include <string.h>
 
int main()
{
    long long int num;
    scanf("%lld", &num);
    int i, j, k;
    int length, front;
    long long int ans;
    for (i = 0; i < num; i++) {
        char line[1000001], temp[1000001];
        int alphabet['z' + 1] = {0};
        scanf("%s", line);
        length = strlen(line);
        j = 0;
        k = 'a';
        for (k = 'a'; k <= 'z'; k++) {
            while(!alphabet[k] && j < length) {
                alphabet[line[j]] += 1;
                j++;
            }
            
        }
        if ((!alphabet['a'] || !alphabet['b'] || !alphabet['c'] || !alphabet['d'] || !alphabet['e'] || !alphabet['f'] || !alphabet['g'] || !alphabet['h'] || !alphabet['i'] || !alphabet['j'] || !alphabet['k'] || !alphabet['l'] || !alphabet['m'] || !alphabet['n'] || !alphabet['o'] || !alphabet['p'] || !alphabet['q'] || !alphabet['r'] || !alphabet['s'] || !alphabet['t'] || !alphabet['u'] || !alphabet['v'] || !alphabet['w'] || !alphabet['x'] || !alphabet['y'] || !alphabet['z']) && (j >=length)) {
            printf("0\n");
            continue;
        }
        ans = 1;
        ans += length - j;
        for (front = 0; front < length - 26; front++) {
            alphabet[line[front]] -= 1;
            while (!alphabet[line[front]] && j < length) {
                alphabet[line[j]] += 1;
                j++;
            }
            if (!alphabet[line[front]] && j >= length) {
                break;
            }
            ans += length - j + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}