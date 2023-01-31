#pragma once
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "head.h"
#include "DFT/DFT.h"
#include "FFT/CooleyTukeyAlgorithm.h"


void FT (struct signal *s) {
    clock_t startClock;
    int error = 0;

    // DFT
    startClock = clock();
    DFT(s->length, s->timeDomain, s->DFT);
    s->DFTTime = (double)(clock() - startClock) / CLOCKS_PER_SEC;

    // FFT_Radix2
    startClock = clock();
    error = FFT_Radix2(s->length,s->timeDomain, s->FFT_Radix2);
    s->FFT_Radix2_Time = error ? -1 : (double)(clock() - startClock) / CLOCKS_PER_SEC;

    // FFT_Radix4
    startClock = clock();
    error = FFT_Radix4(s->length,s->timeDomain, s->FFT_Radix4);
    s->FFT_Radix4_Time = error ? -1 : (double)(clock() - startClock) / CLOCKS_PER_SEC;

    // FFT_RadixMixed
    startClock = clock();
    error = FFT_RadixMixed(s->length,s->timeDomain, s->FFT_RadixMixed);
    s->FFT_RadixMixed_Time = error ? -1 : (double)(clock() - startClock) / CLOCKS_PER_SEC;
}


struct signal getSignal() {
    struct signal s;

    // Read signal
    s.length = 0;

    while (1) {
        scanf_s("%d", &s.timeDomain[s.length]);
        s.length++;

        if (getchar() == '\n') break;
    }

    // FT
    FT(&s);

    return s;
}


void printFTLog(struct signal *s) {
    printf_s("[%s]\n"
             "\tDFT: %.3f s\n"
             "\tFFT_Radix2_Time: %.3f s\n"
             "\tFFT_Radix4_Time: %.3f s\n"
             "\tFFT_RadixMixed_Time: %.3f s\n"
             "\n",
             s->name,
             s->DFTTime,
             s->FFT_Radix2_Time,
             s->FFT_Radix4_Time,
             s->FFT_RadixMixed_Time
             );
}


void saveFTLog(struct signal *S) {
    // Output txt
    {
        char file[100] = "../output/";

        strcat(file, S->name);
        strcat(file, ".txt");

        FILE *fp = fopen(file, "w");

        int x = 0;
        for (int i = 0; i < MAX_LENGTH_OF_SIGNAL; i++) {
            x = (MAX_LENGTH_OF_SIGNAL / 2 + i) % MAX_LENGTH_OF_SIGNAL;

            fprintf(fp, "%d %.2f %.2f %.2f %.2f %.2f\n",
                    i - MAX_LENGTH_OF_SIGNAL / 2,
                    creal(S->timeDomain[i]),
                    creal(S->DFT[x]),
                    creal(S->FFT_Radix2[x]),
                    creal(S->FFT_Radix4[x]),
                    creal(S->FFT_RadixMixed[x])
            );
        }

        fclose(fp);
    }

    // Gnuplot
    {
        char plt[100] = "../output/";

        strcat(plt, S->name);
        strcat(plt, ".plt");

        FILE *fp = fopen(plt, "w");

        fprintf(
                fp,
                "scale = 500.0\n"
                "\n"
                "set term png\n"
                "set terminal pngcairo size 4*scale, 5*scale fontscale 2 linewidth 4 pointscale 4\n"
                "set output '%s.png'\n"
                "\n"
                "set multiplot layout 3, 2 title \"< %s >\"  font \", 20\"\n"
                "set grid\n"
                "\n"
                "set key font \",10\"\n"
                "set tics font \",10\"\n"
                "set xlab font \",10\"\n"
                "set key left top\n"
                "\n"
                "set xlab \"t (time domain)\"\n"
                "plot \"%s.txt\" u (column(1)):(column(2)) with lines title \"time domain\" lc 2\n"
                "\n"
                "set xlab \"w (freq domain)\"\n"
                "plot \"%s.txt\" u (column(1)):(column(3)) with lines title \"DFT\" lc 2\n"
                "plot \"%s.txt\" u (column(1)):(column(3)) with lines title \"DFT\" lc 7, \"%s.txt\" u (column(1)):(column(4)) with lines title \"FFT.CT.radix2\" lc 2\n"
                "plot \"%s.txt\" u (column(1)):(column(3)) with lines title \"DFT\" lc 7, \"%s.txt\" u (column(1)):(column(5)) with lines title \"FFT.CT.radix4\" lc 2\n"
                "\n"
                "set xrange [-100:100]\n"
                "plot \"%s.txt\" u (column(1)):(column(3)) with lines title \"DFT\" lc 7, \"%s.txt\" u (column(1)):(column(4)) with lines title \"FFT.CT.radix2\" lc 2\n"
                "plot \"%s.txt\" u (column(1)):(column(3)) with lines title \"DFT\" lc 7, \"%s.txt\" u (column(1)):(column(5)) with lines title \"FFT.CT.radix4\" lc 2\n"
                "\n"
                "unset multiplot",
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name,
                S->name
        );

        fclose(fp);
    }
}