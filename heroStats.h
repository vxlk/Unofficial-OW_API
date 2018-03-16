#pragma once
#include <vector>
//#include "curl_Get.h"

/*nifty c++ trick to turn a var name into a string*/
#define STRINGIFY(name) stringify(#name), (name))
#define NUM_CATEGORIES 12
#define NUM_HEROES 26
#define BUFFER_SIZE 256
typedef std::pair<std::string, std::string> DoubleString;
typedef std::pair<std::string, int>			StatTable;
std::vector<std::pair<DoubleString, StatTable> > statTable;
DoubleString* heroId = new DoubleString[NUM_HEROES + 1]; //+1 for the all_heroes category
static const std::string heroList[NUM_HEROES] = {
	"Doomfist"  , "Genji"  , "McCree"     ,
	"Pharah"    , "Reaper" , "Soldier: 76",
	"Sombra"    , "Tracer" , "Hanzo"      ,
	"Junkrat"   , "Mei"    , "TorbjÃ¶rn"  , //this is how torb's name is read in unicode i guess..
	"Widowmaker", "D.Va"   , "Orisa"      ,
	"Reinhardt" , "Roadhog", "Winston"    ,
	"Zarya"     , "Ana"	   , "LÃºcio"     , //lucio ...
	"Mercy"		, "Moira"  , "Symmetra"   ,
	"Zenyatta"
};

enum stringEnum {
	Doomfist,Genji,McCree,
	Pharah,Reaper,Soldier76,
	Sombra,Tracer,Hanzo,
	Junkrat,Mei,Torbjorn,
	Widowmaker,DVa,Orisa,
	Reinhardt,Roadhog,Winston,
	Zarya,Ana,Lucio,//lucio...
	Mercy,Moira,Symmetra,
	Zenyatta, LAST = -1
};

static const enum stringEnum stringMap[] = {
	Doomfist,Genji,McCree,
	Pharah,Reaper,Soldier76,
	Sombra,Tracer,Hanzo,
	Junkrat,Mei,Torbjorn,
	Widowmaker,DVa,Orisa,
	Reinhardt,Roadhog,Winston,
	Zarya,Ana,Lucio,//lucio...
	Mercy,Moira,Symmetra,
	Zenyatta, LAST
};

std::vector < std::pair<std::string, stringEnum> > heroMap;

///MUST BE CALLED AS PART OF INIT PROCESS
void buildHeroMap() {
	for (int i = 0; stringMap[i] != LAST; i++) {
		heroMap[i].first = heroList[i];
		heroMap[i].second = stringMap[i];
	}
}
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

			struct match {
				int medalBronze;
				int medalSilver;
				int medalGold;
				int noMedal;
				int cards;
			};

			struct game {
				int timePlayed;
				int gamesWon;
				int gamesPlayed;
				int gamesTied;
				int gamesLost;
				int gameWinPercent;
			};

			struct combat {
				int heroDamageDone;
				int barrierDamageDone;
				int deaths;
				int objectiveTime;
				int objectiveKills;
				int eliminations;
				int timeOnFire;
			};

			struct averages {
				float winPercent;
				float avgHeroDamage;
				float avgBarrierDamage;
				float avgDeaths;
				float avgObjectiveTime;
				float avgObjectiveKills;
				float avgEliminations;
				float avgTimeOnFire;
			};

			match match;
			averages averages;
			combat combat;
			game game;
	public:
		
		virtual const std::string getName() { return "Uninitialized Hero"; }

		inline void stringifyAllObjects() {
		
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
		{
			
			if (thatIsDamageDealer)
				dpsStats = new damageDealer;
			

			if (thatIsHealer)
				healerStats = new healer;
			

			if (thatIsTank)
				tankStats = new tank;
			
		} //end constructor

		void stringify(int name);
		void updateStats(heroStats old);
		heroStats returnBaseStats() { return this; }
		inline void setBaseStats(std::string* buffer) {

		};
		
		virtual inline void calculateAvgs() {}

		/*the only way to change stats*/
		virtual void updateStats() {}
		void updateBaseStats() {

			for (int index = 0; index < statTable.size(); ++index) {

				//check for special inits first
				if (this->dpsStats) {
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
					//go thru all stats and see if they match
					//find each name and assign to the variable
					if (statTable[index].second.first == "Critical Hits")
						this->dpsStats->criticalHits = statTable[index].second.second;
					
				}

				if (this->healerStats) {
					healerStats = new healer;
				}

				if (this->tankStats) {
					tankStats = new tank;
				}
			}
		}
		heroStats& operator=(const heroStats& other) // copy assignment
		{
			
			return *this;
		}

		virtual ~heroStats() {}
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
		//damage dealer
		heroStats baseStats = new heroStats(false, true, false);

	public:
		const std::string getName() { return "Widowmaker"; }
		widowStats() { }
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