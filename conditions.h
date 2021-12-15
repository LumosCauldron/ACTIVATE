#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "tools.h"
// Number conditions
char numeq(int a, int b)  {	return a == b; 	}
char numneq(int a, int b) {	return a != b; 	}
char numgt(int a, int b)  {	return a > b; 	}
char numgte(int a, int b) {	return a >= b; 	}
char numlt(int a, int b)  {	return a < b; 	}
char numlte(int a, int b) {	return a <= b; 	}
char numgtby(int a, int b, int diff)  { return (a - diff) == b; }
char numltby(int a, int b, int diff)  { return (a + diff) == b; }
char numeven(int a) { return ((MOD(a, 2)) == 0); }
char numodd(int a)  { return ((MOD(a, 2)) != 0); }
char numdivisibleby(int a, int divisor)    { return (MOD(a, divisor) == 0); }
char numnotdivisibleby(int a, int divisor) { return (MOD(a, divisor) != 0); }

// Remainder conditions
char isrmeq(int a, int b, int val)  { return ((MOD(a, b)) == val); }
char isrmneq(int a, int b, int val) { return ((MOD(a, b)) != val); }
char isrmgt(int a, int b, int val)  { return ((MOD(a, b)) > val); }
char isrmgte(int a, int b, int val) { return ((MOD(a, b)) >= val); }
char isrmlt(int a, int b, int val)  { return ((MOD(a, b)) < val); }
char isrmlte(int a, int b, int val) { return ((MOD(a, b)) <= val); }
char isrmgtby(int a, int b, int val, int diff) { return (((MOD(a, b)) - diff) == val); }
char isrmltby(int a, int b, int val, int diff) { return (((MOD(a, b)) + diff) == val); }
char isrmeven(int a, int b, int val) { return (MOD((MOD(a, b)), 2) == 0); }
char isrmodd(int a, int b, int val)  { return (MOD((MOD(a, b)), 2) != 0); }
char isrmdivisibleby(int a, int b, int val)    { return (MOD((MOD(a, b)), val) == 0); }
char isrmnotdivisibleby(int a, int b, int val) { return (MOD((MOD(a, b)), val) != 0); }

#endif
