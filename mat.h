#ifndef MAT
#define MAT

#include "num.h"
#include "vec.h"

typedef struct Mat {
	int rows;
	int cols;
	vec_t* mat[];
} mat_t;

vec_t* getRow(mat_t* a, int index);

num_t* matGet(mat_t* a, int i, int j);

bool matSet(mat_t* a, num_t* n, int i, int j);

vec_t* getCol(mat_t* a, int index);

mat_t* joinCol(mat_t* a, vec_t* v);

vec_t* removeCol(mat_t* a, int index);

bool setRow(mat_t* a, int row, vec_t* v);

mat_t* emptyMat(int r, int c);

mat_t* matFromFloat(int r, int c,float f[r][c]);

mat_t* matFromDouble(int r, int c, double f[r][c]);

mat_t* copyMat(mat_t* a);

mat_t* transpose(mat_t* a);

mat_t* matOp(mat_t* a, mat_t* b, vec_t* f(vec_t*, vec_t*));

mat_t* addMat(mat_t* a, mat_t* b);

mat_t* subMat(mat_t* a, mat_t* b);

mat_t* mulMat(mat_t* a, mat_t* b);

mat_t* divMat(mat_t* a, mat_t* b);

mat_t* dotMat(mat_t* a, mat_t* b);

vec_t* dotMatVec(mat_t* a, vec_t* b);

void printMat(mat_t* m, bool frac);

#endif
