#include "HashMap.cpp"
#include "Graphics.cpp"
#include "Noise.cpp"
#include "Animals.cpp"
#include "DrawRules.cpp"
#include "MinerSructers.cpp"
#include "Events.cpp"


using namespace std;


int main() {


	Events event(237468);

	Noise::Noise f(X, Y, 2389754);

	graphicsLive screen;
	long double** field = f.getGrid();
	screen.setField(field);

	return 0;

}