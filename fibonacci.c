#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcion sin optimizaciones.
void invertir(char *str) {
    for (int i = 0 ; i < strlen(str) / 2 ; ++i) {
        char aux = str[i];
        str[i] = str[strlen(str) - i - 1];
        str[strlen(str) - i - 1] = aux;
    }
}

// Funcion con reduccion de llamadas a funciones.
void invertir1(char *str) {
    int lenght = strlen(str);
    char aux;
    for (int i = 0 ; i < lenght / 2 ; ++i) {
        aux = str[i];
        str[i] = str[lenght - i - 1];
        str[lenght - i - 1] = aux;
    }
}

// Funcion con loop unrolling.
void invertir2(char *str) {
    int lenght = strlen(str);
    char aux;
    char aux2;  
    for (int i = 0 ; i < (lenght / 2) ; i += 2) {        
        aux = str[i];
        aux2 = str[i+1];
        str[i] = str[lenght - i - 1];
        str[i+1] = str[lenght - i - 2];
        str[lenght - i - 1] = aux;
        str[lenght - i - 2] = aux2;
    }
}

// Funcion con reduccion de operaciones.
void invertir3(char *str) {
    int lenght = strlen(str);
    char aux, aux2, aux3, aux4;
    for (int i = 0 ; i < lenght / 2 ; i += 2) {     
        aux = str[i];
        aux2 = str[i+1];
        aux3 = lenght - i - 1;
        aux4 = aux3 - 1;
        str[i] = str[aux3];
        str[i+1] = str[aux4];
        str[aux3] = aux;
        str[aux4] = aux2;
    }
}


int main() {
    char prueba[] = "abcdefghij"; 
    // printf("original: %s\n", prueba);
    invertir(prueba);
    printf("invertir: %s\n\n", prueba);

    
    char prueba1[] = "abcdefghijk"; 
    // printf("original: %s\n", prueba1);
    invertir1(prueba1);
    printf("invertir1: %s\n\n", prueba1);

    
    char prueba2[] = "abcdefghijk"; 
    // printf("original: %s\n", prueba2);
    invertir2(prueba2);
    printf("invertir2: %s\n\n", prueba2);

    
    char prueba3[] = "abcdefghijk"; 
    // printf("original: %s\n", prueba3);
    invertir3(prueba3);
    printf("invertir3: %s\n", prueba3);

    return 0;
}