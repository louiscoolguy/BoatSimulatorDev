#pragma once
#include <vector>
#include <tuple>

#define WORLD_INIT_SIZE 50
#define PERLIN_PERSISTANCE 1.6
#define PERLIN_OCTAVES 8
#define PERLIN_MULTIPLIER 2
#define SNOW_MOUNTAIN_TOP 80
#define ALMOST_MOUNTAIN 65
#define GRASS 50
#define SAND 40
#define WATER 25

typedef std::vector<std::tuple<int, int, int>> perlinData_t;
std::vector<std::tuple<int, int, int>> getFirstWorld(int seed);