#pragma once
#ifndef _MINER_STRUCTERS_
#define _MINER_STRUCTERS_

#define _ROUND_ 0.001 
#include <iostream>

typedef struct vec2 {
	vec2(long double xCor, long double yCor):x(xCor), y(yCor){}
	vec2(long double xCor) :x(xCor), y(0){}
	vec2() :x(0), y(0) {}

	long double x,y;
};

typedef struct RGB {
public:
	RGB(unsigned char r, unsigned char g, unsigned char b) :r(r), g(g), b(b) {}
	RGB(unsigned char r, unsigned char g) :r(r), g(g), b(0) {}
	RGB(unsigned char r) :r(r), g(g), b(0) {}
	RGB() :r(0), g(g), b(0) {}
	unsigned char r, g, b;
};

typedef struct pos {
	pos(int xCor, int yCor) :x(xCor), y(yCor) {}
	pos(int xCor) :x(xCor), y(0) {}
	pos() :x(0), y(0) {}
	int x, y;
};

template <class _F, class _S>
class Pair2 {
public:
	Pair2(_F first, _S second): first(first), second(second){}
	Pair2() :first(),second(){}
	_F first;
	_S second;
};

std::ostream& operator<<(std::ostream& output, const vec2& vec) {
	output << "(" << vec.x << "," << vec.y << ")";
	return output;
}
std::ostream& operator<<(std::ostream& output, const pos& vec) {
	output << "(" << vec.x << "," << vec.y << ")";
	return output;
}

int lerp(int num,int range) {
	if (num >= 0 && num <= range) {return num;}
	if (num < 0) { return range-num;}
	return num-range;
}

long double lerp(long double num) {
	if (num >= 0 && num <= 1) {return num;}
	if (num < 0) {return 0;}
	return 1;
}

long double lerpN(long double num) {
	if (num >= -1 && num <= 1) {return num;}
	if (num < -1) {return -1;}
	return 1;
}

long double lerpC(long double num) {
	if (num >= 0 && num <= 1) {return num;}
	if (num > 1) { while (num-- > 1); return num;}
	if (num < 0) {while (num++ > 1);return num;}
}

long double lerpCN(long double num) {
	if (num >= -1 && num <= 1) { return num;}
	if (num > 1) {while (num-- > 1); return num;}
	if (num < -1) {while (num++ > 1); return num;}
}

vec2 round_(const vec2& num, const long double& approximation) {return vec2(long long int(num.x / approximation + (num.x < 0 ? -0.5 : 0.5)) * approximation, long long int(num.y / approximation + (num.y < 0 ? -0.5 : 0.5)) * approximation);}

long double round_(const long double& num, const long double& approximation) {return long long int(num / approximation + (num < 0 ? -0.5 : 0.5)) * approximation;}

template<typename Class>
vec2* getBalanceRange(const Class& LastElement) {

	vec2* range = new vec2[(int)LastElement + 1];
	float pstep = -1;
	float step = fabs(2.0 / ((int)LastElement + 1));

	for (int i = 0; i <= (int)LastElement; i++) {
		range[i].x = lerpN(pstep);
		range[i].y = lerpN(pstep) + step;
		pstep += step;
	}

	return range;
}

#endif