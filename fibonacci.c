#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long int lli;

long long int fibonacci(long long int *n) {
    if (*n == 1) return 0;
    if (*n == 2) return 1;
    long long int m = *n - 1;
    long long int p = *n - 2;
    return fibonacci(&m) + fibonacci(&p);
}

int main(int argc, char const *argv[]){
    
    if (argc < 2 || argc > 3) {
        printf("Uso %s <valor maximo> <Número de experimentos. Def=20>\n", argv[0]);
        return 1;
    }

    lli max = atoll(argv[1]);
    lli N_exp = 20;
    if (argc == 3) N_exp = atoll(argv[2]);


    printf("n,tiempo_[s]\n");
    for(lli i = 1; i <= max; i++) {
        
        double time_spent = 0;
        
        for(int j = 0; j < N_exp; j++) {
            lli n = i;
            
            clock_t start = clock();
            fibonacci(&n);
            clock_t end = clock();

            time_spent += (double)(end - start) / CLOCKS_PER_SEC;
        }

        printf("%lld,%f\n", i, time_spent/N_exp);
    }


    return 0;
}