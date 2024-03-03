#pragma once
#define _ANIMALS_
#ifdef _ANIMALS_

#include <vector>
#include "MinerSructers.cpp"

typedef enum {
	Male,
	Female,
	Non_binery
}Gender;

typedef enum {
	Air,
	Wolf,
	Bunny,
	Grass,
}AnimalsSpecies;

typedef enum {
	Food,
	RunAway,
	Reproduce,
	None
}Priority;

class AnimalSettings {
public:
	AnimalSettings(Gender gender,int viewDistance,float libido, float hunger, short ageLimit):gender(gender), viewDistance(viewDistance),libido(lerp(libido)), hunger(hunger), ageLimit(ageLimit){}
	AnimalSettings(int viewDistance) :gender(Non_binery), viewDistance(viewDistance), libido(0), hunger(0), ageLimit(0) {}
	AnimalSettings():gender(Non_binery),viewDistance(0),libido(0),hunger(0), ageLimit(0){}

	void replace(const AnimalSettings& OtherTable, const bool& SetInDifferents) {
		if (SetInDifferents) {
			AnimalSettings blink = AnimalSettings();
			if (OtherTable.gender!=blink.gender) {
				gender = OtherTable.gender;
			}
			if (OtherTable.viewDistance != blink.viewDistance) {
				viewDistance += OtherTable.viewDistance;
			}
			if (OtherTable.libido!=blink.libido) {
				libido += OtherTable.libido;
			}
			if (OtherTable.hunger!=blink.hunger) {
				hunger += OtherTable.hunger;
			}
			if (OtherTable.ageLimit!=blink.ageLimit) {
				ageLimit += OtherTable.ageLimit;
			}
		}
		else {
			gender = OtherTable.gender;
			viewDistance += OtherTable.viewDistance;
			libido += OtherTable.libido;
			hunger += OtherTable.hunger;
			ageLimit += OtherTable.ageLimit;
		}
	}

	Gender getGender()const noexcept { return gender; }
	int getViewDistance()const noexcept { return viewDistance; }
	float getLibido()const noexcept { return libido; }
	float getHunger()const noexcept { return hunger; }
	short getAgeLimit()const noexcept { return ageLimit; }

	bool IsDied()const noexcept { return ageLimit <= 0; }

protected:
	Gender gender;
	int viewDistance;
	float libido;
	float hunger;
	short ageLimit;
};

class AnimalDecreaseStep {
public:
	AnimalDecreaseStep(float hungerDecrease, float libidoDecrease, int ageDecrease) : hungerDecrease(hungerDecrease), libidoDecrease(libidoDecrease), ageDecrease(ageDecrease) {}
	AnimalDecreaseStep(float hungerDecrease, float libidoDecrease ) : hungerDecrease(hungerDecrease), libidoDecrease(libidoDecrease), ageDecrease(1) {}
	AnimalDecreaseStep(float hungerDecrease) : hungerDecrease(hungerDecrease), libidoDecrease(0), ageDecrease(1) {}
	AnimalDecreaseStep(): hungerDecrease(0), libidoDecrease(0), ageDecrease(1){}

	void replace(const AnimalDecreaseStep& OtherTable, const bool& SetInDifferents) {
		if (SetInDifferents) {
			AnimalDecreaseStep blink = AnimalDecreaseStep();
			if (OtherTable.hungerDecrease != blink.hungerDecrease) {
				hungerDecrease = lerp(hungerDecrease+OtherTable.hungerDecrease);
			}
			if (OtherTable.ageDecrease != blink.ageDecrease) {
				ageDecrease = lerp(ageDecrease+OtherTable.ageDecrease);
			}
			if (OtherTable.libidoDecrease != blink.libidoDecrease) {
				libidoDecrease =lerp(libidoDecrease+ OtherTable.libidoDecrease);
			}
		}
		else {
			hungerDecrease = lerp(hungerDecrease + OtherTable.hungerDecrease);
			ageDecrease = lerp(ageDecrease + OtherTable.ageDecrease);
			libidoDecrease = lerp(libidoDecrease + OtherTable.libidoDecrease);
		}
	}

	float getHungerDecrease()const noexcept { return hungerDecrease; }
	float getLibidoDecrease()const noexcept { return libidoDecrease; }
	int   getAgeDecrease()const noexcept { return ageDecrease; }

protected:
	float hungerDecrease;
	float libidoDecrease;
	int   ageDecrease;
};

class Animal {
public:
	Animal(AnimalsSpecies Species, Gender gender, int viewDistance, float libido, float hunger, short ageLimit, float hungerDecrease, float libidoDecrease, int ageDecrease) :AnSetting(gender, viewDistance, libido, hunger, ageLimit), AnDecStep(hungerDecrease, libidoDecrease, ageDecrease), Species(Species), priority(None) {}
	Animal(AnimalsSpecies Species, Gender gender, int viewDistance, float libido, float hunger, short ageLimit, float hungerDecrease, float libidoDecrease) :AnSetting(gender, viewDistance, libido, hunger, ageLimit), AnDecStep(hungerDecrease, libidoDecrease), Species(Species),priority(None) {}
	Animal(AnimalsSpecies Species, Gender gender, int viewDistance, float libido, float hunger, short ageLimit) :AnSetting(gender, viewDistance, libido,hunger,ageLimit), AnDecStep(),Species(Species),priority(None) {}
	Animal():AnSetting(), AnDecStep(), Species(Air), priority(None) {}
	
	AnimalDecreaseStep AnDecStep;
	AnimalSettings AnSetting;

	AnimalsSpecies Species;
	Priority priority;

public:
	void move();
	void birth();
protected:
	void setAir(Animal& Species) { Species = Animal();}

	std::vector<Animal> ViewAnimals;
	void getViewAnimals();

};
 
#endif