/*
 * Fast Fourier Transform, Cooley-Tukey Algorithm
 * radix            : 2
 * Time complexity  : O(N log N)
*/
int FFT_Radix2(int N, const double complex* time, double complex* freq);
void FFT_Radix2_source(int N, const double complex* time, double complex* freq);


/*
 * Fast Fourier Transform, Cooley-Tukey Algorithm
 * radix            : 4
 * Time complexity  : O(N log N)
*/
int FFT_Radix4(int N, const double complex* time, double complex* freq);
void FFT_Radix4_source(int N, const double complex* time, double complex* freq);


/*
 * Fast Fourier Transform, Cooley-Tukey Algorithm
 * radix            : 4 and 2
 * Time complexity  : O(N log N)
*/
int FFT_RadixMixed(int N, const double complex* time, double complex* freq);
void FFT_RadixMixed_source(int N, const double complex* time, double complex* freq);