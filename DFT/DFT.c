#include <math.h>
#include <complex.h>
#include "DFT.h"


void DFT(int N, const double complex* time, double complex* freq) {
    for (int k = 0; k < N; k++) {
        freq[k] = 0.0 + 0.0I;

        for (int n = 0; n < N; n++)
            freq[k] += time[n] * cexp(-2I * M_PI / N * k * n);
    }
}