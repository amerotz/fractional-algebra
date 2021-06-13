#ifndef VEC
#define VEC

#include "num.h"

typedef struct Vec {
	int dim;
	num_t* vec[];
} vec_t;

vec_t* emptyVec(int n);

bool setNum(vec_t* a, int index, num_t* n);

num_t* getNum(vec_t* a, int index);

num_t* removeNum(vec_t* a, int index);

vec_t* copyVec(vec_t* a);

vec_t* vecFromFloat(float f[], int n);

vec_t* vecFromDouble(double f[], int n);

vec_t* addVec(vec_t* a, vec_t* b);

vec_t* subVec(vec_t* a, vec_t* b);

vec_t* mulVec(vec_t* a, vec_t* b);

vec_t* mulVecScalar(vec_t* a, num_t* n);

vec_t* divVec(vec_t* a, vec_t* b);

vec_t* hadamard(vec_t* a, vec_t* b);

num_t* dotVec(vec_t* a, vec_t* b);

void printVec(vec_t* v, bool frac);

#endif
