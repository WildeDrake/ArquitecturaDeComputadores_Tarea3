#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long int lli;

lli fibonacci_OP(lli n) {
    lli f0 = 0, f1 = 1, f2 = 1,f3 = 2, f2_cp;
    for(lli i = 4 ; i < n ; i += 4){
        f2_cp = f2;

        f0 = f2 + f3;
        f1 = f2 + f3 * 2;
        f2 = f2 * 2 + f3 * 3;
        f3 = f2_cp * 3 + f3 * 5;
    }

    switch(n%4) {
        case 1:
            return f0;
            break;
        case 2:
            return f1;
            break;
        case 3:
            return f2;
            break;
        case 0:
            return f3;
            break;
    }

    return -1;
}

int main(int argc, char const *argv[]){
    
    if (argc < 2 || argc > 4) {
        printf("Uso %s <valor maximo> <intervalo. Def=200> <Número de experimentos. Def=20>\n", argv[0]);
        return 1;
    }

    lli max = atoll(argv[1]);
    lli N_exp = 20;
    lli intervalo = 200;
    if (argc == 3) intervalo = atoll(argv[2]);
    if (argc == 4) N_exp = atoll(argv[3]);

    printf("n,tiempo_[s]\n");
    for(lli i = 1; i <= max; i+=intervalo) {
        
        double time_spent = 0;
        
        for(int j = 0; j < N_exp; j++) {
            lli n = i;
            
            clock_t start = clock();
            fibonacci_OP(n);
            clock_t end = clock();

            time_spent += (double)(end - start) / CLOCKS_PER_SEC;
        }

        printf("%lld,%f\n", i, time_spent/N_exp);
    }
    return 0;
}