cmake_minimum_required(VERSION 3.24)
project(FFTs C)

set(CMAKE_C_STANDARD 23)
MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(FFTs main.c head.h DFT/DFT.h DFT/DFT.c head.c FFT/CooleyTukeyAlgorithm.h FFT/CooleyTukeyAlgorithm.c sample.h sample.c)
