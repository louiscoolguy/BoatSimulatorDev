#pragma once

namespace Perlin{
	double interpolate(double a, double b, double x);

	double smooth2d(double x, double y, int octave, int seed);

	double pnoise2d(double x, double y, double persistence, int octaves, int seed);
}