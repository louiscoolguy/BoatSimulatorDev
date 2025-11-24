#include <stdio.h>
#include <math.h>


namespace Perlin {
    static double rawnoise(int n) {
        n = (n << 13) ^ n;
        return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    }

    static double noise2d(int x, int y, int octave, int seed) {
        return rawnoise(x * 1619 + y * 31337 + octave * 3463 + seed * 13397);
    }

    double interpolate(double a, double b, double x) {
        double f = (1 - cos(x * 3.14159)) * 0.5;
        return a * (1 - f) + b * f;
    }

    double smooth2d(double x, double y, int octave, int seed) {
        int intx = (int)x;
        double fracx = x - intx;
        int inty = (int)y;
        double fracy = y - inty;

        double v1 = noise2d(intx, inty, octave, seed);
        double v2 = noise2d(intx + 1, inty, octave, seed);
        double v3 = noise2d(intx, inty + 1, octave, seed);
        double v4 = noise2d(intx + 1, inty + 1, octave, seed);

        double i1 = interpolate(v1, v2, fracx);
        double i2 = interpolate(v3, v4, fracx);

        return interpolate(i1, i2, fracy);
    }

    double pnoise2d(double x, double y, double persistence, int octaves, int seed) {
        double total = 0.0;
        double frequency = 1.0;
        double amplitude = 1.0;
        int i = 0;

        for (i = 0; i < octaves; i++) {
            total += smooth2d(x * frequency, y * frequency, i, seed) * amplitude;
            frequency /= 2;
            amplitude *= persistence;
        }

        return total;
    }
}
