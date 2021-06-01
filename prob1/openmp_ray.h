#pragma once
#include <omp.h>
#include "sphere.h"
#include <stdio.h>

void openmp_kernel(int x, int y, Sphere* s, unsigned char* ptr);
double render_openmp(int threads, Sphere* temp_s, unsigned char* bitmap);