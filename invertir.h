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
    int length = strlen(str);
    char aux;
    for (int i = 0 ; i < length / 2 ; ++i) {
        aux = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = aux;
    }
}


// Funcion con loop unrolling.
void invertir2(char *str) {
    int length = strlen(str);
    char aux;
    char aux2;  
    int i;
    for (i = 0 ; i < (length / 2) - 1 ; i += 2) {        
        aux = str[i];
        aux2 = str[i+1];
        str[i] = str[length - i - 1];
        str[i+1] = str[length - i - 2];
        str[length - i - 1] = aux;
        str[length - i - 2] = aux2;
    }
    if (i < (length / 2)) {
        aux = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = aux;
    }
}


// Funcion con reduccion de operaciones.
void invertir3(char *str) {
    int length = strlen(str);
    int halflength = (length / 2) - 1;
    char aux, aux2;
    int i, j;
    for (i = 0, j = length-1 ; i < halflength ; i += 2, j -= 2) {
        aux = str[i];
        aux2 = str[i+1];
        str[i] = str[j];
        str[i+1] = str[j-1];
        str[j] = aux;
        str[j-1] = aux2;
    }
    if (i < halflength + 1) {
        aux = str[i];
        str[i] = str[j];
        str[j] = aux;
    }
}