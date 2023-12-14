#ifndef __DIEHARDER_H__
#define __DIEHARDER_H__

#include <stdint.h>

#define CONST_CAST(x) (x)(uintptr_t)

double kstest(double *pvalue, int count);
double kstest_kuiper(double *pvalue,int count);

inline double dieharder_pvalue(const double *P, unsigned long long N)
{
    return kstest(CONST_CAST(double*)(P), (int)N);
}

inline double dieharder_pvalue_kupier(const double *P, unsigned long long N)
{
    return kstest_kuiper(CONST_CAST(double*)(P), (int)N);
}

/*
   -k ks_flag - ks_flag
     0 is fast but slightly sloppy for psamples > 4999 (default).
     1 is MUCH slower but more accurate for larger numbers of psamples.
     2 is very slow and accurate to machine precision.
     3 is kuiper ks, fast, quite inaccurate for small samples, deprecated.
*/
#endif
