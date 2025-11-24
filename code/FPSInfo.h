#pragma once

struct FPSStruct {
	int frameCount;
	int currentFPS;
	float deltaTime;
};

extern FPSStruct delta;