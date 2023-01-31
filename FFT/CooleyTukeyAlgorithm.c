#include <complex.h>
#include <stdio.h>
#include <math.h>
#include "..\head.h"
#include "CooleyTukeyAlgorithm.h"


int FFT_Radix2(int N, const double complex* time, double complex* freq) {
    double l = log2(N);

    if (l != (int)l)
         return 1;
    else {
         FFT_Radix2_source(N, time, freq);
         return 0;
    }
}


void FFT_Radix2_source(int N, const double complex* time, double complex* freq) {
    if (N == 1) {
        freq[0] = time[0];
        return;
    }

    // FFT
    double complex odd[N / 2] , even[N / 2];

    for (int i = 0; i < N; i++)
        (i % 2 == 0 ? even : odd)[i / 2] = time[i];

    FFT_Radix2_source(N / 2, odd, odd);
    FFT_Radix2_source(N / 2, even, even);

    for (int k = 0; k < N / 2; k++) {
        double complex temp = cexp(-2I * M_PI / N * k);

        freq[k + N / 2] = even[k] - temp * odd[k];
        freq[k] = even[k] + temp * odd[k];
    }
}


int FFT_Radix4(int N, const double complex* time, double complex* freq) {
    double l = log2(N);

    if (l != (int)l || (int)l % 2 == 1)
        return 1;
    else {
        FFT_Radix4_source(N, time, freq);
        return 0;
    }
}


void FFT_Radix4_source(int N, const double complex* time, double complex* freq) {
    if (N == 1) {
        freq[0] = time[0];
        return;
    }

    // FFT
    double complex f0[N / 4], f1[N / 4], f2[N / 4], f3[N / 4];

    for (int i = 0; i < N; i++){
        if (i % 4 == 0) f0[i / 4] = time[i];
        else if (i % 4 == 1) f1[i / 4] = time[i];
        else if (i % 4 == 2) f2[i / 4] = time[i];
        else if (i % 4 == 3) f3[i / 4] = time[i];
    }

    FFT_Radix4_source(N / 4, f0, f0);
    FFT_Radix4_source(N / 4, f1, f1);
    FFT_Radix4_source(N / 4, f2, f2);
    FFT_Radix4_source(N / 4, f3, f3);

    for (int k = 0; k < N / 4; k++) {
        double complex temp1 = cexp(-2I * M_PI / N * k);
        double complex temp2 = cexp(-2I * M_PI / N * k * 2);

        freq[k] = (f0[k] + temp2 * f2[k]) + temp1 * (f1[k] + temp2 * f3[k]);
        freq[k + N / 4] = (f0[k] - temp2 * f2[k]) - 1I * temp1 * (f1[k] - temp2 * f3[k]);
        freq[k + N / 2] = (f0[k] + temp2 * f2[k]) - temp1 * (f1[k] + temp2 * f3[k]);
        freq[k + N / 4 * 3] = (f0[k] - temp2 * f2[k]) + 1I * temp1 * (f1[k] - temp2 * f3[k]);
    }
}


int FFT_RadixMixed(int N, const double complex* time, double complex* freq) {
    double l = log2(N);

    if (l != (int)l)
        return 1;
    else {
        FFT_RadixMixed_source(N, time, freq);
        return 0;
    }
}


void FFT_RadixMixed_source(int N, const double complex* time, double complex* freq) {
    if (N == 1) {
        freq[0] = time[0];
        return;
    }

    if (N % 4 == 0) {
        // FFT
        double complex f0[N / 4], f1[N / 4], f2[N / 4], f3[N / 4];

        for (int i = 0; i < N; i++){
            if (i % 4 == 0) f0[i / 4] = time[i];
            else if (i % 4 == 1) f1[i / 4] = time[i];
            else if (i % 4 == 2) f2[i / 4] = time[i];
            else if (i % 4 == 3) f3[i / 4] = time[i];
        }

        FFT_RadixMixed_source(N / 4, f0, f0);
        FFT_RadixMixed_source(N / 4, f1, f1);
        FFT_RadixMixed_source(N / 4, f2, f2);
        FFT_RadixMixed_source(N / 4, f3, f3);

        for (int k = 0; k < N / 4; k++) {
            double complex temp1 = cexp(-2I * M_PI / N * k);
            double complex temp2 = cexp(-2I * M_PI / N * k * 2);

            freq[k] = (f0[k] + temp2 * f2[k]) + temp1 * (f1[k] + temp2 * f3[k]);
            freq[k + N / 4] = (f0[k] - temp2 * f2[k]) - 1I * temp1 * (f1[k] - temp2 * f3[k]);
            freq[k + N / 2] = (f0[k] + temp2 * f2[k]) - temp1 * (f1[k] + temp2 * f3[k]);
            freq[k + N / 4 * 3] = (f0[k] - temp2 * f2[k]) + 1I * temp1 * (f1[k] - temp2 * f3[k]);
        }
    }
    else if (N % 2 == 0) {
        // FFT
        double complex odd[N / 2], even[N / 2];

        for (int i = 0; i < N; i++)
            (i % 2 == 0 ? even : odd)[i / 2] = time[i];

        FFT_RadixMixed_source(N / 2, odd, odd);
        FFT_RadixMixed_source(N / 2, even, even);

        for (int k = 0; k < N / 2; k++) {
            double complex temp = cexp(-2I * M_PI / N * k);

            freq[k + N / 2] = even[k] - temp * odd[k];
            freq[k] = even[k] + temp * odd[k];
        }
    }
}