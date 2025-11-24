#include <iostream>
#include "WorldGeneration.h"
#include "Perlin.h"


std::vector<std::tuple<int, int, int>> getFirstWorld(int seed) {
	static std::vector<std::tuple<int, int, int>> perlinValues;

	if (!perlinValues.size()) {
		perlinValues.reserve(WORLD_INIT_SIZE * WORLD_INIT_SIZE_X);
		perlinValues.clear();
		for (int perlinX = 0; perlinX < WORLD_INIT_SIZE; perlinX++) {
			for (int perlinY = 0; perlinY < WORLD_INIT_SIZE_X; perlinY++) {

				float noiseValue = Perlin::pnoise2d(perlinX, perlinY, PERLIN_PERSISTANCE, PERLIN_OCTAVES, seed);

				int perlinColor = (int)((noiseValue)*PERLIN_MULTIPLIER);

				perlinColor = (perlinColor > 255) ? 255 : perlinColor;
				perlinColor = (perlinColor < 0) ? 0 : perlinColor;
				perlinValues.push_back({ perlinX, perlinY, perlinColor });
			}
		}
	}
	return perlinValues;
}