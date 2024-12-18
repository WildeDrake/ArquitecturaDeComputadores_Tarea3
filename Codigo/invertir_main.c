#include <stdio.h>
#include "invertir.h"

int main() {
    char prueba[] = "abcdefg"; 
    // printf("original: %s\n", prueba);
    invertir(prueba);
    printf("invertir0: %s\n\n", prueba);

    
    char prueba1[] = "abcdefg"; 
    // printf("original: %s\n", prueba1);
    invertir1(prueba1);
    printf("invertir1: %s\n\n", prueba1);

    
    char prueba2[] = "abcdefg"; 
    // printf("original: %s\n", prueba2);
    invertir2(prueba2);
    printf("invertir2: %s\n\n", prueba2);

    
    char prueba3[] = "abcdefg"; 
    // printf("original: %s\n", prueba3);
    invertir3(prueba3);
    printf("invertir3: %s\n", prueba3);

    return 0;
}