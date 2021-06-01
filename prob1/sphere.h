#pragma once
#include <math.h>

#define INF 2e10f

struct Sphere {

    float   r, b, g;
    float   radius;
    float   x, y, z;
    float hit(float ox, float oy, float* n) {
        float dx = ox - x;
        float dy = oy - y;
        if (dx * dx + dy * dy < radius * radius) {
            float dz = sqrtf(radius * radius - dx * dx - dy * dy);
            *n = dz / sqrtf(radius * radius);
            return dz + z;
        }
        return -INF;
    }
};