#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define IDENT 1
#define OP *
typedef float data_t;

double perfomanceCounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart-b->QuadPart)/(double)freq.QuadPart;
}

typedef struct {
    long int len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(int len) {
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    if (!result) return NULL;
    result->len = len;
    if (len > 0) {
        data_t *data = (data_t *)calloc(len, sizeof(data_t));
        if (!data) {
            free((void *) result);
            return NULL;
        }
        result->data = data;
    } else result->data = NULL;
    return result;
}

data_t *get_vec_start(vec_ptr v){
    return v->data;
}

int get_vec_element(vec_ptr v, int index, data_t *dest) {
    if (index < 0 || index >= v->len) return 0;
    *dest = v->data[index];
    return 1;
}

int put_vec_element(vec_ptr v, int index, data_t data) {
    if (index < 0 || index >= v->len) return 0;
    v->data[index] = data;
    return 1;
}

int vec_length(vec_ptr v) {
    return v->len;
}

///////////////////////////////////////////////////////////////////////////

// Funcion no optimizada.
void combine1(vec_ptr v, data_t *dest) {
    int i;
    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

// Funcion que reduce las llamadas de vec_lenght de n veces a sólo una vez.

void combine2(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);

    *dest = IDENT;
    for(i = 0; i < length ; i++){
        data_t val;
        get_vec_element(v,i,&val);
    }
    *dest = *dest OP val;
}

// Funcion con reduccion de llamadas a funciones.
void combine3(vec_ptr v, data_t *dest) {
    int i;
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);
    *dest = 0;
    for (i = 0 ; i < length ; i++) {
        *dest = *dest OP data[i];
    }
}

// Funcion que elimina el uso del puntero *dest dentro del ciclo (Reduciendo las referencias a memoria)

void combine4(vec_ptr v, data_t *dest) {
    long int i, length = vec_length(v);
    data_t *data = get_vec_start(v), acc = IDENT;
    for (i = 0; i < length; i++){
        acc = acc OP data[i];
        *dest = acc;
    }
}

// Funcion con loop unrolling de 4 operaciones.
void combine5(vec_ptr v, data_t *dest) {
    long int i, length = vec_length(v);
    data_t *data = get_vec_start(v), acc = IDENT;
    for (i = 0; i < length; i+=4){
        acc = acc OP ((data[i] OP data[i+1]) OP (data[i+2] OP data[i+3]));
    }
    for ( ; i < length; i++){
        acc = acc OP data[i];
    }
    *dest = acc;
}

// Funcion con paralelismo de 4 vias.
void combine6(vec_ptr v, data_t *dest) {
    int i;
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t resultado1 = IDENT;
    data_t resultado2 = IDENT;
    data_t resultado3 = IDENT;
    data_t resultado4 = IDENT;
    for (i = 0 ; i < length ; i += 4) {
        resultado1 = resultado1 OP data[i];
        resultado2 = resultado2 OP data[i+1];
        resultado3 = resultado3 OP data[i+2];
        resultado4 = resultado4 OP data[i+3];
    }
    for ( ; i < length ; i++) {
        resultado1 = resultado1 OP data[i];
    }
    *dest = resultado1 OP resultado2 OP resultado3 OP resultado4;
}

///////////////////////////////////////////////////////////////////////////

int main() {
    double secs, sum_secs=0.0;
    LARGE_INTEGER t_ini, t_fin;
    int hora=time(NULL);
    vec_ptr vector;
    data_t aux;
    int i, k, n, m;
    data_t res;
    printf("\n Ingrese cantidad de elementos del arreglo:");
    scanf("%d",&n);
    vector = new_vec(n);
    srand(hora);
     if(vector!=NULL) {
        for(i=0; i < vec_length(vector); i++) {
            aux = rand()%10;
            put_vec_element(vector,i,(data_t)aux);
        }

       /*for(i=0; i < vec_length(vector); i++) {
            get_vec_element(vector,i,&aux);
            printf("\nvector[%d]=%f",i,aux);
        }*/
        printf("\n Prueba para combine1: ");
        printf("\n Ingrese cantidad pruebas con %d elementos:",n);
        scanf("%d",&m);

        for(k=0; k<m; k++) {
            res=0;
            QueryPerformanceCounter(&t_ini);
            combine1(vector, &res);
            QueryPerformanceCounter(&t_fin);
            secs=perfomanceCounter_diff(&t_fin, &t_ini);
            printf("\nResultado [%d] = %f Milisegundos: %.16g", vec_length(vector), res, secs*1000.0);
            sum_secs=sum_secs+secs;
        }
        printf("\nResultado [%d] = %f Milisegundos: %.16g", vec_length(vector), res, sum_secs*1000.0/m);

        sum_secs = 0.0;secs=0;
        printf("\n Prueba para combine5: ");
        printf("\n Ingrese cantidad pruebas con %d elementos:",n);
        scanf("%d",&m);
        for(k=0; k<m; k++) {
            res=0;
            QueryPerformanceCounter(&t_ini);
            combine5(vector, &res);
            QueryPerformanceCounter(&t_fin);
            secs=perfomanceCounter_diff(&t_fin, &t_ini);
            printf("\nResultado [%d] = %f Milisegundos: %.16g", vec_length(vector), res, secs*1000.0);
            sum_secs=sum_secs+secs;
        }
        printf("\nResultado [%d] = %f Milisegundos: %.16g", vec_length(vector), res, sum_secs*1000.0/m);
     } else
        printf("\n\nNose pudo crear el arreglo!!");
    return 0;
}
