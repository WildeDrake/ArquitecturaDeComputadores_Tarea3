#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define IDENT 1
#define OP    *

typedef float data_t;

typedef struct {
    long int len;
    data_t *data;
} vec_rec, *vec_ptr;

/* Create vector of specified length */
 vec_ptr new_vec(int len) {
    /* allocate header structure */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    if (!result) return NULL; /* Couldn’t allocate storage */
    result->len = len;
    /* Allocate array */
    if (len > 0) {
        data_t *data = (data_t *)calloc(len, sizeof(data_t));
        if (!data) {
            free((void *) result);
            return NULL; /* Couldn’t allocate storage */
        }
        result->data = data;
    } else result->data = NULL;
    return result;
}

data_t *get_vec_start(vec_ptr v){
    return v->data;
}

/*
 * Retrieve vector element and store at dest.
 * Return 0 (out of bounds) or 1 (successful)
*/
int get_vec_element(vec_ptr v, int index, data_t *dest) {
    if (index < 0 || index >= v->len) return 0;
    *dest = v->data[index];
    return 1;
}

/*
 * Put vector element and store at vector.
 * Return 0 (out of bounds) or 1 (successful)
*/

int put_vec_element(vec_ptr v, int index, data_t data) {
    if (index < 0 || index >= v->len) return 0;
    v->data[index] = data;
    return 1;
}

/* Return length of vector */
int vec_length(vec_ptr v) {
    return v->len;
}

/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest) {
    int i;
    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
        printf("alb");
    }
}

void combine3(vec_ptr v, data_t *dest) {
    int i;
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);
    *dest = 0;
    for (i = 0; i < length; i++) {
        *dest = *dest + data[i];
    }
}

int main() {
    vec_ptr vector;
    data_t aux;
    int i, n;
    data_t res;
    int hora=time(NULL);    
    srand(hora);    
    printf("\n Ingrese cantidad de elementos del arreglo:");
    scanf("%d",&n);
    vector = new_vec(n);
    srand(hora);
     if(vector!=NULL) {
        for(i=0; i < vec_length(vector); i++) {
            aux = rand()/RAND_MAX;
            put_vec_element(vector,i,aux);
        }
        clock_t start=clock();
        combine1(vector, &res);
        clock_t end=clock();
        printf("\nResultado=%f\nEjecucion de combine1 desde %d hasta %d\nCiclos transcurridos:%f", res, start, end,/*CLOCKS_PER_SEC*/ end-start);
        start=clock();
        combine3(vector, &res);
        end=clock();
        printf("\nResultado=%f\nEjecucion de combine3 desde %d hasta %d\nCiclos transcurridos:%f", res, start, end,/*CLOCKS_PER_SEC*/ end-start);

     } else
        printf("\n\nNose pudo crear el arreglo!!");
    return 0;
}
