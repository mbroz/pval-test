#ifndef __NISTSTS_H__
#define __NISTSTS_H__

#define UNUSED(x) (void)(x)

#define ALPHA 0.01 /* SIGNIFICANCE LEVEL */

#define TEST_FREQUENCY          1
#define TEST_BLOCK_FREQUENCY    2
#define TEST_CUSUM              3
#define TEST_RUNS               4
#define TEST_LONGEST_RUN        5
#define TEST_RANK               6
#define TEST_FFT                7
#define TEST_NONPERIODIC        8
#define TEST_OVERLAPPING        9
#define TEST_UNIVERSAL         10
#define TEST_APEN              11
#define TEST_RND_EXCURSION     12
#define TEST_RND_EXCURSION_VAR 13
#define TEST_SERIAL            14
#define TEST_LINEARCOMPLEXITY  15

int nist_compute(const double *P, int numOfBitStreams, int test, double *pval);

inline double nist_pvalue(const double *P, unsigned long long N)
{
	double p  = 0;
	nist_compute(P, (int)N, 0, &p);
	return p;
}
#endif
