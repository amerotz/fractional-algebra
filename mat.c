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

mat_t* gaussElim(mat_t* a){
	mat_t* m = copyMat(a); 
	for(int i = 0; i < a->rows; i++){
		vec_t* r = getRow(m, i);
		num_t* pivot = getNum(r, i);
		for(int j = i+1; j < a->rows; j++){
			vec_t* s = getRow(m, j);
			num_t* coeff = div(getNum(s, i), pivot);
			vec_t* res = subVec(s, mulVecScalar(r, coeff));
			setRow(m, j, res);
		}
	}
	return m;
}

mat_t* jordan(mat_t* a){
	mat_t* m = copyMat(a);
	int col = a->cols-1;
	for(int i = m->rows-1; i > -1; i--){
		vec_t* r = getRow(m, i);
		num_t* pivot = getNum(r, col);
		for(int j = i-1; j > -1; j--){
			vec_t* s = getRow(m, j);
			num_t* coeff = div(getNum(s, col), pivot);
			vec_t* res = subVec(s, mulVecScalar(r, coeff));
			setRow(m, j, res);
		}
		col--;
	}
	col = a->cols-1;
	for(int i = m->rows-1; i > -1; i--){
		vec_t* r = getRow(m, i);
		num_t* pivot = getNum(r, col);
		if(!zero(pivot)) setRow(m, i, divVecScalar(r, pivot));
		col--;
	}
	return m;
}

vec_t* upperSolve(mat_t* A, vec_t* b){
	vec_t* x = emptyVec(b->dim);
	int n = b->dim-1;
	setNum(x, n, div(getNum(b, n), matGet(A, n, n)));
	for(int i = n; i > -1; i--){
		num_t* sum = createNum(0, 1);
		for(int j = i+1; j <= n; j++){
			sum = add(sum, mul(matGet(A, i, j), getNum(x, j)));
		}
		setNum(x, i, div(sub(getNum(b, i), sum), matGet(A, i, i)));
	}
	return x;
}

vec_t* solve(mat_t* a, vec_t* b){
	mat_t* A = joinCol(a, b);
	A = gaussElim(A);
	vec_t* B = removeCol(A, A->cols-1);
	return upperSolve(A, B);
}

mat_t* identity(int rows, int cols){
	mat_t* m = emptyMat(rows, cols);
	for(int i = 0; i < m->rows; i++) matSet(m, createNum(1, 1), i, i);
	return m;
}

mat_t* joinMat(mat_t* a, mat_t* b){
	int r = a->rows > b->rows ? a->rows : b->rows;
	int c = a->cols + b->cols;
	mat_t* m = emptyMat(r, c);
	for(int i = 0; i < a->rows; i++){
		for(int j = 0; j < a->cols; j++){
			matSet(m, matGet(a, i, j), i, j);
		}
	}
	for(int i = 0; i < b->rows; i++){
		for(int j = 0; j < b->cols; j++){
			matSet(m, matGet(b, i, j), i, j+a->cols);
		}
	}
	return m;
}

mat_t* splitMat(mat_t* a, int col1, int col2){
	mat_t* m = emptyMat(a->rows, col2-col1);
	for(int i = 0; i < a->rows; i++){
		for(int j = col1; j < col2; j++){
			matSet(m, matGet(a, i, j), i, j-col1);
		}
	}
	return m;
}

mat_t* inverse(mat_t* m){
	mat_t* I = identity(m->rows, m->cols);

	mat_t* M = joinMat(m, I);
	M = gaussElim(M);

	mat_t* inv = splitMat(M, M->cols/2, M->cols);
	mat_t* src = splitMat(M, 0, M->cols/2);

	M = joinMat(inv, src);
	M = jordan(M);
	mat_t* res = splitMat(M, 0, M->cols/2);
	return res;
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
