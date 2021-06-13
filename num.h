#ifndef NUM
#define NUM

#include "stdio.h"
#include "stdbool.h"

void *malloc(size_t size);
void free(void* ptr);

typedef struct Number {
	int num;
	int den;
} num_t;

int gcd(int a, int b);

int abs(int a);

int lcm(int a, int b);

num_t* copyNum(num_t* a);

num_t* simplify(num_t* a);

num_t* createNum(int n, int d);

num_t* fromFloat(float f);

num_t* fromDouble(double f);

num_t* add(num_t* a, num_t* b);

num_t* sub(num_t* a, num_t* b);

num_t* mul(num_t* a, num_t* b);

num_t* invert(num_t* a);

num_t* div(num_t* a, num_t* b);

void printNum(num_t* a, bool frac);

#endif
