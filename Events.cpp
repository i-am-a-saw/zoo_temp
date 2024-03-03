#pragma once
#ifndef _EVENTS_
#define _ENENTS_

#include "Noise.cpp"
#include "HashMap.cpp"
#include "MinerSructers.cpp"
#include "DoubleLinkedStack.cpp"
#include "Animals.cpp"
#include "DefaultMacroses.cpp"

#define Event_Macroses\
_DEFAULT_DAY_\
_DEFAULT_SEASON_\
_DEFAULT_EXTRA_EVENT_\
_DEFAULT_DAY_DURATION_\
_DEFAULT_SEASON_DURATION_\
_TRAIL_LEN_\
_LAST_SEASON_\
_LAST_DAY_\
_LAST_EXTRA_

#define _DEFAULT_DAY_ Morning
#define _DEFAULT_SEASON_ Summer
#define _DEFAULT_EXTRA_EVENT_ Sunny

#define _DEFAULT_DAY_DURATION_ 5
#define _DEFAULT_SEASON_DURATION_ 20
#define _DEFAULT_EXTRA_DUTARION_ 7

#define _TRAIL_LEN_ 100

#define _LAST_SEASON_ Winter // if you'll change related enum you must change the macros for usage be correct
typedef enum {
	Summer,
	Spring,
	Automn,
	Winter
}Season;

#define _LAST_DAY_ Night // if you'll change related enum you must change the macros for usage be correct
typedef enum {
	Morning,
	Night
}Day;

#define _LAST_EXTRA_ Rain // if you'll change related enum you must change the macros for usage be correct
typedef enum {
	Sunny,
	Rain,
}Extra;

class Events {
public:
	Events(long long int Seed, short seasonDuration, short dayDuration, Season curSeason, Day curDay, Extra ExtraEvent) :Seed(Seed), seasonDuration(seasonDuration), dayDuration(dayDuration), curDay(curDay), curSeason(curSeason), ExtraEvent(ExtraEvent), Trail_len(0), ExtraTimePassed(0), ExtraStack(){ Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap(); }
	Events(long long int Seed, short seasonDuration, short dayDuration,Season curSeason, Day curDay) :Seed(Seed), seasonDuration(seasonDuration), dayDuration(dayDuration), curDay(curDay), curSeason(curSeason), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap();}
	Events(long long int Seed, short seasonDuration, short dayDuration, Season curSeason) :Seed(Seed), seasonDuration(seasonDuration), dayDuration(dayDuration), curDay(_DEFAULT_DAY_), curSeason(curSeason), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap();}
	Events(long long int Seed, Season curSeason, Day curDay) :Seed(Seed), seasonDuration(_DEFAULT_SEASON_DURATION_), dayDuration(_DEFAULT_DAY_DURATION_), curDay(curDay), curSeason(curSeason), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap(); }
	Events(long long int Seed, Season curSeason) :Seed(Seed), seasonDuration(_DEFAULT_SEASON_DURATION_), dayDuration(_DEFAULT_DAY_DURATION_), curDay(_DEFAULT_DAY_), curSeason(curSeason), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap(); }
	Events(long long int Seed, short seasonDuration,short dayDuration) :Seed(Seed), seasonDuration(seasonDuration), dayDuration(dayDuration), curDay(_DEFAULT_DAY_), curSeason(_DEFAULT_SEASON_), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_);setDelaultMap(); }
	Events(long long int Seed, short seasonDuration) :Seed(Seed), seasonDuration(seasonDuration), dayDuration(), curDay(_DEFAULT_DAY_), curSeason(_DEFAULT_SEASON_), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap();}
	Events(long long int Seed) :Seed(Seed), seasonDuration(_DEFAULT_SEASON_DURATION_), dayDuration(_DEFAULT_DAY_DURATION_), curDay(_DEFAULT_DAY_), curSeason(_DEFAULT_SEASON_), ExtraEvent(_DEFAULT_EXTRA_EVENT_), Trail_len(0), ExtraTimePassed(0), ExtraStack() { Trail = _DEFAULT_SET_TRAIL_(Seed, _TRAIL_LEN_); setDelaultMap(); }

	~Events() { delete[] Trail; }
