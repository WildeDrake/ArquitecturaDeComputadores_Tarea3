#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "invertir.h"

char* getArr(int tamArr) {
    char* arreglo = (char*)malloc((tamArr + 1) * sizeof(char));
    if (arreglo == NULL) {
        printf("Error al asignar memoria para el arreglo.\n");
        return NULL;
    }
    srand(time(NULL));
    for (int i = 0; i < tamArr; i++) {
        arreglo[i] = 'a' + rand()%31;
    }
    arreglo[tamArr] = '\0';
    return arreglo;
}

int main(int argc, char const *argv[]){
    
    if (argc < 2 || argc > 3) {
        printf("Uso %s <Tamano de la palabra> <Numero de experimentos>\n", argv[0]);
        return 1;
    }
    int tamArray = atoi(argv[1]);
    int N_exp = atoi(argv[2]);
    char* Array = getArr(tamArray);
    double time0 = 0, time1 = 0, time2 = 0, time3 = 0;
    clock_t start; clock_t end;
    for(int i = 0 ; i < N_exp ; i++) {
        start = clock();
        invertir(Array);
        end = clock();
        time0 += (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        invertir1(Array);
        end = clock();
        time1 += (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        invertir2(Array);
        end = clock();
        time2 += (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        invertir3(Array);
        end = clock();
        time3 += (double)(end - start) / CLOCKS_PER_SEC;
    }
    printf("%d; %f; %f; %f; %f\n", tamArray, time0/N_exp, time1/N_exp, time2/N_exp, time3/N_exp);

    if (Array != NULL) free(Array);
    return 0;
}