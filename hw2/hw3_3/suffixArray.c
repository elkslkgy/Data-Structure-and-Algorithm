#include <stdio.h>
#include <string.h>

char t[200002]; //放字串排列
int sa[200002]; //在merge的時候幫忙記東西的陣列
int totalLen;
int c[200002];   // counting sort array
int temp[2][200002];
int alphabet[26];
//int pi[100001];
//int short_pi[100001];

void suffix_array();
int Rabin_Karp(int place, int SLS, int shortLen, int LLS);
//void shortKMP(int shortLen, int start);

int main()
{
    int pair;
    scanf("%d", &pair);
    while (pair != 0) {
        char sen1[100001];
        scanf("%s%s", t, sen1);
        int length, length1;
        length = strlen(t);
        length1 = strlen(sen1);
        totalLen = length + length1;
        strcat(t, sen1);
        // make the two strings together

        suffix_array();
        int times;
        scanf("%d", &times);
        while (times != 0) {
        	int ans = 0;
        	int head1, tail1, head2, tail2;
			scanf("%d%d%d%d", &head1, &tail1, &head2, &tail2); //printf("%d %d %d %d\n", head1, tail1, head2, tail2);
			int len1, len2;
			len1 = tail1 - head1 + 1;
			len2 = tail2 - head2 + 1;
			int shortLen, longLen, SLS, LLS;
			if (len1 > len2) {
				longLen = len1;
				shortLen = len2;
				SLS = head2 + length;
				LLS = head1;
			}
			else {
				longLen = len2;
				shortLen = len1;
				SLS = head1;
				LLS = head2 + length;
			}
			//shortKMP(shortLen, SLS);
			//longKMP(longLen, LLS, SLS);
			int topAlph;
			int i;
			topAlph = t[SLS];
			if (topAlph == 'a') {
				for (i = 0; i < alphabet[topAlph - 'a']; i++) {
					if (sa[i] == SLS) break;
				}	
			}
			else {
				for (i = alphabet[topAlph - 'a' - 1]; i < alphabet[topAlph - 'a']; i++) {
					if (sa[i] == SLS) break;
				}
			}
			topAlph = t[LLS];
			if (topAlph == 'a') {
				for (i = 0; i < alphabet[topAlph - 'a']; i++) {
					if (sa[i] >= longLen - shortLen + 1 + LLS) {
						continue;
					}
					else if (sa[i] < LLS) {
						continue;
					}
					else {
						if (Rabin_Karp(i, SLS, shortLen, LLS)) {
							ans++;
						}
					}
				}	
			}
			else {
				for (i = alphabet[topAlph - 'a' - 1]; i < alphabet[topAlph - 'a']; i++) {
					if (sa[i] >= longLen - shortLen + 1 + LLS) {
						continue;
					}
					else if (sa[i] < LLS) {
						continue;
					}
					else {
						if (Rabin_Karp(i, SLS, shortLen, LLS)) {
							ans++;
						}
					}
				}
			}
			printf("%d\n", ans);
        	times--;
        }
        pair--;
    }
    return 0;
}

void suffix_array()
{
    int N = totalLen;
    int A = 26;
    int *rank = temp[0];
    int *new_rank = temp[1];
    int i;
    for (i = 0; i < A; ++i) {
    	c[i] = 0;
    	alphabet[i] = 0;
    }
    for (i = 0; i < N; ++i) {
    	alphabet[t[i] - 'a']++;
    	rank[i] = t[i] - 'a';
    	c[rank[i]]++;
    }
    for (i = 1; i < A; ++i) {
    	c[i] += c[i - 1];
    	alphabet[i] = c[i];
    }
    for (i = N-1; i >= 0; --i) {
    	sa[--c[t[i] - 'a']] = i;
    }
    int n;
    for (n = 1; n < N; n *= 2) //n = 1, 2, 4, 8, 16......
    {
        for (i = 0; i < A; ++i) c[i] = 0;
        for (i = 0; i < N; ++i) c[rank[i]]++;
        for (i = 1; i < A; ++i) c[i] += c[i-1];
        int *sa2 = new_rank;
        int r = 0;
        for (i = N - n; i < N; ++i) {
            sa2[r++] = i;
        }
        for (i = 0; i < N; ++i)
            if (sa[i] >= n)
                sa2[r++] = sa[i] - n;
        for (i = N - 1; i >= 0; --i)
            sa[--c[rank[sa2[i]]]] = sa2[i];
 
        new_rank[sa[0]] = r = 0;
        for (i = 1; i < N; ++i)
        {
            if (!(rank[sa[i-1]] == rank[sa[i]] && sa[i-1]+n < N && rank[sa[i-1]+n] == rank[sa[i]+n]))
                r++;
            new_rank[sa[i]] = r;
        }
        int *a;
		a = rank;
		rank = new_rank;
		new_rank = a;
        if (r == N-1) break;
        A = r + 1;
    }
}

int Rabin_Karp(int place, int SLS, int shortLen, int LLS)
{
	int value = 0, add = 0;
	int i;
	for (i = 0; i < shortLen; i++) {
		value += t[SLS + i] - 'a';
		add += t[LLS + i] - 'a';
	}
	if (value == add) {
		for (i = 0; i < shortLen; i++) {
			if (t[SLS + i] != t[LLS + i])
				return 0;
		}
		return 1;
	}
	return 0;
}

/*void shortKMP(int shortLen, int start)
{
	short_pi[1] = 0;
	int k = 0;
	int q;
	for (q = 2; q <= shortLen; q++) {
		while (k > 0 && t[k + 1 + start] != t[q + start]) {
			k = short_pi[k];
		}
		if (t[k + 1 + start] == t[q + start]) {
			k++;
		}
		short_pi[k] = k;
	}
}

void longKMP(int longLen, int LONGstart, int SHORTstart)
{
	pi[1] = 0;
	int k = 0;
	int q;
	for (q = 2; q <= longLen; q++) {
		while (k > 0 && t[k + 1 + SHORTstart] != t[q + LONGstart]) {
			k = short_pi[k];
		}
		if (t[k + 1 + start] == t[q + start]) {
			k++;
		}
		short_pi[k] = k;
	}
}*/