#pragma once
#include <chrono>
#include "Graphics.h"

class Pendulum {
public:
	float x, y, l, r;
	float cx, cy,omega;
	float theta_0,time_elapsed;
	std::chrono::steady_clock::time_point start_time_point, cur_time_point;
	Pendulum(float x, float y, float l, float r);

	void init();

	void update();

	void draw(Graphics*);
};

void convertFloatToWCHAR(float,size_t);