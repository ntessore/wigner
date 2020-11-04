#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "wigner.h"

#ifndef LINELEN
#define LINELEN 1024
#endif

int cmp(const void* a, const void* b)
{
    const double* x = a;
    const double* y = b;
    return (x[0] > y[0]) - (x[0] < y[0]);
}

int main(int argc, char* argv[])
{
    int l, l0, l1, m1, m2, nt, n, i;
    double t, t0, t1, x, d;
    FILE* fp;
    char buf[LINELEN];
    char* ell;
    char* c_l;
    double* l_cl;
    double* cl;
    double* wd;
    
    if(argc < 8 || argc > 9)
    {
        fprintf(stderr, "usage: cl_to_xi lmin lmax m1 m2 th0 th1 nth [file]\n");
        return EXIT_FAILURE;
    }
    
    l0 = atoi(argv[1]);
    l1 = atoi(argv[2]);
    m1 = atoi(argv[3]);
    m2 = atoi(argv[4]);
    t0 = atof(argv[5]);
    t1 = atof(argv[6]);
    nt = atoi(argv[7]);
    
    if(l0 < 0 || l1 < l0)
    {
        fprintf(stderr, "error: 0 <= lmin <= lmax required\n");
        return EXIT_FAILURE;
    }
    
    if(t0 < 0 || t1 < t0)
    {
        fprintf(stderr, "error: 0 <= th0 <= th1 required\n");
        return EXIT_FAILURE;
    }
    
    if(nt < 2)
    {
        fprintf(stderr, "error: nth > 1 required\n");
        return EXIT_FAILURE;
    }
    
    fp = argc > 8 ? fopen(argv[8], "r") : stdin;
    if(!fp)
    {
        perror(NULL);
        return EXIT_FAILURE;
    }
    
    i = 1;
    l_cl = malloc(i*2*sizeof(double));
    if(!l_cl)
        perror(NULL), abort();
    
    for(l = 1, n = 0; fgets(buf, sizeof(buf), fp); ++l)
    {
        ell = strtok(buf, " \t\r\n");
        c_l = strtok(NULL, " \t\r\n");
        
        if(!ell || *ell == '#')
            continue;
        
        if(!c_l || *c_l == '#')
        {
            fprintf(stderr, "error: line %d: missing `C_l` value\n", l);
            return EXIT_FAILURE;
        }
        
        if(n == i)
        {
            i *= 2;
            l_cl = realloc(l_cl, i*2*sizeof(double));
            if(!l_cl)
                perror(NULL), abort();
        }
        
        l_cl[n*2+0] = atof(ell);
        l_cl[n*2+1] = atof(c_l);
        n += 1;
    }
    
    if(fp != stdin)
        fclose(fp);
    
    if(n < 2)
    {
        fprintf(stderr, "error: needs at least two entries\n");
        return EXIT_FAILURE;
    }
    
    qsort(l_cl, n, 2*sizeof(double), cmp);
    
    cl = malloc((l1-l0+1)*sizeof(double));
    wd = malloc((l1-l0+1)*sizeof(double));
    if(!cl || !wd)
        perror(NULL), abort();
    
    l = l0;
    if(l_cl[0] > l)
    {
        d = (l_cl[3] - l_cl[1])/(l_cl[2] - l_cl[0]);
        for(; l < l_cl[0]; ++l)
            cl[l-l0] = l_cl[1] + d*(l - l_cl[0]);
    }
    for(i = 1; l <= l1; ++l)
    {
        while(i < n && l_cl[2*i] < l)
            ++i;
        d = (l_cl[2*i+1] - l_cl[2*i-1])/(l_cl[2*i] - l_cl[2*i-2]);
        cl[l-l0] = l_cl[2*i+1] + d*(l - l_cl[2*i]);
    }
    
    printf("# %-22s  %-s\n", "theta [deg]", "xi");
    
    d = (t1 - t0)/(nt - 1);
    for(i = 0; i < nt; ++i)
    {
        t = t0 + d*i;
        
        wigner_d_l(l0, l1, m1, m2, 0.017453292519943295769*t, wd);
        
        x = 0;
        for(l = l0; l <= l1; ++l)
            x += 0.079577471545947667884*(2*l+1)*cl[l-l0]*wd[l-l0];
        
        printf("%.18e  %.18e\n", t, x);
    }
    
    free(cl);
    free(wd);
    free(l_cl);
    
    return EXIT_SUCCESS;
}
