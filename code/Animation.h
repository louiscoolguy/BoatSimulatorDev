#pragma once

class Animation {
private:
	int m_AnimationFPS;
	int m_currentFPS;
public:
	Animation(const int AnimationFPS, int currentFPS);
	void update();
	void render();
};