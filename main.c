#pragma once
#include <stdio.h>
#include "head.h"
#include "sample.h"


int main() {
    printf("Signal length: %d\n\n", MAX_LENGTH_OF_SIGNAL);

    // Sample signals
    struct signal sgnSin = getSinSignal(401);
    printFTLog(&sgnSin);
    saveFTLog(&sgnSin);

    struct signal sgnRec = getRectangleSignal(1000);
    printFTLog(&sgnRec);
    saveFTLog(&sgnRec);

    return 0;
}