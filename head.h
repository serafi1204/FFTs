#include <complex.h>
#define MAX_LENGTH_OF_SIGNAL 32768


// Struct
typedef struct signal {
    char name[MAX_LENGTH_OF_SIGNAL];
    int length;
    double complex timeDomain[MAX_LENGTH_OF_SIGNAL];
    double DFTTime;
    double complex DFT[MAX_LENGTH_OF_SIGNAL];
    double FFT_Radix2_Time;
    double complex FFT_Radix2[MAX_LENGTH_OF_SIGNAL];
    double FFT_Radix4_Time;
    double complex FFT_Radix4[MAX_LENGTH_OF_SIGNAL];
    double FFT_RadixMixed_Time;
    double complex FFT_RadixMixed[MAX_LENGTH_OF_SIGNAL];
} signal;


// Function
void FT (struct signal *s);
struct signal getSignal();
void printFTLog(struct signal *s);
void saveFTLog(struct signal *s);

