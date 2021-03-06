/*
	SQRT_MOD
	tested
*/
#include <bits/stdc++.h>
using namespace std;

int extgcd(int a, int b, int &x, int &y){
	int g = a; x = 1; y = 0;
	if (b != 0){
		g = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	return g;
}

//	Jacobi Symbol (m/n), m,n>=0  and n is odd
//	(m/n)==1 || x^2 == m (mod n) solvable, -1 unsolvable
#define NEGPOW(e) ((e) % 2 ? -1 : 1)
int powMod(int a, int b, int p) {
	int res = 1;
	while (b)
		if (b & 1)
			res = int (res * 1ll * a % p),  --b;
		else
			a = int (a * 1ll * a % p),  b >>= 1;
	return res;
}
int invMod(int a, int m) {
	int x, y;
	if (extgcd(a, m, x, y) == 1) 
		return (x + m) % m;
	else return 0; // unsolvable
}
int jacobi(int a, int m) {
	if (a == 0) return m == 1 ? 1 : 0;
	if (a % 2)  return NEGPOW((a-1)*(m-1)/4)*jacobi(m%a, a);
	else return NEGPOW((m*m-1)/8)*jacobi(a/2, m);
}
//	find x: x2 = n (mod p) p is prime
//	No solution when: n(p-1)/2 = -1 mod p
int sqrtMod(int n, int p) { 
	int S, Q, W, i, m = invMod(n, p);
	for (Q = p - 1, S = 0; Q % 2 == 0; Q /= 2, ++S);
	do { W = rand() % p; } 
	while (W == 0 || jacobi(W, p) != -1);
	for (int R = powMod(n, (Q+1)/2, p), V = powMod(W, Q, p); ;) {
		int z = R * R * m % p;
		for (i = 0; i < S && z % p != 1; z *= z, ++i);
		if (i == 0) return R;
		R = (R * powMod(V, 1 << (S-i-1), p)) % p;
	}
}

void test_SQRT_MOD(){
	assert(sqrtMod(4,7)==2);
	assert(sqrtMod(6,5)==1);
	assert(sqrtMod(8,7)==1);
	assert(sqrtMod(1,5)==1);
	cout<<"DONE\n";
}
int main(){
	test_SQRT_MOD();
	return 0;
}