private:
	const long long int Seed;

	const short seasonDuration;
	const short dayDuration;

	Day curDay;
	Season curSeason;
	Extra ExtraEvent;

	bool curDayChanged;
	bool curSeasonChanged;
	bool ExtraEventChanged;

	//These Delault map must be manualy filled in setDelaultMap() function
	// You must take coresponding macroses from _DEFAULT_MACROSES_ file DefaultMacroses.cpp
	//Otherwise it will NOT effect on your animals at all.
	HashMap<Day, Pair2<AnimalSettings,AnimalDecreaseStep>> effectAnimalDayMap;
	HashMap<Season, Pair2<AnimalSettings, AnimalDecreaseStep>> effectAnimalSeasonMap;
	HashMap<Extra, Pair2<AnimalSettings, AnimalDecreaseStep>> effectAnimalExtraMap;
public:
	
	void commitStep(const int& step){
		setExtraEvent(step);
		setDay(step);
		setSeason(step);
	}

	void commitSettingEffects(Animal& TheAnimal,const int& x,const int& y) {
		if (curDayChanged) { effectAnimalSettingsDay(TheAnimal.AnSetting, TheAnimal.AnDecStep);}
		if (curSeasonChanged) { effectAnimalSettingsSeason(TheAnimal.AnSetting, TheAnimal.AnDecStep);}
		if (ExtraEventChanged) { effectAnimalSettingsExtra(TheAnimal.AnSetting, TheAnimal.AnDecStep, x, y);}
	}

	Day getDay() { return curDay; }
	Season getSeason() { return curSeason; }
	Extra getExtra() { return ExtraEvent; }

	void setCustomExtraEventRange(Pair2<Extra,Pair2<vec2,int>> Range[(int)_LAST_EXTRA_+1])noexcept {
		ExtraMap.clear();
		for (int i = 0; i <= (int)_LAST_EXTRA_; i++) {
			ExtraMap.put(Range[i].first, Range[i].second);
		}
	}

	void setCustomTrail(long double* trail, int len) {
		delete[] Trail;
		if (len > _TRAIL_LEN_) { len = _TRAIL_LEN_; }
		int id;
		while (len--) {
			id = lerp(_TRAIL_LEN_ - len, _TRAIL_LEN_);
			Trail[id] = trail[id];
		}
	}
	void setCustomTrail(long double*& trail,int len) {
		delete[] Trail;
		if (len > _TRAIL_LEN_) { len = _TRAIL_LEN_; }
		int id;
		while (len--) {
			id = lerp(_TRAIL_LEN_ - len, _TRAIL_LEN_);
			Trail[id] = trail[id];
		}
	}

