#pragma once
#ifndef _NOISE_
#define _NOISE_

#include <iostream>
#include "MinerSructers.cpp"

#define Noise_Macroses\
_ROUND_\
_DEFAULT_SET_TRAIL_\
_GET_NUM_LEN_STRIP_

#define _ROUND_ 0.001 
#define _DEFAULT_SET_TRAIL_(Seed,len) Noise::Noise(1, 1, Seed, 0, 1, 0, 2, 1).getStrip(len); 

namespace Noise {

	void printGrid(long double**& grid, const int& xLen, const int& yLen);
	void printGrid(const long double**& grid, const int& xLen, const int& yLen);
	void printGrid(const long double*& grid,const int& yLen);
	void printGrid(long double*& grid, const int& yLen);

	class Noise {

	public:

		Noise(int xLen, int yLen, long long int Seed, long double Offset, long double Amplitude, long double Exponent, long long int Harmonic_Spread, long long int Harmonic) :xLen(xLen), yLen(yLen), Offset(Offset), Amplitude(Amplitude), Exponent(Exponent), Harmonic_Spread(Harmonic_Spread), Harmonic(Harmonic), Seed(Seed) {}
		Noise(int xLen, int yLen, long long int Seed, long double Offset, long double Amplitude, long double Exponent, long long int Harmonic_Spread) :xLen(xLen), yLen(yLen), Offset(Offset), Amplitude(Amplitude), Exponent(Exponent), Harmonic_Spread(Harmonic_Spread), Harmonic(1), Seed(Seed) {}
		Noise(int xLen, int yLen, long long int Seed, long double Offset, long double Amplitude, long double Exponent) :xLen(xLen), yLen(yLen), Offset(Offset), Amplitude(Amplitude), Exponent(Exponent), Harmonic_Spread(1), Harmonic(1), Seed(Seed) {}
		Noise(int xLen, int yLen, long long int Seed, long double Offset, long double Amplitude) :xLen(xLen), yLen(yLen), Offset(Offset), Amplitude(Amplitude), Exponent(1), Harmonic_Spread(1), Harmonic(1), Seed(Seed) {}
		Noise(int xLen, int yLen, long long int Seed, long double Offset) :xLen(xLen), yLen(yLen), Offset(Offset), Amplitude(0.5), Exponent(1), Harmonic_Spread(1), Harmonic(1), Seed(Seed) {}
		Noise(int xLen, int yLen, long long int Seed) :xLen(xLen), yLen(yLen), Offset(0.5), Amplitude(0.5), Exponent(1), Harmonic_Spread(1), Harmonic(1), Seed(Seed) {}
		Noise(long long int Seed) :xLen(1), yLen(1), Offset(0.5), Amplitude(0.5), Exponent(1), Harmonic_Spread(1), Harmonic(1), Seed(Seed) {}

	private:

		const int xLen, yLen;
		const long long int Seed, Harmonic_Spread, Harmonic;
		const long double Offset, Amplitude, Exponent;

	public:

		long double** getGrid() const {
			long double** resGrid = new long double * [xLen];
			for (int i = 0; i < xLen; i++) {
				resGrid[i] = new long double[yLen];
			}

			for (int i = 0; i < xLen; i++) {
				for (int j = 0; j < yLen; j++) {
					resGrid[i][j] = perlin(i / Amplitude, j / Amplitude);
				}
			}

			return resGrid;
		}

		long double** getGrid(const int& xLen, const int& yLen) const {
			long double** resGrid = new long double * [xLen];
			for (int i = 0; i < xLen; i++) {
				resGrid[i] = new long double[yLen];
			}

			for (int i = 0; i < xLen; i++) {
				for (int j = 0; j < yLen; j++) {
					resGrid[i][j] = perlin(i / Amplitude, j / Amplitude);
				}
			}

			return resGrid;
		}

		long double* getStrip() const {
			long double* resStrip = new long double[yLen];

			for (int i = 0; i < yLen; i++) {
				resStrip[i] = perlin(i / Amplitude, i / Amplitude);;
			}

			return resStrip;
		}

		long double* getStrip(const int& len) const {
			long double* resStrip = new long double[len];

			for (int i = 0; i < len; i++) {
				resStrip[i] = perlin(i / Amplitude, (i + 1) / Amplitude);;
			}

			return resStrip;
		}

