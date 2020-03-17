#include "prime.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* This function calculates (ab)%c */
int modulo(int a, int b, int c) {
	long long x = 1, y = a; // long long is taken to avoid overflow of intermediate results
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x * y) % c;
		}
		y = (y * y) % c; // squaring the base
		b /= 2;
	}
	return x % c;
}

/* this function calculates (a*b)%c taking into account that a*b might overflow */
long long mulmod(long long a, long long b, long long c) {
	long long x = 0, y = a % c;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x + y) % c;
		}
		y = (y * 2) % c;
		b /= 2;
	}
	return x % c;
}

// Miller-Rabin primality test, iteration signifies the accuracy of the test
bool prime_test(uint64_t n, int iteration) {
	if (n < 2) {
		return false;
	}
	if (n != 2 && n % 2 == 0) {
		return false;
	}
	long long s = n - 1;
	while (s % 2 == 0) {
		s /= 2;
	}
	for (int i = 0; i < iteration; i++) {
		long long a = rand() % (n - 1) + 1, temp = s;
		long long mod = modulo(a, temp, n);
		while (temp != n - 1 && mod != 1 && mod != n - 1) {
			mod = mulmod(mod, mod, n);
			temp *= 2;
		}
		if (mod != n - 1 && temp % 2 == 0) {
			return false;
		}
	}
	return true;
}

uint64_t prime_next(uint64_t n)
{
	int is_prime = 0;
	for (uint32_t i = n; i < 2 * n; ++i)
	{
		if (prime_test(i, 5))
			return i;
	}
	fprintf(stderr, "Failed to find prime following %d", n);
	return n;
}