private:
	int Trail_len, ExtraTimePassed;
	long double* Trail;
	HashMap<Extra, Pair2<vec2,int>> ExtraMap;
	SDLL<Extra> ExtraStack;

	//Set related functions
	void setExtraEvent(const int& step)noexcept {
		ExtraEventChanged = false;
		resetTrail();

		const int& duration = ExtraMap.getV(ExtraEvent).second;
		if (!ExtraStack.empty() && ExtraTimePassed++== duration) {
			ExtraEvent = ExtraStack.popH();
			ExtraTimePassed = 0;
			ExtraEventChanged = true;
		}

		addExtraStack();

		++Trail_len;
	}
	void setDay(const int& step)noexcept {
		curDayChanged = false;
		if (step >= dayDuration) {
			if (!(step % dayDuration)) {
				curDay = (Day)(((int)curDay + 1) % ((int)_LAST_DAY_+1));
				curDayChanged = true;
			}
		}
	}
	void setSeason(const int& step) noexcept {
		curSeasonChanged = false;
		if (step >= seasonDuration) {
			if (!(step % seasonDuration)) {
				curSeason = (Season)(((int)curSeason + 1) % ((int)_LAST_SEASON_+1));
				curSeasonChanged = true;
			}
		}
	}

	//Additinal functions
	void resetTrail() {
		if (Trail_len + 1 == _TRAIL_LEN_) {
			delete[] Trail;
			Trail = _DEFAULT_SET_TRAIL_(Seed - (int)curDay - (int)curSeason - (int)ExtraEvent, _TRAIL_LEN_);
			Trail_len = 0;
		}
	}

	void addExtraStack()noexcept {
		for (int item = 0; item <= (int)_LAST_EXTRA_; item++) {
			const vec2& boards = ExtraMap.getV((Extra)item).first;
			if (boards.x <= Trail[Trail_len] && Trail[Trail_len] <= boards.y) {
				ExtraStack.add((Extra)item);
				break;
			}
		}
	}

	//Map related functions
	void setDelaultMap()noexcept {
		vec2* ExtraEventRange = getBalanceRange(_LAST_EXTRA_);

		for (int ex = 0; ex <= (int)_LAST_EXTRA_; ex++) {
			if (!ExtraMap.inMap((Extra)ex)) {
				ExtraMap.put((Extra)ex, Pair2(ExtraEventRange[ex], _DEFAULT_EXTRA_DUTARION_));
			}
		}
		delete[] ExtraEventRange;
#ifdef _DEFAULT_MACROSES_
		
		effectAnimalDayMap.put(Morning, Pair2(
			AnimalSettings(
				_DEFAULT_MORNING_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_MORNING_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_MORNING_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_MORNING_AnimalDecreaseStep_ageDecrease_
			))
		);
		effectAnimalDayMap.put(Night, Pair2(
			AnimalSettings(
				_DEFAULT_MORNING_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_NIGHT_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_NIGHT_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_NIGHT_AnimalDecreaseStep_ageDecrease_
			))
		);
		effectAnimalSeasonMap.put(Summer, Pair2(
			AnimalSettings(
				_DEFAULT_SUMMER_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_SUMMER_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_SUMMER_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_SUMMER_AnimalDecreaseStep_ageDecrease_
			))
		);

		effectAnimalSeasonMap.put(Automn, Pair2(
			AnimalSettings(
				_DEFAULT_AUTOMN_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_AUTOMN_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_AUTOMN_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_AUTOMN_AnimalDecreaseStep_ageDecrease_
			))
		);

		effectAnimalSeasonMap.put(Winter, Pair2(
			AnimalSettings(
				_DEFAULT_WINTER_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_WINTER_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_WINTER_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_WINTER_AnimalDecreaseStep_ageDecrease_
			))
		);

		effectAnimalSeasonMap.put(Spring, Pair2(
			AnimalSettings(
				_DEFAULT_SPRING_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_SPRING_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_SPRING_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_SPRING_AnimalDecreaseStep_ageDecrease_
			))
		);

		effectAnimalExtraMap.put(Sunny, Pair2(
			AnimalSettings(
				_DEFAULT_SUNNY_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_SUNNY_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_SUNNY_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_SUNNY_AnimalDecreaseStep_ageDecrease_
			))
		);

		effectAnimalExtraMap.put(Rain, Pair2(
			AnimalSettings(
				_DEFAULT_RAIN_AnimalSettings_viewDistance_
			),
			AnimalDecreaseStep(
				_DEFAULT_RAIN_AnimalDecreaseStep_hungerDecrease_,
				_DEFAULT_RAIN_AnimalDecreaseStep_libidoDecrease_,
				_DEFAULT_RAIN_AnimalDecreaseStep_ageDecrease_
			))
		);
		

#else
		for (int item = 0; i <= (int)_LAST_DAY_; i++) {
			effectAnimalDayMap.put((Day)item, Pair2(AnimalSettings(), AnimalDecreaseStep()));
		}
		for (int item = 0; i <= (int)_LAST_SEASON_; i++) {
			effectAnimalDayMap.put((Season)item, Pair2(AnimalSettings(), AnimalDecreaseStep()));
		}
		for (int item = 0; i <= (int)_LAST_EXTRA_; i++) {
			effectAnimalDayMap.put((Extra)item, Pair2(AnimalSettings(), AnimalDecreaseStep()));
		}

#endif // _DEFAULT_MACROSES_
	}

	//Effect settings functions
	void effectAnimalSettingsSeason(AnimalSettings& Settings, AnimalDecreaseStep& DecreaseStep)const noexcept {
		Settings.replace(effectAnimalSeasonMap.getV(curSeason).first, true);
		DecreaseStep.replace(effectAnimalSeasonMap.getV(curSeason).second, true);
	}
	void effectAnimalSettingsDay(AnimalSettings& Settings, AnimalDecreaseStep& DecreaseStep)const noexcept {
		Settings.replace(effectAnimalDayMap.getV(curDay).first, true);
		DecreaseStep.replace(effectAnimalDayMap.getV(curDay).second, true);
	}
	void effectAnimalSettingsExtra(AnimalSettings& Settings, AnimalDecreaseStep& DecreaseStep,const int& x,const int& y)const noexcept {
		Settings.replace(effectAnimalExtraMap.getV(ExtraEvent).first, true);
		DecreaseStep.replace(effectAnimalExtraMap.getV(ExtraEvent).second, true);
	}
		
};

#ifndef __SaveMacros__

#undef Event_Macroses

#endif // __SaveMacros__

#endif // _EVENTS_