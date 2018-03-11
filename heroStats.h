#pragma once
#include <vector>
//#include "curl_Get.h"

/*nifty c++ trick to turn a var name into a string*/
#define STRINGIFY(name) stringify(#name), (name))

typedef std::pair<std::string, std::string> DoubleString;
typedef std::pair<std::string, int>			StatTable;

///TODO NAMESPACE ISSUES;;;;;

//namespace heroStats {
	/*
	This file contains the template that holds stats earned by a player for each hero

		HeroStats -> stats all heroes have
			|
			^
		Σ (all heroes) heroSpecificStats - a child struct with additional niche stats for each hero

	Each player contains a list of all possible heroes (regardless of time played)
		and the stats for each specific hero are logged according to that player's recorded stats
	*/

	struct damageDealer {
		int soloKills;
		int finalBlows;
		int multiKills;
		int criticalHits;
		int critAcc;
		int weaponAccuracy;
		int weaponAccuracyBestInGame;
		int bestKillStreak;

		float damageDoneAvg;
		float soloKillsAvg;
		float multiKillsAvg;
		float accuracyAvg;
	};

	struct healer {
		int offensiveAssists = 0;
		int	offensiveAssistsMostInGame = 0;
		int defensiveAssists = 0;
		int	defensiveAssistsMostInGame = 0;
		int healingDone = 0;
		int healingDoneMostInGame = 0;

		float healingDoneAvg;
		float defensiveAssistsAvg;
		float offensiveAssistsAvg;
	};

	struct tank {
		int damageBlocked;
		int damageAbsorbed;
	};

	/*
	current issue, i want inheritance without the overhead,
	if i make all of these public it is ugly
	if i make them protected i still need to make getters for every one ...
	idk
	*/
	class heroStats {

		//contains this hero's stats shared by all heroes
	protected:
		//accessory
		std::vector<std::pair<std::string, int> > stringifiedStats;

		damageDealer* dpsStats = nullptr;
		healer* healerStats = nullptr;
		tank* tankStats = nullptr;

			//match
			int medalBronze;
			int medalSilver;
			int medalGold;
			int noMedal;
			int cards;

			//game
			int timePlayed;
			int gamesWon;

			//combat
			int heroDamageDone;
			int barrierDamageDone;
			int deaths;
			int objectiveTime;
			int objectiveKills;
			int eliminations;
			int timeOnFire;

			//avgs
			float winPercent;
			float avgHeroDamage;
			float avgBarrierDamage;
			float avgDeaths;
			float avgObjectiveTime;
			float avgObjectiveKills;
			float avgEliminations;
			float avgTimeOnFire;
		


	public:

		inline void stringifyAllObjects() {
			stringify(noMedal);
			stringify(medalBronze);
			stringify(medalSilver);
			stringify(medalGold);
			stringify(cards);
			stringify(timePlayed);
			stringify(gamesWon);
			stringify(objectiveTime);
			stringify(objectiveKills);
			stringify(heroDamageDone);
			stringify(barrierDamageDone);
			stringify(deaths);
			stringify(timeOnFire);
		}

		inline void stringify(char* name, int value) {
			this->stringifiedStats.push_back(std::make_pair(name, value));
		}

		inline std::vector<std::pair<std::string, int> > returnStatStrings() { return this->stringifiedStats; }
		/*
		3 fields that specify the type of character, used to generalize stats, and reduce the memory
		footprint each hero has to hold.  Each hero should only contain stats relevant to it

		In general : each hero should only be one category, healer - tank - dps
		The heroStats should then be casted to a specific hero to obtain the stats specific to that hero
		*/

		heroStats(bool thatIsHealer = false, bool thatIsDamageDealer = false, bool thatIsTank = false)
			: 
			noMedal(0),
			medalBronze(0),
			medalSilver(0),
			medalGold(0),
			cards(0),
			timePlayed(0),
			gamesWon(0),
			objectiveTime(0),
			objectiveKills(0),
			heroDamageDone(0),
			barrierDamageDone(0),
			deaths(0),
			timeOnFire(0),
			winPercent(0.0),
			avgHeroDamage(0.0),
			avgBarrierDamage(0.0),
			avgDeaths(0.0),
			avgObjectiveTime(0.0),
			avgObjectiveKills(0.0),
			avgEliminations(0.0),
			avgTimeOnFire(0.0)
			
		{
			if (thatIsDamageDealer) {
				dpsStats = new damageDealer;
				//zarya is damagedealer
			}

			if (thatIsHealer) {
				healerStats = new healer;
			}

			if (thatIsTank) {
				tankStats = new tank;
			}
		} //end constructor

		void stringify(int name);
		void updateStats(heroStats old);
		heroStats returnBaseStats() { return this; }
		inline void setBaseStats(std::string* buffer) {

		};
		
		virtual inline void calculateAvgs() {}

		/*the only way to change stats*/
		virtual void updateStats() {}
		void updateBaseStats();
	};

	class widowStats : public heroStats {

	private:
		struct widowSpecificStats {
			int venomMineKills;
			int	scopedCriticalHits;
			int	scopedCriticalHitsMostInGame;
			int	VenomMineKillsMostInGame;
			int	scopedAccuracyBestInGame;
			int	scopedAccuracy;
			int reconAssists;
		};

		struct widowAvgStats {
			float venomMineKillsAvg;
			float scopedCriticalHitsAvg;
			float reconAssistsAvg;
		};

		/*the values the implementer can see*/
		struct widowStatInterface {
			widowSpecificStats specificStats;
			widowAvgStats avgStats;
			heroStats baseStats;
			widowStatInterface(widowStats those) {
				this->specificStats = those.getSpecific();
				this->baseStats		= those.getBaseStats();
				this->avgStats		= those.getAvgStats();
			}
		};

		//widowStatInterface statInterface = nullptr;

		/*the values that can be changed*/
		widowSpecificStats theseWidowStats;
		widowAvgStats theseWidowAvgStats;
		heroStats baseStats = new heroStats(false, true, false);

	public:

		const widowSpecificStats getSpecific()  const { return this->theseWidowStats; }
		const widowAvgStats	     getAvgStats()  const { return this->theseWidowAvgStats; }
		const heroStats		     getBaseStats() const { return this->baseStats; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const widowStatInterface* statInterface = new widowStatInterface(*this);

		inline void calculateAvgs() {

		}
	
		void updateStats() { delete this->statInterface;
							 this->theseWidowAvgStats.reconAssistsAvg = 5;
							 this->statInterface = new widowStatInterface(*this);
							}
	};

	class genjiStats : public heroStats {

		heroStats baseStats = new heroStats(false, true, false);

		/*Hero Specific*/
		int dragonBladeKills;
		int dragonBladeKillsMostInGame;
		int damageReflected;
		

		/*Averages*/
		float dragonBladeKillsAvg;
		float damageReflectedAvg;
	
	};


//}