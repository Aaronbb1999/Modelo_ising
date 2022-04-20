#include "functions.h"
#include "math.h"

void config_inicial(int s[MAX_COLS][MAX_COLS],int N,int v)
{
    int i,j,aux;
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
}


void Metropolis(int s[MAX_COLS][MAX_COLS],int N,double T)
{
    int n,m,E,i,j;
    int nd,na,md,ma;
    double p=1,et;
    n=gsl_rng_uniform_int(tau,N);
    m=gsl_rng_uniform_int(tau,N);

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