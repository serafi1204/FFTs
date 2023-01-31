#pragma once
#include <string.h>
#include <math.h>
#include<stdlib.h>
#include "head.h"
#include "DFT/DFT.h"
#include "FFT/CooleyTukeyAlgorithm.h"


struct signal getSinSignal(int freq) {
    struct signal s;

    strcpy(s.name, "sin");

    s.length = MAX_LENGTH_OF_SIGNAL;
    for (int i = 0; i < MAX_LENGTH_OF_SIGNAL; i++)
        s.timeDomain[i] = sin(i * 2 *M_PI / freq);

    FT(&s);

    return s;
}


struct signal getRectangleSignal(int width) {
    struct signal s;

    strcpy(s.name, "rectangle");

    // Rectangle signal
    s.length = MAX_LENGTH_OF_SIGNAL;
    for (int i = 0; i < MAX_LENGTH_OF_SIGNAL; i++)
        s.timeDomain[i] = width * 2 < i && i < MAX_LENGTH_OF_SIGNAL - width * 2 ? 1.0f : 0.0f;

    // FT
    FT(&s);

    return s;
}