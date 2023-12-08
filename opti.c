#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

double perfomanceCounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart-b->QuadPart)/(double)freq.QuadPart;
}

void psum1(float a[], float p[], long int n) {
    long int i;
    p[0] = a[0];
    for (i=1; i<n; i++){
        p[i] = p[i-1] + a[i];
    }
}

void psum2(float a[], float p[], long int n) {
    long int i;
    p[0] = a[0];
    for (i = 1; i < n-1; i+=2) {
        float mid_val = p[i-1] + a[i];
        p[i] = mid_val;
        p[i+1] = mid_val + a[i+1];
    }
    if (i < n) p[i] = p[i-1] + a[i];
}

int main() {
    long int i, j, n;
    float aux, vector[260000], res[260000];
    double secs;
    LARGE_INTEGER t_ini, t_fin;
    clock_t ini,fin;
    srand(time(NULL));
    for(j=1; j<=25; j++) {
        n=10000*j;
        for(i=0; i < n; i++) {
                aux = (float)rand()/RAND_MAX;
                //printf("\nvector[%d]=%f", i, aux);
                vector[i]=aux;
        }

        QueryPerformanceCounter(&t_ini);
        //ini=clock();
        psum2(vector, res, n);
        //fin=clock();
        QueryPerformanceCounter(&t_fin);
        secs=perfomanceCounter_diff(&t_fin, &t_ini);
        printf("\nResultado [%d] = %f Milisegundos: %.16g", n, res[n-1], secs*1000.0);

        printf("\n%d",fin-ini);
    }
    return 0;
}