		void printGrid()const {
			long double** grid = getGrid();
			for (int i = 0; i < xLen; i++) {
				for (int j = 0; j < yLen; j++) {
					std::cout << grid[i][j] << " ";
				}
				std::cout << '\n';
			}
			delete grid;
		}

		void printStrip()const {
			long double* Strip = getStrip();
			for (int i = 0; i < yLen; i++) {
				std::cout << Strip[i] << " ";
			}
			delete Strip;
		}

#define _GET_NUM_LEN_STRIP_ 10
		float getNum() const {
			long double* trail = _DEFAULT_SET_TRAIL_(Seed, _GET_NUM_LEN_STRIP_);

			for (int i = 0; i < _GET_NUM_LEN_STRIP_; i++) {
				std::cout << trail[i] << " ";
				if (trail[i] > -1 && trail[i] < 1) {
					return trail[i];
				}
			}
			delete trail;
			return getNum(Seed + 1);
		}

	protected:
		float getNum(const long long int& seed) const {
			long double* trail = _DEFAULT_SET_TRAIL_(seed, _GET_NUM_LEN_STRIP_);

			for (int i = 0; i < _GET_NUM_LEN_STRIP_; i++) {
				if (trail[i] > -1 && trail[i] < 1) {
					return trail[i];
				}
			}
			delete trail;
			return getNum(seed + 1);
		}

		long double perlin(long double x, long double y) const {
			int x0 = (int)x - 1;
			int y0 = (int)y - 1;
			int x1 = x0 + 1;
			int y1 = y0 + 1;

			long double sx = x - (long long int)x0;
			long double sy = y - (long long int)y0;

			long double n0 = dotGridGrad(x0, y0, x, y);
			long double n1 = dotGridGrad(x1, y0, x, y);
			long double ix0 = Interpolate(n0, n1, sx * Exponent);

			n0 = dotGridGrad(x0, y1, x, y);
			n1 = dotGridGrad(x1, y1, x, y);
			long double ix1 = Interpolate(n0, n1, sx * Exponent);

			long double fx0 = fx(sx);
			long double fx1 = fx(sy);

			long double res0 = Interpolate(ix0, ix1, sy) * fx0;
			long double res1 = Interpolate(ix0, ix1, sy) * fx1;

			long double res = round_(lerpN(Clip(res0 + Offset, res1 + Offset, 1)), _ROUND_);

			return res;
		}

		vec2 randGrad(int ix, int iy) const {

			const unsigned w = 8 * sizeof(unsigned);
			const unsigned s = w / 2;
			unsigned a = ix, b = iy;

			a *= Seed; b ^= a << s | a >> w - s;
			b *= Seed; a ^= b << s | b >> w - s;
			a *= Seed;

			long double r = a * (3.14159265 / ~(~0u >> 1));

			return vec2(cos(r), sin(r));
		}

		long double dotGridGrad(int ix, int iy, long double x, long double y)const {
			vec2 grand = randGrad(ix, iy);

			long double dx = x - (long double)ix;
			long double dy = y - (long double)iy;

			return (dx * grand.x + dy * grand.y);
		}

		long double Interpolate(long double n1, long double n2, long double w)const {
			return (n1 - n2) * (3.0 - w * 2) * w * w + n1;
		}

		long double dotProduct(const vec2& v1, const vec2& v2)const {
			return v1.x * v2.x + v2.y + v2.y;
		}

		long double Clip(const long double& a, const long double& b, const long double w)const {
			return	a + w * (b - a);
		}

		long double fx(const long double& sx)const {
			return pow(Harmonic_Spread / Harmonic, Exponent) * pow(sx, Exponent - 1);
		}

	};

}

static void printGrid(long double**& grid, const int& xLen, const int& yLen) {
	for (int i = 0; i < xLen; i++) {
		for (int j = 0; j < yLen; j++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << '\n';
	}
}

static void printGrid(const long double**& grid, const int& xLen, const int& yLen) { printGrid(grid,xLen,yLen); }

static void printGrid(long double*& grid, const int& yLen) {
	for (int i = 0; i < yLen; i++) {
		std::cout << grid[i] << " ";
	}
}

static void printGrid(const long double*& grid, const int& yLen) { printGrid(grid, yLen); }


#ifndef __SaveMacros__

#undef Noise_Macroses

#endif // __SaveMacros__

#endif // _NOISE_
