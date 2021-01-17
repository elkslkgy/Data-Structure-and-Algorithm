#include <stdio.h>
#include <stdlib.h>

int Q, L, T;
//Q:how many requests	L:machines' names	T:change how many times
int a, b, c, d ;
int c_seed = 0, s_seed = 0;
char cmd;
int s[5] = {0};
long long int mac[16777216] = {0};
long long int k = 1;

void next_request();

int main()
{
	scanf("%d%d%d%d%d%d%d", &Q, &L, &T, &a, &b, &c, &d);
	int i;
	long long int S = 0, X = 0;
	int q = 0;
	for ( i = 1; i <= Q; i++ ) {
		if ( (!q) && T ) {
			scanf("%d", &q);
			T--;
		}
		if ( q == i ) {
			scanf("%d%d%d%d", &a, &b, &c, &d);
			c_seed = s_seed = 0;
			q = 0;
		}
		next_request();
		long long int ans = 0;
		ans = (s[0] << 18) + (s[1] << 12) + (s[2] << 6) + s[3];
		if ( cmd == 'A' ) {
			mac[ans] |= (k << s[4]);
		}
		if ( cmd == 'C' ) {
			if ( (mac[ans] >> s[4]) & 1 ) {
				S += i;
				X ^= i;
			}
		}
	}
	printf("%lld %lld\n", S, X);
	return 0;
}

void next_request()
{
	c_seed = ( c_seed * a + b ) & 255;
	cmd = "AC" [ c_seed & 1 ];
	// don’t forget to allocate memory for s
	int i;
	for ( i = 0; i < L; i++ ) {
		s_seed = ( s_seed * c + d ) & 1023;
		s[i] = ( s_seed >> 3 ) & 63;
	}
	return;
}