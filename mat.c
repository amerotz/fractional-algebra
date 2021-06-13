#include "mat.h"

vec_t* getRow(mat_t* a, int index){
	if(index < 0 || index > a->rows) return NULL;
	return a->mat[index];	
}

num_t* matGet(mat_t* a, int i, int j){
	if(i < 0 || i > a->rows || j < 0 || j > a->cols) return NULL;
	return getNum(getRow(a, i), j);
}

bool matSet(mat_t* a, num_t* n, int i, int j){
	if(i < 0 || i > a->rows || j < 0 || j > a->cols) return false;
	setNum(getRow(a, i), j, n);
	return true;
}

vec_t* getCol(mat_t* a, int index){
	if(index < 0 || index > a->cols) return NULL;
	vec_t* v = emptyVec(a->rows);
	for(int i = 0; i < a->rows; i++){
		setNum(v, i, matGet(a, i, index));
	}
	return v;
}

mat_t* joinCol(mat_t* a, vec_t* v){
	mat_t* m = emptyMat(a->rows, a->cols+1);
	for(int i = 0; i < m->rows; i++){
		for(int j = 0; j < m->cols; j++){
			if(j < a->cols) matSet(m, matGet(a, i, j), i, j);
			else matSet(m, getNum(v, i), i, j);
		}
	}
	return m;
}

vec_t* removeCol(mat_t* a, int index){
	vec_t* v = emptyVec(a->rows);
	for(int i = 0; i < a->rows; i++){
		setNum(v, i, removeNum(getRow(a, i), index));
	}
	a->cols -= 1;
	return v;
}

bool setRow(mat_t* a, int row, vec_t* v){
	if(row < 0 || row > a->rows) return false;
	a->mat[row] = copyVec(v);
	return true;
}

mat_t* emptyMat(int r, int c){
	mat_t* m = malloc(sizeof(mat_t) + r*sizeof(vec_t*));
	m->rows = r;
	m->cols = c;
	for(int i = 0; i < r; i++){
		m->mat[i] = emptyVec(c);
	}
	return m;
}

mat_t* matFromFloat(int r, int c,float f[r][c]){
	mat_t* m = emptyMat(r, c);
	for(int y = 0; y < r; y++){
		float tmp[c];
		for(int x = 0; x < c; x++){
			tmp[x] = f[y][x];
		}
		setRow(m, y, vecFromFloat(tmp, c));
	}
	return m;
}

mat_t* matFromDouble(int r, int c, double f[r][c]){
	mat_t* m = emptyMat(r, c);
	for(int y = 0; y < r; y++){
		double tmp[c];
		for(int x = 0; x < c; x++){
			tmp[x] = f[y][x];
		}
		setRow(m, y, vecFromDouble(tmp, c));
	}
	return m;
}

mat_t* copyMat(mat_t* a){
	mat_t* b = emptyMat(a->rows, a->cols);
	for(int i = 0; i < a->rows; i++){
		setRow(b, i, getRow(a, i));
	}
	return b;
}

mat_t* transpose(mat_t* a){
	mat_t* m = emptyMat(a->cols, a->rows);
	for(int i = 0; i < m->rows; i++){
		m->mat[i] = copyVec(getCol(a, i));
	}
	return m;
}

mat_t* matOp(mat_t* a, mat_t* b, vec_t* f(vec_t*, vec_t*)){
	if(a->rows != b->rows || a->cols != b->cols) return NULL;
	mat_t* m = emptyMat(a->rows, a->cols);
	for(int i = 0; i < m->rows; i++){
		setRow(m, i, f(getRow(a, i), getRow(b, i)));
	}
	return m;
}

mat_t* addMat(mat_t* a, mat_t* b){
	return matOp(a, b, addVec);
}

mat_t* subMat(mat_t* a, mat_t* b){
	return matOp(a, b, subVec);
}

mat_t* mulMat(mat_t* a, mat_t* b){
	return matOp(a, b, mulVec);
}

mat_t* divMat(mat_t* a, mat_t* b){
	return matOp(a, b, divVec);
}

mat_t* dotMat(mat_t* a, mat_t* b){
	if(a->cols != b->rows) return NULL;
	mat_t* m = emptyMat(a->rows, b->cols);
	for(int i = 0; i < a->rows; i++){
		for(int j = 0; j < b->cols; j++){ 
			matSet(m, dotVec(getRow(a, i), getCol(b, j)), i, j); 
		}
	}
	return m;
}

vec_t* dotMatVec(mat_t* a, vec_t* b){
	if(a->cols != b->dim) return NULL;
	vec_t* v = emptyVec(a->rows);
	for(int i = 0; i < a->rows; i++){
		setNum(v, i, dotVec(getRow(a, i), b));
	}
	return v;
}

void printMat(mat_t* m, bool frac){
	printf("{");
	int i = 0;
	printVec(m->mat[i], frac);
	printf("\n");
	for(i = 1; i < m->rows-1; i++){
		printf(" ");
		printVec(m->mat[i], frac);
		printf("\n");
	}
	printf(" ");
	printVec(m->mat[i], frac);
	printf("}");
}
