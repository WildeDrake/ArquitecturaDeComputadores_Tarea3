#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long int lli;

lli fibonacci_OP(lli n) {

    if (n == 1) return 0;
    if (n == 2) return 1;

    n-=2; //desplazamiento para calcular a partir de n=3

    lli f0=0,f1=1,fib[4];
    for(lli i=0;i<n;i+=4){
        fib[0]=f0 + f1;
        fib[1]=f0 + f1*2;
        fib[2]=f0*2 + f1*3;
        fib[3]=f0*3 + f1*5;
        f0=fib[2];
        f1=fib[3];
    }

    return fib[n%4];
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
