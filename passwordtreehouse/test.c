#include "../tools.h"

long long int power(long long int x, int p)
{
	if (p == 1)
		return 1;
	register int i;
	for (i = p; i > 0; --i)
		x *= x;
	return x;
}

int shuffle(int i)
{
	int arr[18] = {10, 2, 15, 8, 3, 4, 5, 14, 17, 0, 16, 7, 11, 13, 9, 6, 1, 12};
	return arr[i];
}

int main()
{
register long long int x = 17;
	char q;
	for (q = 16; q > -1; --q)
		printf("%d\n", MOD(power(x,q), 17));
}

/* Generators when multiplying by 2

register long long int x = 128;
	char q;
	for (q = 64; q > -1; --q)
		printf("%lld\n", x = MOD(x <<= 1, 19));

*/
