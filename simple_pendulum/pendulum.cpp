#include <math.h>
#include <chrono>
#include "Pendulum.h"
#define PI 3.14159265359
#define G 9.81

wchar_t wBuffer[32];
char cBuffer[32];

	Pendulum::Pendulum(float x, float y, float l, float r) :x(x), y(y), l(l), r(r) {
		start_time_point = std::chrono::high_resolution_clock::now();
		this->init();
	}
	
	void Pendulum:: update() {
		cur_time_point = std::chrono::high_resolution_clock::now();
		auto time_diff = cur_time_point - start_time_point;
		time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_diff).count()/10;


		//math part ... sinusoidal .. blah blah
		float theta = theta_0 * cos(omega*time_elapsed);

		cx = x + l * sin(theta);
		cy = y + l * cos(theta);
	}

	void Pendulum::draw(Graphics* context) {
		context->DrawLine(x-100,y,x+100,y,0,0,1);
		context->DrawLine(x,y,cx,cy,1,1,1);
		context->DrawCircle(cx, cy, r, 1, 1, 1);

		float param_x = 100, param_y = 100,offset = 30;
		context->CustomDrawText(param_x,param_y,L"Parameters:\n",13);

		context->CustomDrawText(param_x, param_y + offset, L"omega = ", 9);
		convertFloatToWCHAR(omega,4);
		context->CustomDrawText(param_x + 100, param_y + offset, wBuffer, 4);
		

		context->CustomDrawText(param_x, param_y + 2*offset, L"length = ", 10);
		convertFloatToWCHAR(l, 4);
		context->CustomDrawText(param_x + 100, param_y + 2*offset, wBuffer, 4);

		context->CustomDrawText(param_x, param_y + 3 * offset, L"g = ", 5);
		convertFloatToWCHAR(10.0000, 2);
		context->CustomDrawText(param_x + 100, param_y + 3 * offset, wBuffer, 2);

		context->CustomDrawText(1000, param_y + 4 * offset, L"Formula:", 9);
		context->CustomDrawText(1000, param_y+5*offset, L"x = x0 * cos(omega*t)", 22);
		//render time elapsed

		convertFloatToWCHAR(time_elapsed, 4);

		float char_x = x-100, char_y = 500;
		context->CustomDrawText(char_x, char_y, L"Time Elapsed(s)",16);
		context->CustomDrawText(char_x+50,char_y+50,wBuffer,4);
	}

	void Pendulum::init() {
		theta_0 = PI / 6;
		cx = x + l * sin(theta_0);
		cy = y + l * cos(theta_0);
		omega = sqrt(G / l);
	}

	void convertFloatToWCHAR(float value,size_t length) {
		_gcvt_s(cBuffer, sizeof(cBuffer), value, length);
		mbstowcs_s(NULL,wBuffer,cBuffer, length);
	}

