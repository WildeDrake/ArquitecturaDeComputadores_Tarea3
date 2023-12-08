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
        arreglo[i] = (char)(rand() % 256);
    }
    arreglo[tamArr - 1] = '\0';
}

int main(int argc, char const *argv[]){
    
    if (argc < 2 || argc > 3) {
        printf("Uso %s <Tamano de la palabra> <Numero de experimentos>\n", argv[0]);
        return 1;
    }
    int tamArray = atoi(argv[1]);
    int N_exp = atoi(argv[2]);
    
    char* Array = getArr(tamArray);
    int time0 = 0, time1 = 0, time2 = 0, time3 = 0;

    for(int i = 0 ; i < N_exp ; i++) {

        clock_t start = clock();
        invertir(Array);
        clock_t end = clock();
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

    printf("%d; %d; %d; %d; %d\n", tamArray, time0/N_exp, time1/N_exp, time2/N_exp, time3/N_exp);

    return 0;
}