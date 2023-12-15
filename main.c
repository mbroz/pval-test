#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE(array) \
    (sizeof(array) / sizeof(array[0]))

#include "dieharder/dieharder.h"
#include "nist-sts/nist-sts.h"
#include "testu01/testu01.h"

/* some test vectors */
struct tv {
    unsigned long long n;
    double p_dieharder_ks;
    double p_dieharder_ks_kuiper;
    double p_nist_sts;
    double p_testu01_closepairs;
    double p_testu01_maxoft;
    double p_testu01_ksp;
    double p_testu01_ksm;
    double p_testu01_ks;
    double p_testu01_ad;
    double p_testu01_cm;
    double p_testu01_wg;
    double p_testu01_wu;

    double v[128];
};

static struct tv tvs[] = {
    { 10, 0.77470533, 0.84135195, 0.73991829, 0.46196332, 0.46196332,
       0.20694496, 0.85347617, 0.20694496, 0.46196267, 0.39354650, 0.53705106, 0.61016066,
      { 0.024130, 0.365111, 0.377638, 0.483505, 0.506671,
        0.740374, 0.768266, 0.817382, 0.888149, 0.985609 }
    },
    { 10, 0.78126146, 0.62603398, 0.53414622, 0.49756899, 0.49756899,
       0.68702473, 0.16442022, 0.16442022, 0.49756968, 0.45148528, 0.17456792, 0.29593230,
      { 0.074514, 0.458474, 0.152269, 0.514449, 0.285739,
        0.422312, 0.426972, 0.715464, 0.683528, 0.662753 }
    },
    { 10, 0.59929734, 0.99787263, 0.21330931, 0.40070128, 0.40070128,
       0.97337498, 0.20674325, 0.20674325, 0.40070128, 0.39511549, 0.53673684, 0.57356159,
      { 0.01946478, 0.11948380, 0.12925806, 0.13562642, 0.23480394,
        0.51469966, 0.61449786, 0.68046770, 0.69371794, 0.92190720 }
    },
    { 10, 0.78126146, 0.62603398, 0.53414622, 0.49756968, 0.49756968,
       0.68702473, 0.16442022, 0.16442022, 0.49756968, 0.45148528, 0.17456792, 0.29593230,
      { 0.074514, 0.458474, 0.152269, 0.514449, 0.285739,
        0.422312, 0.426972, 0.715464, 0.683528, 0.662753 }
    },
};

static bool equal(double a, double b)
{
    return (fabs(a - b) <= 0.0001);
}

void run_test(void)
{
    double p;
    for (unsigned int i = 0; i < ARRAY_SIZE(tvs); i++) {
        p = dieharder_pvalue(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_dieharder_ks, p))
            printf("[%u] FAIL Dieharder, got %.8f\n", i, p);

        p = dieharder_pvalue_kuiper(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_dieharder_ks_kuiper, p))
            printf("[%u] FAIL Dieharder Kuiper, got %.8f\n", i, p);

        p = nist_pvalue(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_nist_sts, p))
            printf("[%u] FAIL NIS_STS, got %.8f\n", i, p);

        p = testu01_pvalue_snpair_ClosePairs(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_closepairs, p))
            printf("[%u] FAIL TestU01 ClosePairs, got %.8f\n", i, p);

        p = testu01_pvalue_sknuth_MaxOft(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_maxoft, p))
            printf("[%u] FAIL TestU01 MaxOft, got %.8f\n", i, p);

        p = testu01_pvalue_ksp(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_ksp, p))
            printf("[%u] FAIL TestU01 KSP, got %.8f\n", i, p);

        p = testu01_pvalue_ksm(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_ksm, p))
            printf("[%u] FAIL TestU01 KSM, got %.8f\n", i, p);

        p = testu01_pvalue_ks(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_ks, p))
            printf("[%u] FAIL TestU01 KS, got %.8f\n", i, p);

        p = testu01_pvalue_ad(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_ad, p))
            printf("[%u] FAIL TestU01 AD, got %.8f\n", i, p);

        p = testu01_pvalue_cm(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_cm, p))
            printf("[%u] FAIL TestU01 CM, got %.8f\n", i, p);

        p = testu01_pvalue_wg(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_wg, p))
            printf("[%u] FAIL TestU01 WG, got %.8f\n", i, p);

        p = testu01_pvalue_wu(tvs[i].v, tvs[i].n);
        if (!equal(tvs[i].p_testu01_wu, p))
            printf("[%u] FAIL TestU01 WU, got %.8f\n", i, p);
    }
}

double tst[] = {
        0.49523900, 0.77794400, 0.20551300, 0.24200100, 0.03537800,
        0.84930900, 0.20623000, 0.85872300, 0.58644100, 0.54850600,
        0.93146600, 0.91558200, 0.41335700, 0.64695200, 0.22095200,
        0.33304400, 0.39643800, 0.74745300, 0.60167000
};
const unsigned int tst_num = ARRAY_SIZE(tst);

int help(const char *arg0, const char *err) {
    if (err)
        printf("%s\n\n", err);
    printf("Use: %s\n", arg0);
    return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {

    // help(argv[0], NULL)
    // run_test();

    printf("Test size %u\n", tst_num);

    printf("DIEHARDER         %.8f\n", dieharder_pvalue(tst, tst_num));
    printf("DIEHARDER_KUIPER  %.8f\n", dieharder_pvalue_kuiper(tst, tst_num));
    printf("NIST              %.8f\n", nist_pvalue(tst, tst_num));
    printf("TESTU01_ClosePair %.8f\n", testu01_pvalue_snpair_ClosePairs(tst, tst_num));
    printf("TESTU01_MaxOft    %.8f\n", testu01_pvalue_sknuth_MaxOft(tst, tst_num));
    printf("TESTU01_KSP       %.8f\n", testu01_pvalue_ksp(tst, tst_num));
    printf("TESTU01_KSM       %.8f\n", testu01_pvalue_ksm(tst, tst_num));
    printf("TESTU01_KS        %.8f\n", testu01_pvalue_ks(tst, tst_num));
    printf("TESTU01_AD        %.8f\n", testu01_pvalue_ad(tst, tst_num));
    printf("TESTU01_CM        %.8f\n", testu01_pvalue_cm(tst, tst_num));
    printf("TESTU01_WG        %.8f\n", testu01_pvalue_wg(tst, tst_num));
    printf("TESTU01_WU        %.8f\n", testu01_pvalue_wu(tst, tst_num));

    return 0;
}
