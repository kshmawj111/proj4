#pragma once
#include <omp.h>
#include "sphere.h"
#include <stdio.h>


#define rnd( x ) (x * rand() / RAND_MAX)
#define INF 2e10f
#define DIM 2048
#define SPHERES 20


void openmp_kernel(int x, int y, Sphere* s, unsigned char* ptr)
{
	int offset = x + y * DIM;
	float ox = (x - DIM / 2);
	float oy = (y - DIM / 2);

	//printf("x:%d, y:%d, ox:%f, oy:%f\n",x,y,ox,oy);

	float r = 0, g = 0, b = 0;
	float   maxz = -INF;

	for (int i = 0; i < SPHERES; i++) {
		float   n;
		float   t = s[i].hit(ox, oy, &n);
		if (t > maxz) {
			float fscale = n;
			r = s[i].r * fscale;
			g = s[i].g * fscale;
			b = s[i].b * fscale;
			maxz = t;
		}
	}

	ptr[offset * 4 + 0] = (int)(r * 255);
	ptr[offset * 4 + 1] = (int)(g * 255);
	ptr[offset * 4 + 2] = (int)(b * 255);
	ptr[offset * 4 + 3] = 255;
}


double render_openmp(int threads, Sphere* temp_s, unsigned char* bitmap)
{	
	double start = omp_get_wtime();

#pragma omp parallel for schedule(guided, 40) num_threads(threads)
	for (int x = 0; x < DIM; x++)
		for (int y = 0; y < DIM; y++)
			openmp_kernel(x, y, temp_s, bitmap);
	
	double total_exe_time = omp_get_wtime() - start;

	printf("openmp exe time: %lf, with %d threads\n", total_exe_time, threads);
}