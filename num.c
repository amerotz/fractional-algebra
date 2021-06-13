#include "num.h"

int gcd(int a, int b){
	int tmp;            	
	while(b != 0){      	
        	tmp = a;
		a = b;      	
		b = tmp % b;	
	}
	return a;
}

int abs(int a){
	return a > 0 ? a : -a;
}

int lcm(int a, int b){
	int g = gcd(a, b);
	int lcm = abs(a*b)/g;
	return lcm;
}

num_t* copyNum(num_t* a){
	num_t* b = malloc(sizeof(num_t));
	b->num = a->num;
	b->den = a->den;
	return b;
}

num_t* simplify(num_t* a){
	int g = gcd(a->num, a->den);
	a->num /= g;
	a->den /= g;	
	return a;
}

num_t* createNum(int n, int d){
	num_t* a = malloc(sizeof(num_t));
	a->num = n;
	a->den = d;
	return simplify(a);
}

num_t* fromFloat(float f){
	int d = 1;
	while((f - (int) f) != 0) {
		f *= 10;
		d *= 10;
	}
	return createNum((int) f, d);
}

num_t* fromDouble(double f){
	int d = 1;
	while((f - (int) f) != 0) {
		f *= 10;
		d *= 10;
	}
	return createNum((int) f, d);
}

num_t* add(num_t* a, num_t* b){
	int mul = lcm(a->den, b->den);
	int n = a->num*mul/a->den + b->num*mul/b->den;
	num_t* c = createNum(n, mul);
	return simplify(c);
}

num_t* sub(num_t* a, num_t* b){
	int mul = lcm(a->den, b->den);
	int n = a->num*mul/a->den - b->num*mul/b->den;
	num_t* c = createNum(n, mul);
	return simplify(c);
}

num_t* mul(num_t* a, num_t* b){
	int nn = (a->num)*(b->num);
	int dd = (a->den)*(b->den);
	num_t* c = createNum(nn, dd);
	return simplify(c);
}

num_t* invert(num_t* a){
	return createNum(a->den, a->num);
}

num_t* div(num_t* a, num_t* b){
	return mul(a, invert(b));
}

void printNumFloat(num_t* a){
	float n = a->num/(float)a->den;
	printf("%f", n);
}

void printNumFrac(num_t* a){
	printf("%d/%d", a->num, a->den);
}

void printNum(num_t* a, bool frac){
	frac ? printNumFrac(a) : printNumFloat(a);
}
