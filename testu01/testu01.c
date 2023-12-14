#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "testu01.h"
#include "gofs.h"
#include "gofw.h"
#include "fbar.h"
#include "tables.h"

void debug_array(const double *V, unsigned long long N, const char *s)
{
    printf("%s ----\n", s);
    for (int i = 1; i <= N; i++)
        printf("%f\n", V[i]);
    printf("----\n");
}

/* Copy and shift, TestU01 do not use value at index 0, values are stored 1..N */
static void tables_CopyTabD_1 (const double T1[], double T2[], int n1, int n2)
{
    for (int i = n1; i <= n2; i++)
        T2[i] = T1[i-1];
}

/* m-NP */
double testu01_pvalue_snpair_ClosePairs(const double *P, unsigned long long N)
{
    double d, p;
    double *T;

    T = calloc(N+1, sizeof(double));
    if (!T) {
        printf("testu01: out of memory\n");
        return nan("NAN");
    }
    tables_CopyTabD_1(P, T, 1, N);
    tables_QuickSortD(T, 1, N);
    d = gofs_AndersonDarling (T, N);
    p = fbar_AndersonDarling (N, d);

    free(T);
    return p;
}

/* AD A2 */
double testu01_pvalue_sknuth_MaxOft(const double *P, unsigned long long N)
{
    double p;
    double *T;
    gofw_TestArray sVal;

    T = calloc(N+1, sizeof(double));
    if (!T) {
        printf("testu01: out of memory\n");
        return nan("NAN");
    }

    tables_CopyTabD_1(P, T, 1, N);
    tables_QuickSortD(T, 1, N);
    /* optimization - overwriting T[] in-place */
    gofs_ContUnifTransform (T, N, wdist_Unif, NULL, T);
    gofw_Tests0 (T, N, sVal);
    p = fbar_AndersonDarling (N, sVal[gofw_AD]);

    free(T);
    return p;
}
