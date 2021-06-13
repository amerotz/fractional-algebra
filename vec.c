#include "vec.h"

vec_t* emptyVec(int n){
	vec_t* v = malloc(sizeof(vec_t) + n*sizeof(num_t*));
	v->dim = n;
	for(int i = 0; i < n; i++){
		setNum(v, i, createNum(0, 1));
	}
	return v;
}

bool setNum(vec_t* a, int index, num_t* n){
	if(index < 0 || index > a->dim) return false;
	a->vec[index] = copyNum(n);
	return true;
}

num_t* getNum(vec_t* a, int index){
	if(index < 0 || index > a->dim) return NULL;
	return a->vec[index];
}

num_t* removeNum(vec_t* a, int index){
	if(index < 0 || index > a->dim) return NULL;
	vec_t* x = emptyVec(a->dim-1);
	num_t* n;
	int j = 0;
	for(int i = 0; i < a->dim; i++){
		if(i == index) {
			n = copyNum(getNum(a, index));
		}
		else{
			setNum(x, j, getNum(a, i));
			j++;
		}
	}
	free(a);
	a = copyVec(x);
	return n;
}

vec_t* copyVec(vec_t* a){
	int n = a->dim;
	vec_t* v = emptyVec(a->dim);
	for(int i = 0; i < n; i++){
		setNum(v, i, a->vec[i]);
	}
	return v;
}

vec_t* vecFromFloat(float f[], int n){
	vec_t* v = emptyVec(n);
	for(int i = 0; i < n; i++){
		setNum(v, i, fromFloat(f[i]));
	}
	return v;
}

vec_t* vecFromDouble(double f[], int n){
	vec_t* v = emptyVec(n);
	for(int i = 0; i < n; i++){
		setNum(v, i, fromDouble(f[i]));
	}
	return v;
}

vec_t* vecOp(vec_t* a, vec_t* b, num_t* f(num_t*, num_t*)){
	if(a->dim != b->dim) return NULL;
	int n = a->dim;
	vec_t* v = emptyVec(n);
	for(int i = 0; i < n; i++){
		setNum(v, i, f(getNum(a, i), getNum(b, i)));
	}	
	return v;
}

vec_t* addVec(vec_t* a, vec_t* b){
	return vecOp(a, b, add);
}

vec_t* subVec(vec_t* a, vec_t* b){
	return vecOp(a, b, sub);
}

vec_t* mulVec(vec_t* a, vec_t* b){
	return vecOp(a, b, mul);
}

vec_t* mulVecScalar(vec_t* a, num_t* b){
	int n = a->dim;
	vec_t* v = emptyVec(n);
	for(int i = 0; i < n; i++){
		setNum(v, i, mul(getNum(a, i), b));
	}	
	return v;
}

vec_t* divVec(vec_t* a, vec_t* b){
	return vecOp(a, b, div);
}

vec_t* hadamard(vec_t* a, vec_t* b){
	return mulVec(a, b);
}

num_t* dotVec(vec_t* a, vec_t* b){
	if(a->dim != b->dim) return NULL;
	int n = a->dim;
	num_t* c = createNum(0, 1);
	for(int i = 0; i < n; i++){
		c = add(c, mul(getNum(a, i), getNum(b, i)));
	}
	return c;
}

void printVec(vec_t* v, bool frac){
	printf("[");
	int i;
	for(i = 0; i < v->dim-1; i++){
		printNum(v->vec[i], frac);
		printf(", ");
	}
	printNum(v->vec[i], frac);
	printf("]");
}
