#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "wigner_d.h"

int main(int argc, char* argv[])
{
    int l, l0, l1, n, m;
    double t;
    double* d;
    
    if(argc != 6)
    {
        fprintf(stderr, "usage: showdl l0 l1 m' m theta\n");
        return EXIT_FAILURE;
    }
    
    l0 = atoi(argv[1]);
    l1 = atoi(argv[2]);
    n = atoi(argv[3]);
    m = atoi(argv[4]);
    t = atof(argv[5]);
    
    if(l1 < l0)
    {
        fprintf(stderr, "range error: l0 <= l1 is required\n");
        return EXIT_FAILURE;
    }
    
    d = malloc((l1-l0+1)*sizeof(double));
    if(!d)
    {
        perror(NULL);
        return EXIT_FAILURE;
    }
    
    wigner_d(l0, l1, n, m, 0.017453292519943295769*t, d);
    
    printf("#    l  d^l_{%d, %d}(%g deg)\n", n, m, t);
    for(l = l0; l <= l1; ++l)
        printf("%6d  %+.18e\n", l, d[l-l0]);
    
    free(d);
    return EXIT_SUCCESS;
}
