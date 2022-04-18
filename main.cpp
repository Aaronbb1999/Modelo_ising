#include "functions.h"
#include <stdio.h>
#include "math.h"
#include "gsl_rng.h"

gsl_rng *tau;


int main()
{
    double x;
    int i;
    extern gsl_rng *tau;

    int semilla=132456;
    tau=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau,semilla);

    x=gsl_rng_uniform(tau);
    i=gsl_rng_uniform_int(tau,100);

    printf("%lf, %i",x,i);
    return 0;
}