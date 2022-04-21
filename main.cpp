#include <stdio.h>
#include "math.h"
#include "gsl_rng.h"

gsl_rng *tau;


int main()
{
    double T,p,et;
    int i,j,k,N=40,v=0,iter,aux;
    int nd,na,md,ma,E,n,m;
    int s[N][N];
    extern gsl_rng *tau;

    FILE *f;
    f=fopen("Resultados.dat","w");

    int semilla=162456;
    tau=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau,semilla);


    //Configuración inicial
    printf("Para configuracion ordenada pulse 1:");
    scanf("%i",&v);
    printf("Numero de iteraciones:");
    scanf("%i",&iter);
    printf("Temperatura [0,5]:");
    scanf("%lf",&T);

    //Tomamos un estado inicial ordenado o desordenado
    if(v==1)
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                s[i][j]=1;
            }
        }
    }
    else
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                aux=gsl_rng_uniform_int(tau,2);
                if(aux==0)
                {
                    s[i][j]=-1;
                }
                else
                {
                    s[i][j]=1;
                }
            }
        }
    }


    //Algoritmo de Metropolis
    for(i=0;i<iter;i++)
    {

        //Rellenamos la hoja de resultados
        for(j=0;j<N;j++)
        {
            
            for(k=0;k<N-1;k++)
            {
                fprintf(f,"%i,",s[j][k]);
            }
            fprintf(f,"%i",s[j][k]);
            fprintf(f,"\n");
        }
        fprintf(f,"\n");

        //Empezamos el algoritmo tomando una posición aleatoria (n,m)
        p=1;
        n=gsl_rng_uniform_int(tau,N);
        m=gsl_rng_uniform_int(tau,N);


        //Aplicamos las condiciones periódicas
        if(n==0)
        {
            nd=1;
            na=N-1;
        }
        else if(n==N-1)
        {
            nd=0;
            na=N-2;
        }
        else
        {
            nd=n+1;
            na=n-1;
        }
        if(m==0)
        {
            md=1;
            ma=N-1;
        }
        else if(m==N-1)
        {
            md=0;
            ma=N-2;
        }
        else
        {
            md=m+1;
            ma=m-1;
        }

        //Calculamos E y comprobamos si hay que cambiar o no la orientación del spin.
        E=2*s[n][m]*(s[nd][m]+s[na][m]+s[n][md]+s[n][ma]);

        if(exp(-E/T)<p)
        {
            p=exp(-E/T);
        }

        et=gsl_rng_uniform(tau);
        if(et<p)
        {
            s[n][m]=-s[n][m];
        }
    }
    
    fclose(f);
    
    

    return 0;
}