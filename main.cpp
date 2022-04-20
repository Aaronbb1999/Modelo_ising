#include "functions.h"
#include <stdio.h>
#include "math.h"
#include "gsl_rng.h"

gsl_rng *tau;


int main()
{
    double x,T;
    int i,j,k,N=50,v=0,iter;
    int s[N][N];
    extern gsl_rng *tau;

    FILE *f;
    fopen("Resultados.dat","w");

    int semilla=132456;
    tau=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau,semilla);

    //x=gsl_rng_uniform(tau);
    //i=gsl_rng_uniform_int(tau,100);

    //Configuración inicial
    printf("Para configuración aleatoria pulse 1:");
    scanf("%i",&v);
    printf("Numero de iteraciones:");
    scanf("%i",&iter);
    printf("Temperatura [0,5]:");
    scanf("%lf",&T);

    config_inicial(s,N,v);

    for(i=0;i<iter;i++)
    {
        for(j=0;j<N;j++)
        {
            for(k=0;k<N;k++)
            {
                fprintf(f,"&i ",s[j][k]);
            }
            fprintf(f,"/n");
        }
        fprintf(f,"/n");

        Metropolis(s,N,T);
    }

    
    

    return 0;
}