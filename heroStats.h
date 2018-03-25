#pragma once
#include <vector>
//#include "curl_Get.h"

/*nifty c++ trick to turn a var name into a string*/
#define STRINGIFY(name) stringify(#name), (name))
#define NUM_CATEGORIES 12
#define NUM_HEROES 26
#define BUFFER_SIZE 256
typedef std::pair<std::string, std::string> DoubleString;
typedef std::pair<std::string, float>			StatTable;

///HOW STAT TABLE IS FORMATTED:::
//name       type   stat name         #
//Widowmaker Best Kill Streak - Best 24
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
		Σ (all heroes) /	heroSpecificStats - a child struct with additional niche stats for each hero
					   \	base stats held by all heroes

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
		int finalBlowsBestGame;
		int critBestLife;
		int critBestGame;
		int multiKillBest;
		int soloKillsBestGame;


		float soloKillsAvg;
		float multiKillsAvg;
		float accuracyAvg;
		float finalBlowsAvg;
		float critAvg;
		float critPerTen;
		float soloKillsPerTen;
		float multiKillsPerTen;
		float finalBlowsPerTen;
	};

	struct healer {
		int offensiveAssists;
		int	offensiveAssistsMostInGame;
		int defensiveAssists;
		int	defensiveAssistsMostInGame;
		int healingDone;
		int healingDoneMostInGame;

		float healingDoneAvg;
		float defensiveAssistsAvg;
		float offensiveAssistsAvg;
	};

	struct tank {
		int damageBlocked;
		int damageAbsorbed;
		int damageBlockedMostInGame;
		int damageAbsorbedMostInGame;

		float damageBlockedAvg;
		float damageAbsorbedAvg;
		float damageBlockedPerTen;
		float damageAbsorbedPerTen;
	};

	struct match {
		int medalBronze;
		int medalSilver;
		int medalGold;
		int noMedal;
		int cards;
	};

	struct game {
		float timePlayed;
		int gamesWon;
		int gamesPlayed;
		int gamesTied;
		int gamesLost;
		int gameWinPercent;
	};

	struct combat {
		int allDamageDone;
		int heroDamageDone;
		int barrierDamageDone;
		int deaths;
		int objectiveTime;
		int objectiveKills;
		int eliminations;
		int timeOnFire;
		int killStreakBest;

		int eliminationsBestGame;
		int eliminationsBestLife;
		int heroDamageDoneBestLife;
		int heroDamageDoneBestGame;
		int objKillsBestGame;
		int objTimeBestGame;
		int timeOnFireBestGame;
		int allDamageDoneBest;
		int barrierDamageDoneBestGame;

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
		
		float elimsPerLife;

		float heroDamagePerTen;
		float barrierDamagePerTen;
		float deathsPerTen;
		float objTimePerTen;
		float objKillsPerTen;
		float eliminationsPerTen;
		float timeOnFirePerTen;
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

			match match_;
			averages averages_;
			combat combat_;
			game game_;
			
	public:
		
		/*the values the implementer can see*/
		static struct baseStatI {
			match match;
			averages averages;
			combat combat;
			game game;

			const baseStatI updateI(const baseStatI* those) {
				this->match = those->match;
				this->averages = those->averages;
				this->combat = those->combat;
				this->game = those->game;
				return *this;
			}

			baseStatI() {}

			//heroStat copy
			baseStatI(heroStats those) {
				this->match = those.match_;
				this->averages = those.averages_;
				this->combat = those.combat_;
				this->game = those.game_;
			}
		};

		const baseStatI* baseStatInterface = new baseStatI(*this);

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

		void internalSetup(bool thatIsHealer = false, bool thatIsDamageDealer = false, bool thatIsTank = false)
		{
			
			if (thatIsDamageDealer)
				dpsStats = new damageDealer;
			

			if (thatIsHealer)
				healerStats = new healer;
			

			if (thatIsTank)
				tankStats = new tank;
			
		}

		void stringify(int name);
		
		//heroStats returnBaseStats() { return this; }
		inline void setBaseStats(std::string* buffer) {

		};
		
		virtual inline void calculateAvgs() {}

		/*the only way to change stats*/
		virtual void updateStats() {}

		void updateBaseStats(const std::string& name) {

			//cast to minutes
			float timePlayed = this->game_.timePlayed * 60;
			//cast to ten minute intervals
			timePlayed /= 10;

			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == name) {
					//check for special inits first
					if (this->dpsStats) {

						//go thru all stats and see if they match
						//find each name and assign to the variable
						if (statTable[index].second.first == "Critical Hits")
							this->dpsStats->criticalHits = statTable[index].second.second;
						if (statTable[index].second.first == "Solo Kills")
							this->dpsStats->soloKills = statTable[index].second.second;
						if (statTable[index].second.first == "Final Blows")
							this->dpsStats->finalBlows = statTable[index].second.second;
						if (statTable[index].second.first == "Multikills")
							this->dpsStats->multiKills = statTable[index].second.second;
						if (statTable[index].second.first == "Critical Hit Accuracy")
							this->dpsStats->critAcc = statTable[index].second.second;
						if (statTable[index].second.first == "Weapon Accuracy")
							this->dpsStats->weaponAccuracy = statTable[index].second.second;
						if (statTable[index].second.first == "Weapon Accuracy - Best in Game")
							this->dpsStats->weaponAccuracyBestInGame = statTable[index].second.second;
						if (statTable[index].second.first == "Final Blows - Most in Game")
							this->dpsStats->finalBlowsBestGame = statTable[index].second.second;
						if (statTable[index].second.first == "Multikill - Best")
							this->dpsStats->multiKillBest = statTable[index].second.second;
						if (statTable[index].second.first == "Solo Kills - Most in Game")
							this->dpsStats->soloKillsBestGame = statTable[index].second.second;
						if (statTable[index].second.first == "Critical Hits - Most in Game")
							this->dpsStats->critBestGame = statTable[index].second.second;
						if (statTable[index].second.first == "Critical Hits - Most in Life")
							this->dpsStats->critBestLife = statTable[index].second.second;
						if (statTable[index].second.first == "Kill Streak - Best")
							this->dpsStats->bestKillStreak = statTable[index].second.second;

						//dps averages
						this->dpsStats->accuracyAvg = this->dpsStats->weaponAccuracy / (float)this->game_.gamesPlayed;
						this->dpsStats->multiKillsAvg = this->dpsStats->multiKills / (float)this->game_.gamesPlayed;
						this->dpsStats->soloKillsAvg = this->dpsStats->soloKills / (float)this->game_.gamesPlayed;
						this->dpsStats->finalBlowsAvg = this->dpsStats->finalBlows / (float)this->game_.gamesPlayed;
						this->dpsStats->critAvg = this->dpsStats->critAvg / (float)this->game_.gamesPlayed;

						this->dpsStats->critPerTen = this->dpsStats->criticalHits / (float)timePlayed;
						this->dpsStats->soloKillsPerTen = this->dpsStats->soloKills / (float)timePlayed;
						this->dpsStats->multiKillsPerTen = this->dpsStats->multiKills / (float)timePlayed;
						this->dpsStats->finalBlowsPerTen = this->dpsStats->finalBlows / (float)timePlayed;

					}

					if (this->healerStats) {
						healerStats = new healer;
					}

					if (this->tankStats) {
						if (statTable[index].second.first == "Damage Blocked")
							this->tankStats->damageBlocked = statTable[index].second.second;
						if (statTable[index].second.first == "Damage Blocked - Most in Game")
							this->tankStats->damageBlockedMostInGame = statTable[index].second.second;

						//tank avgs
						this->tankStats->damageBlockedAvg = this->tankStats->damageBlocked / (float)this->game_.gamesPlayed;

						this->tankStats->damageBlockedPerTen = this->tankStats->damageBlocked / (float)timePlayed;
					}

					//update universal stats
					//combat
					if (statTable[index].second.first == "Eliminations")
						this->combat_.eliminations = statTable[index].second.second;
					if (statTable[index].second.first == "Deaths")
						this->combat_.deaths = statTable[index].second.second;
					if (statTable[index].second.first == "All Damage Done")
						this->combat_.allDamageDone = statTable[index].second.second;
					if (statTable[index].second.first == "Objective Kills")
						this->combat_.objectiveKills = statTable[index].second.second;
					if (statTable[index].second.first == "Objective Time")
						this->combat_.objectiveTime = statTable[index].second.second;
					if (statTable[index].second.first == "Time Spent on Fire")
						this->combat_.timeOnFire = statTable[index].second.second;
					if (statTable[index].second.first == "Hero Damage Done")
						this->combat_.heroDamageDone = statTable[index].second.second;
					if (statTable[index].second.first == "Barrier Damage Done")
						this->combat_.barrierDamageDone = statTable[index].second.second;
					//match
					if (statTable[index].second.first == "Medals - Bronze")
						this->match_.medalBronze = statTable[index].second.second;
					if (statTable[index].second.first == "Medals - Silver")
						this->match_.medalSilver = statTable[index].second.second;
					if (statTable[index].second.first == "Medals - Gold")
						this->match_.medalGold = statTable[index].second.second;
					if (statTable[index].second.first == "Cards")
						this->match_.cards = statTable[index].second.second;
					//game
					if (statTable[index].second.first == "Time Played")
						this->game_.timePlayed = statTable[index].second.second;
					if (statTable[index].second.first == "Games Played")
						this->game_.gamesPlayed = statTable[index].second.second;
					if (statTable[index].second.first == "Games Won")
						this->game_.gamesWon = statTable[index].second.second;
					if (statTable[index].second.first == "Games Tied")
						this->game_.gamesTied = statTable[index].second.second;
					if (statTable[index].second.first == "Games Lost")
						this->game_.gamesLost = statTable[index].second.second;
					if (statTable[index].second.first == "Win Percentage")
						this->game_.gameWinPercent = statTable[index].second.second;
					//best
					if (statTable[index].second.first == "Eliminations - Most in Life")
						this->combat_.eliminationsBestLife = statTable[index].second.second;
					if (statTable[index].second.first == "Eliminations - Most in Game")
						this->combat_.eliminationsBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Kill Streak - Best")
						this->combat_.killStreakBest = statTable[index].second.second;
					if (statTable[index].second.first == "All Damage Done - Most in Game")
						this->combat_.allDamageDoneBest = statTable[index].second.second;
					if (statTable[index].second.first == "Eliminations - Most in Game")
						this->combat_.eliminationsBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Objective Kills - Most in Game")
						this->combat_.objKillsBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Objective Time - Most in Game")
						this->combat_.objTimeBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Time Spent on Fire - Most in Game")
						this->combat_.timeOnFireBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Hero Damage Done - Most in Game")
						this->combat_.heroDamageDoneBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Hero Damage Done - Most in Life")
						this->combat_.heroDamageDoneBestLife = statTable[index].second.second;
					if (statTable[index].second.first == "Barrier Damage Done - Most in Game")
						this->combat_.barrierDamageDoneBestGame = statTable[index].second.second;
					
					///calculate averages
			
					//Does not factor in ties 
					this->averages_.elimsPerLife	  = this->combat_.eliminations / (float)this->combat_.deaths;
					this->averages_.winPercent		  = this->game_.gamesLost / (float)this->game_.gamesWon;
					this->averages_.avgHeroDamage	  = this->combat_.heroDamageDone / (float)this->game_.gamesPlayed;
					this->averages_.avgBarrierDamage  = this->combat_.barrierDamageDone / (float)this->game_.gamesPlayed;
					this->averages_.avgDeaths		  = this->combat_.deaths / (float)this->game_.gamesPlayed;
					this->averages_.avgObjectiveTime  = this->combat_.objectiveTime / (float)this->game_.gamesPlayed;
					this->averages_.avgObjectiveKills = this->combat_.objectiveKills / (float)this->game_.gamesPlayed;
					this->averages_.avgEliminations	  = this->combat_.eliminations / (float)this->game_.gamesPlayed;
					this->averages_.avgTimeOnFire	  = this->combat_.timeOnFire / (float)this->game_.gamesPlayed;

					this->averages_.barrierDamagePerTen = this->combat_.barrierDamageDone / (float)timePlayed;
					this->averages_.deathsPerTen		= this->combat_.deaths / (float)timePlayed;
					this->averages_.eliminationsPerTen  = this->combat_.eliminations / (float)timePlayed;
					this->averages_.heroDamagePerTen	= this->combat_.heroDamageDone / (float)timePlayed;
					this->averages_.objKillsPerTen		= this->combat_.objectiveKills / (float)timePlayed;
					this->averages_.objTimePerTen		= this->combat_.objectiveTime / (float)timePlayed;
					this->averages_.timeOnFirePerTen	= this->combat_.timeOnFire / (float)timePlayed;

					//this->baseStatInterface = nullptr;
					this->baseStatInterface = new baseStatI(*this);
				}
			}
		}



	/*	heroStats& operator=(const heroStats& other) // copy assignment
		{
			
			return *this;
		}
		*/
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

			float venomMineKillsPerTen;
			float scopedCriticalHitsPerTen;
			float reconAssistsPerTen;
		};

		/*the values the implementer can see*/
		struct widowStatInterface {
			widowSpecificStats specificStats;
			widowAvgStats avgStats;
			baseStatI baseStats;
			widowStatInterface(widowStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats		= those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		widowSpecificStats theseWidowStats;
		widowAvgStats theseWidowAvgStats;

	public:
		const std::string getName() { return "Widowmaker"; }
		widowStats() { internalSetup(false, true, false); }
		const widowSpecificStats getSpecific()  const { return this->theseWidowStats; }
		const widowAvgStats	     getAvgStats()  const { return this->theseWidowAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const widowStatInterface* statInterface = new widowStatInterface(*this);
	
		void updateStats() override {
			
			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Venom Mine Kills")
						this->theseWidowStats.venomMineKills = statTable[index].second.second;
					if (statTable[index].second.first == "Scoped Critical Hits")
						this->theseWidowStats.scopedCriticalHits = statTable[index].second.second;
					if (statTable[index].second.first == "Scoped Critical Hits - Most in Game")
						this->theseWidowStats.scopedCriticalHitsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Venom Mine Kills - Most in Game")
						this->theseWidowStats.VenomMineKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Scoped Accuracy - Best in Game")
						this->theseWidowStats.scopedAccuracyBestInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Scoped Accuracy")
						this->theseWidowStats.scopedAccuracy = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->theseWidowAvgStats.scopedCriticalHitsPerTen = this->theseWidowStats.scopedCriticalHits / (float)timePlayed;
			this->theseWidowAvgStats.reconAssistsPerTen = this->theseWidowStats.reconAssists / (float)timePlayed;
			this->theseWidowAvgStats.venomMineKillsPerTen = this->theseWidowStats.venomMineKills / (float)timePlayed;

			this->theseWidowAvgStats.venomMineKillsAvg = this->theseWidowStats.venomMineKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseWidowAvgStats.reconAssistsAvg = this->theseWidowStats.reconAssists / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseWidowAvgStats.scopedCriticalHitsAvg = this->theseWidowStats.scopedCriticalHits / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new widowStatInterface(*this);
		}
	};

	class genjiStats : public heroStats {

	private:
		struct genjiSpecificStats {
			int dragonBladeKills;
			int damageReflected;
			int dragonBladeKillsMostInGame;
			int damageReflectedMostInGame;
		};

		struct genjiAvgStats {
			float dragonBladeKillsAvg;
			float dragonBladeKillsPerTen;
			float damageReflectedAvg;
			float damageReflectedPerTen;
		};

		/*the values the implementer can see*/
		struct genjiStatInterface {
			genjiSpecificStats specificStats;
			genjiAvgStats avgStats;
			baseStatI baseStats;
			genjiStatInterface(genjiStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats		= those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		genjiSpecificStats thesegenjiStats;
		genjiAvgStats thesegenjiAvgStats;

	public:
		const std::string getName() { return "Genji"; }
		genjiStats() { internalSetup(false, true, false); }
		const genjiSpecificStats getSpecific()  const { return this->thesegenjiStats; }
		const genjiAvgStats	     getAvgStats()  const { return this->thesegenjiAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const genjiStatInterface* statInterface = new genjiStatInterface(*this);

		void updateStats() override {
			
			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Dragonblade Kills")
						this->thesegenjiStats.dragonBladeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Dragonblade Kills - Most in Game")
						this->thesegenjiStats.dragonBladeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Reflected")
						this->thesegenjiStats.damageReflected = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Reflected - Most in Game")
						this->thesegenjiStats.damageReflectedMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesegenjiAvgStats.damageReflectedPerTen = this->thesegenjiStats.damageReflected / (float)timePlayed;
			this->thesegenjiAvgStats.dragonBladeKillsPerTen = this->thesegenjiStats.dragonBladeKills / (float)timePlayed;

			this->thesegenjiAvgStats.damageReflectedAvg = this->thesegenjiStats.damageReflected / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesegenjiAvgStats.dragonBladeKillsAvg = this->thesegenjiStats.dragonBladeKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new genjiStatInterface(*this);
		}
	};

	class doomfistStats : public heroStats {

	private:
		struct doomfistSpecificStats {
			float abilityDamageDone;
			float abilityDamageDoneMostInGame;
			int meteorStrikeKills;
			int meteorStrikeKillsMostInGame;
			float shieldsCreated;
			float shieldsCreatedMostInGame;
		};

		struct doomfistAvgStats {
			float abilityDamageDoneAvg;
			float meteorStrikeKillsAvg;
			float shieldsCreatedAvg;
			float abilityDamageDonePerTen;
			float meteorStrikeKillsPerTen;
			float shieldsCreatedPerTen;
		};

		/*the values the implementer can see*/
		struct doomfistStatInterface {
			doomfistSpecificStats specificStats;
			doomfistAvgStats avgStats;
			baseStatI baseStats;
			doomfistStatInterface(doomfistStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		doomfistSpecificStats thesedoomfistStats;
		doomfistAvgStats thesedoomfistAvgStats;

	public:
		const std::string getName() { return "Doomfist"; }
		doomfistStats() { internalSetup(false, true, false); }
		const doomfistSpecificStats getSpecific()  const { return this->thesedoomfistStats; }
		const doomfistAvgStats	     getAvgStats()  const { return this->thesedoomfistAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const doomfistStatInterface* statInterface = new doomfistStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Ability Damage Done")
						this->thesedoomfistStats.abilityDamageDone = statTable[index].second.second;
					if (statTable[index].second.first == "Ability Damage Done - Most in Game")
						this->thesedoomfistStats.abilityDamageDoneMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Meteor Strike Kills")
						this->thesedoomfistStats.meteorStrikeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Meteor Strike Kills - Most in Game")
						this->thesedoomfistStats.meteorStrikeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Shields Created")
						this->thesedoomfistStats.shieldsCreated = statTable[index].second.second;
					if (statTable[index].second.first == "Shields Created - Most in Game")
						this->thesedoomfistStats.shieldsCreatedMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesedoomfistAvgStats.abilityDamageDonePerTen = this->thesedoomfistStats.abilityDamageDone / (float)timePlayed;
			this->thesedoomfistAvgStats.meteorStrikeKillsPerTen = this->thesedoomfistStats.meteorStrikeKills / (float)timePlayed;
			this->thesedoomfistAvgStats.shieldsCreatedPerTen = this->thesedoomfistStats.shieldsCreated / (float)timePlayed;

			this->thesedoomfistAvgStats.abilityDamageDoneAvg = this->thesedoomfistStats.abilityDamageDone / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesedoomfistAvgStats.meteorStrikeKillsAvg = this->thesedoomfistStats.meteorStrikeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesedoomfistAvgStats.shieldsCreatedAvg = this->thesedoomfistStats.shieldsCreated / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new doomfistStatInterface(*this);
		}
	};

	class mccreeStats : public heroStats {

	private:
		struct mccreeSpecificStats {
			int deadeyeKills;
			int deadeyeKillsMostInGame;
			int fanTheHammerKills;
			int fanTheHammerKillsMostInGame;
		};

		struct mccreeAvgStats {
			float deadeyeKillsAvg;
			float deadeyeKillsPerTen;
			float fanTheHammerKillsAvg;
			float fanTheHammerKillsPerTen;
		};

		/*the values the implementer can see*/
		struct mccreeStatInterface {
			mccreeSpecificStats specificStats;
			mccreeAvgStats avgStats;
			baseStatI baseStats;
			mccreeStatInterface(mccreeStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		mccreeSpecificStats thesemccreeStats;
		mccreeAvgStats thesemccreeAvgStats;

	public:
		const std::string getName() { return "McCree"; }
		mccreeStats() { internalSetup(false, true, false); }
		const mccreeSpecificStats getSpecific()  const { return this->thesemccreeStats; }
		const mccreeAvgStats	     getAvgStats()  const { return this->thesemccreeAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const mccreeStatInterface* statInterface = new mccreeStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Deadeye Kills")
						this->thesemccreeStats.deadeyeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Deadeye Kills - Most in Game")
						this->thesemccreeStats.deadeyeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Fan the Hammer Kills")
						this->thesemccreeStats.fanTheHammerKills = statTable[index].second.second;
					if (statTable[index].second.first == "Fan the Hammer Kills - Most in Game")
						this->thesemccreeStats.fanTheHammerKillsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesemccreeAvgStats.deadeyeKillsPerTen = this->thesemccreeStats.deadeyeKills / (float)timePlayed;
			this->thesemccreeAvgStats.fanTheHammerKillsPerTen = this->thesemccreeStats.fanTheHammerKills / (float)timePlayed;

			this->thesemccreeAvgStats.deadeyeKillsAvg = this->thesemccreeStats.deadeyeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemccreeAvgStats.fanTheHammerKillsAvg = this->thesemccreeStats.fanTheHammerKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new mccreeStatInterface(*this);
		}
	};

	class pharahStats : public heroStats {

	private:
		struct pharahSpecificStats {
			int rocketDirectHits;
			int rocketDirectHitsMostInGame;
			int barrageKills;
			int barrageKillsMostInGame;
		};

		struct pharahAvgStats {
			float barrageKillsAvg;
			float barrageKillsPerTen;
			float rocketDirectHitsAvg;
			float rocketDirectHitsPerTen;
		};

		/*the values the implementer can see*/
		struct pharahStatInterface {
			pharahSpecificStats specificStats;
			pharahAvgStats avgStats;
			baseStatI baseStats;
			pharahStatInterface(pharahStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		pharahSpecificStats thesepharahStats;
		pharahAvgStats thesepharahAvgStats;

	public:
		const std::string getName() { return "Pharah"; }
		pharahStats() { internalSetup(false, true, false); }
		const pharahSpecificStats getSpecific()  const { return this->thesepharahStats; }
		const pharahAvgStats	     getAvgStats()  const { return this->thesepharahAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const pharahStatInterface* statInterface = new pharahStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Barrage Kills")
						this->thesepharahStats.barrageKills = statTable[index].second.second;
					if (statTable[index].second.first == "Barrage Kills - Most in Game")
						this->thesepharahStats.barrageKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Rocket Direct Hits")
						this->thesepharahStats.rocketDirectHits = statTable[index].second.second;
					if (statTable[index].second.first == "Rocket Direct Hits - Most in Game")
						this->thesepharahStats.rocketDirectHitsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesepharahAvgStats.barrageKillsPerTen = this->thesepharahStats.barrageKills / (float)timePlayed;
			this->thesepharahAvgStats.rocketDirectHitsPerTen = this->thesepharahStats.rocketDirectHits / (float)timePlayed;

			this->thesepharahAvgStats.barrageKillsAvg = this->thesepharahStats.barrageKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesepharahAvgStats.rocketDirectHitsAvg = this->thesepharahStats.rocketDirectHits / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new pharahStatInterface(*this);
		}
	};

	class reaperStats : public heroStats {

	private:
		struct reaperSpecificStats {
			int deathBlossomKills;
			int deathBlossomKillsMostInGame;
			int selfHealing;
			int selfHealingMostInGame;
		};

		struct reaperAvgStats {
			float deathBlossomKillsAvg;
			float deathBlossomKillsPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
		};

		/*the values the implementer can see*/
		struct reaperStatInterface {
			reaperSpecificStats specificStats;
			reaperAvgStats avgStats;
			baseStatI baseStats;
			reaperStatInterface(reaperStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		reaperSpecificStats thesereaperStats;
		reaperAvgStats thesereaperAvgStats;

	public:
		const std::string getName() { return "Reaper"; }
		reaperStats() { internalSetup(false, true, false); }
		const reaperSpecificStats getSpecific()  const { return this->thesereaperStats; }
		const reaperAvgStats	     getAvgStats()  const { return this->thesereaperAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const reaperStatInterface* statInterface = new reaperStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Death Blossom Kills")
						this->thesereaperStats.deathBlossomKills = statTable[index].second.second;
					if (statTable[index].second.first == "Death Blossom Kills - Most in Game")
						this->thesereaperStats.deathBlossomKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->thesereaperStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->thesereaperStats.selfHealingMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesereaperAvgStats.selfHealingPerTen = this->thesereaperStats.selfHealing / (float)timePlayed;
			this->thesereaperAvgStats.deathBlossomKillsPerTen = this->thesereaperStats.deathBlossomKills / (float)timePlayed;

			this->thesereaperAvgStats.selfHealingAvg = this->thesereaperStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesereaperAvgStats.deathBlossomKillsAvg = this->thesereaperStats.deathBlossomKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new reaperStatInterface(*this);
		}
	};

	class soldierStats : public heroStats {

	private:
		struct soldierSpecificStats {
			int helixRocketKills;
			int helixRocketKillsMostInGame;
			int tacVisorKills;
			int tacVisorKillsMostInGame;
			int bioticFieldsDeployed;
			int bioticFieldHealingDone;
			int selfHealing;
			int selfHealingMostInGame;
		};

		struct soldierAvgStats {
			float helixRocketKillsAvg;
			float helixRocketKillsPerTen;
			float tacVisorKillsAvg;
			float tacVisorKillsPerTen;
			float bioticFieldsDeployedAvg;
			float bioticFieldsDeployedPerTen;
			float bioticFieldHealingDoneAvg;
			float bioticFieldHealingPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
		};

		/*the values the implementer can see*/
		struct soldierStatInterface {
			soldierSpecificStats specificStats;
			soldierAvgStats avgStats;
			baseStatI baseStats;
			soldierStatInterface(soldierStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		soldierSpecificStats thesesoldierStats;
		soldierAvgStats thesesoldierAvgStats;

	public:
		const std::string getName() { return "Soldier: 76"; }
		soldierStats() { internalSetup(false, true, false); }
		const soldierSpecificStats getSpecific()  const { return this->thesesoldierStats; }
		const soldierAvgStats	     getAvgStats()  const { return this->thesesoldierAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const soldierStatInterface* statInterface = new soldierStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Helix Rockets Kills - Most in Game")
						this->thesesoldierStats.helixRocketKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Helix Rockets Kills")
						this->thesesoldierStats.helixRocketKills = statTable[index].second.second;
					if (statTable[index].second.first == "Tactical Visor Kills")
						this->thesesoldierStats.tacVisorKills = statTable[index].second.second;
					if (statTable[index].second.first == "Tactical Visor Kills - Most in Game")
						this->thesesoldierStats.tacVisorKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Biotic Fields Deployed 188")
						this->thesesoldierStats.bioticFieldsDeployed = statTable[index].second.second;
					if (statTable[index].second.first == "Biotic Field Healing Done")
						this->thesesoldierStats.bioticFieldHealingDone = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->thesesoldierStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->thesesoldierStats.selfHealingMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;
			
			this->thesesoldierAvgStats.selfHealingPerTen = this->thesesoldierStats.selfHealing / (float)timePlayed;
			this->thesesoldierAvgStats.helixRocketKillsPerTen = this->thesesoldierStats.helixRocketKills / (float)timePlayed;
			this->thesesoldierAvgStats.bioticFieldHealingPerTen = this->thesesoldierStats.bioticFieldHealingDone / (float)timePlayed;
			this->thesesoldierAvgStats.bioticFieldsDeployedPerTen = this->thesesoldierStats.bioticFieldsDeployed / (float)timePlayed;
			this->thesesoldierAvgStats.tacVisorKillsPerTen = this->thesesoldierStats.tacVisorKills / (float)timePlayed;

			this->thesesoldierAvgStats.selfHealingAvg = this->thesesoldierStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesesoldierAvgStats.helixRocketKillsAvg = this->thesesoldierStats.helixRocketKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesesoldierAvgStats.bioticFieldHealingPerTen = this->thesesoldierStats.bioticFieldHealingDone / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesesoldierAvgStats.bioticFieldsDeployedAvg = this->thesesoldierStats.bioticFieldsDeployed / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesesoldierAvgStats.tacVisorKillsAvg = this->thesesoldierStats.tacVisorKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new soldierStatInterface(*this);
		}
	};

	class sombraStats : public heroStats {

	private:
		struct sombraSpecificStats {
			int enemiesHacked;
			int enemiesEMPd;
			int enemiesHackedMostInGame;
			int enemiesEMPdMostInGame;
		};

		struct sombraAvgStats {
			float enemiesHackedAvg;
			float enemiesHackedPerTen;
			float enemiesEMPdAvg;
			float enemiesEMPdPerTen;
		};

		/*the values the implementer can see*/
		struct sombraStatInterface {
			sombraSpecificStats specificStats;
			sombraAvgStats avgStats;
			baseStatI baseStats;
			sombraStatInterface(sombraStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		sombraSpecificStats thesesombraStats;
		sombraAvgStats thesesombraAvgStats;

	public:
		const std::string getName() { return "Sombra"; }
		sombraStats() { internalSetup(true, true, false); }
		const sombraSpecificStats getSpecific()  const { return this->thesesombraStats; }
		const sombraAvgStats	     getAvgStats()  const { return this->thesesombraAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const sombraStatInterface* statInterface = new sombraStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Enemies Hacked")
						this->thesesombraStats.enemiesHacked = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies EMP'd")
						this->thesesombraStats.enemiesEMPd = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies Hacked - Most in Game")
						this->thesesombraStats.enemiesHackedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies EMP'd - Most in Game")
						this->thesesombraStats.enemiesEMPdMostInGame = statTable[index].second.second;
				}
			}

				//cast to minutes
				float timePlayed = this->baseStatInterface->game.timePlayed * 60;
				//no need to process
				if (timePlayed == 0.0) return;
				//cast to ten minute intervals
				timePlayed /= 10;

				this->thesesombraAvgStats.enemiesEMPdPerTen = this->thesesombraStats.enemiesEMPd / (float)timePlayed;
				this->thesesombraAvgStats.enemiesHackedPerTen = this->thesesombraStats.enemiesHacked / (float)timePlayed;

				this->thesesombraAvgStats.enemiesEMPdAvg = this->thesesombraStats.enemiesEMPd / (float)this->baseStatInterface->game.gamesPlayed;
				this->thesesombraAvgStats.enemiesHackedAvg = this->thesesombraStats.enemiesHacked / (float)this->baseStatInterface->game.gamesPlayed;


				this->statInterface = new sombraStatInterface(*this);
		}
	};

	class tracerStats : public heroStats {

	private:
		struct tracerSpecificStats {
			int pulseBombKills;
			int pulseBombKillsMostInGame;
			int pulseBombsAttached;
			int pulseBombsAttachedMostInGame;
			int selfHealing;
			int selfHealingMostInGame;
			int healthRecovered;
			int healthRecoveredMostInGame;
		};

		struct tracerAvgStats {
			float pulseBombKillsAvg;
			float pulseBombKillsPerTen;
			float pulseBombKillsAttachedAvg;
			float pulseBombKillsAttachedPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
			float healthRecoveredAvg;
			float healthRecoveredPerTen;
		};

		/*the values the implementer can see*/
		struct tracerStatInterface {
			tracerSpecificStats specificStats;
			tracerAvgStats avgStats;
			baseStatI baseStats;
			tracerStatInterface(tracerStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		tracerSpecificStats thesetracerStats;
		tracerAvgStats thesetracerAvgStats;

	public:
		const std::string getName() { return "Tracer"; }
		tracerStats() { internalSetup(false, true, false); }
		const tracerSpecificStats getSpecific()  const { return this->thesetracerStats; }
		const tracerAvgStats	     getAvgStats()  const { return this->thesetracerAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const tracerStatInterface* statInterface = new tracerStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Pulse Bomb Kills")
						this->thesetracerStats.pulseBombKills = statTable[index].second.second;
					if (statTable[index].second.first == "Pulse Bomb Kills - Most in Game")
						this->thesetracerStats.pulseBombKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Pulse Bombs Attached")
						this->thesetracerStats.pulseBombsAttached = statTable[index].second.second;
					if (statTable[index].second.first == "Pulse Bombs Attached - Most in Game")
						this->thesetracerStats.pulseBombsAttachedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->thesetracerStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->thesetracerStats.selfHealingMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Health Recovered")
						this->thesetracerStats.healthRecovered = statTable[index].second.second;
					if (statTable[index].second.first == "Health Recovered - Most in Game")
						this->thesetracerStats.healthRecoveredMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesetracerAvgStats.healthRecoveredPerTen = this->thesetracerStats.healthRecovered / (float)timePlayed;
			this->thesetracerAvgStats.selfHealingPerTen = this->thesetracerStats.selfHealing / (float)timePlayed;
			this->thesetracerAvgStats.pulseBombKillsAttachedPerTen = this->thesetracerStats.pulseBombsAttached / (float)timePlayed;
			this->thesetracerAvgStats.pulseBombKillsPerTen = this->thesetracerStats.pulseBombKills / (float)timePlayed;

			this->thesetracerAvgStats.healthRecoveredAvg = this->thesetracerStats.healthRecovered / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesetracerAvgStats.selfHealingAvg = this->thesetracerStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesetracerAvgStats.pulseBombKillsAttachedAvg = this->thesetracerStats.pulseBombsAttached / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesetracerAvgStats.pulseBombKillsAvg = this->thesetracerStats.pulseBombKills / (float)this->baseStatInterface->game.gamesPlayed;


			this->statInterface = new tracerStatInterface(*this);
		}
	};
	
	class hanzoStats : public heroStats {

	private:
		struct hanzoSpecificStats {
			int dragonStrikeKills;
			int dragonStrikeKillsMostInGame;
			int scatterArrowKills;
			int scatterArrowKillsMostInGame;
		};

		struct hanzoAvgStats {
			float dragonStrikeKillsAvg;
			float dragonStrikeKillsPerTen;
			float scatterArrowKillsAvg;
			float scatterArrowKillsPerTen;
		};

		/*the values the implementer can see*/
		struct hanzoStatInterface {
			hanzoSpecificStats specificStats;
			hanzoAvgStats avgStats;
			baseStatI baseStats;
			hanzoStatInterface(hanzoStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		hanzoSpecificStats thesehanzoStats;
		hanzoAvgStats thesehanzoAvgStats;

	public:
		const std::string getName() { return "Hanzo"; }
		hanzoStats() { internalSetup(false, true, false); }
		const hanzoSpecificStats getSpecific()  const { return this->thesehanzoStats; }
		const hanzoAvgStats	     getAvgStats()  const { return this->thesehanzoAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const hanzoStatInterface* statInterface = new hanzoStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Dragonstrike Kills")
						this->thesehanzoStats.dragonStrikeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Dragonstrike Kills - Most in Game")
						this->thesehanzoStats.dragonStrikeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Scatter Arrow Kills")
						this->thesehanzoStats.scatterArrowKills = statTable[index].second.second;
					if (statTable[index].second.first == "Scatter Arrow Kills - Most in Game")
						this->thesehanzoStats.scatterArrowKillsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesehanzoAvgStats.dragonStrikeKillsPerTen = this->thesehanzoStats.dragonStrikeKills / (float)timePlayed;
			this->thesehanzoAvgStats.scatterArrowKillsPerTen = this->thesehanzoStats.scatterArrowKills / (float)timePlayed;

			this->thesehanzoAvgStats.dragonStrikeKillsAvg = this->thesehanzoStats.dragonStrikeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesehanzoAvgStats.scatterArrowKillsAvg = this->thesehanzoStats.scatterArrowKills / (float)this->baseStatInterface->game.gamesPlayed;


			this->statInterface = new hanzoStatInterface(*this);
		}
	};

	class junkratStats : public heroStats {

	private:
		struct junkratSpecificStats {
			int enemiesTrapped;
			int enemiesTrappedMostInGame;
			int RIPtireKills;
			int RIPtireKillsMostInGame;
			int concussionMineKills;
			int concussionMineKillsMostInGame;
		};

		struct junkratAvgStats {
			float enemiesTrappedAvg;
			float enemiesTrappedPerTen;
			float RIPtireKillsAvg;
			float RIPtireKillsPerTen;
			float concussionMineKillsAvg;
			float concussionMineKillsPerTen;
		};

		/*the values the implementer can see*/
		struct junkratStatInterface {
			junkratSpecificStats specificStats;
			junkratAvgStats avgStats;
			baseStatI baseStats;
			junkratStatInterface(junkratStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		junkratSpecificStats thesejunkratStats;
		junkratAvgStats thesejunkratAvgStats;

	public:
		const std::string getName() { return "Junkrat"; }
		junkratStats() { internalSetup(false, true, false); }
		const junkratSpecificStats getSpecific()  const { return this->thesejunkratStats; }
		const junkratAvgStats	     getAvgStats()  const { return this->thesejunkratAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const junkratStatInterface* statInterface = new junkratStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Enemies Trapped - Most in Game")
						this->thesejunkratStats.enemiesTrappedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies Trapped")
						this->thesejunkratStats.enemiesTrapped = statTable[index].second.second;
					if (statTable[index].second.first == "RIP-Tire Kills - Most in Game")
						this->thesejunkratStats.RIPtireKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "RIP-Tire Kills")
						this->thesejunkratStats.RIPtireKills = statTable[index].second.second;
					if (statTable[index].second.first == "Concussion Mine Kills")
						this->thesejunkratStats.concussionMineKills = statTable[index].second.second;
					if (statTable[index].second.first == "Concussion Mine Kills - Most in Game")
						this->thesejunkratStats.concussionMineKillsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesejunkratAvgStats.concussionMineKillsPerTen = this->thesejunkratStats.concussionMineKills / (float)timePlayed;
			this->thesejunkratAvgStats.RIPtireKillsPerTen = this->thesejunkratStats.RIPtireKills / (float)timePlayed;
			this->thesejunkratAvgStats.enemiesTrappedPerTen = this->thesejunkratStats.enemiesTrapped / (float)timePlayed;

			this->thesejunkratAvgStats.concussionMineKillsAvg = this->thesejunkratStats.concussionMineKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesejunkratAvgStats.RIPtireKillsAvg = this->thesejunkratStats.RIPtireKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesejunkratAvgStats.enemiesTrappedAvg = this->thesejunkratStats.enemiesTrapped / (float)this->baseStatInterface->game.gamesPlayed;


			this->statInterface = new junkratStatInterface(*this);
		}
	};

	class meiStats : public heroStats {

	private:
		struct meiSpecificStats {
			int enemiesFrozen;
			int enemiesFrozenMostInGame;
			int blizzardKills;
			int blizzardKillsMostInGame;

			int selfHealing;
			int selfHealingMostInGame;
			
		};

		struct meiAvgStats {
			float enemiesFrozenAvg;
			float enemiesFrozenPerTen;
			float blizzardKillsAvg;
			float blizzardKillsPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
		};

		/*the values the implementer can see*/
		struct meiStatInterface {
			meiSpecificStats specificStats;
			meiAvgStats avgStats;
			baseStatI baseStats;
			meiStatInterface(meiStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		meiSpecificStats thesemeiStats;
		meiAvgStats thesemeiAvgStats;

	public:
		const std::string getName() { return "Mei"; }
		meiStats() { internalSetup(false, true, true); }
		const meiSpecificStats getSpecific()  const { return this->thesemeiStats; }
		const meiAvgStats	     getAvgStats()  const { return this->thesemeiAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const meiStatInterface* statInterface = new meiStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Enemies Frozen")
						this->thesemeiStats.enemiesFrozen = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies Frozen - Most in Game")
						this->thesemeiStats.enemiesFrozenMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Blizzard Kills - Most in Game")
						this->thesemeiStats.blizzardKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Blizzard Kills")
						this->thesemeiStats.blizzardKills = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->thesemeiStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->thesemeiStats.selfHealingMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesemeiAvgStats.enemiesFrozenPerTen = this->thesemeiStats.enemiesFrozen / (float)timePlayed;
			this->thesemeiAvgStats.blizzardKillsPerTen = this->thesemeiStats.blizzardKills / (float)timePlayed;
			this->thesemeiAvgStats.selfHealingPerTen = this->thesemeiStats.selfHealing / (float)timePlayed;

			this->thesemeiAvgStats.enemiesFrozenAvg = this->thesemeiStats.enemiesFrozen / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemeiAvgStats.blizzardKillsAvg = this->thesemeiStats.blizzardKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemeiAvgStats.selfHealingAvg = this->thesemeiStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;


			this->statInterface = new meiStatInterface(*this);
		}
	};

	class torbjornStats : public heroStats {

	private:
		struct torbjornSpecificStats {
			int armorPacksCreated;
			int armorPacksCreatedMostInGame;
			int torbKills;
			int torbKillsMostInGame;
			int turretKills;
			int turretKillsMostInGame;
			int moltenCoreKills;
			int moltenCoreKillsMostInGame;
		};

		struct torbjornAvgStats {
			float armorPacksCreatedAvg;
			float armorPacksCreatedPerTen;
			float torbKillsAvg;
			float torbKillsPerTen;
			float turretKillsAvg;
			float turretKillsPerTen;
			float moltenCoreKillsAvg;
			float moltenCoreKillsPerTen;
		};

		/*the values the implementer can see*/
		struct torbjornStatInterface {
			torbjornSpecificStats specificStats;
			torbjornAvgStats avgStats;
			baseStatI baseStats;
			torbjornStatInterface(torbjornStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		torbjornSpecificStats thesetorbjornStats;
		torbjornAvgStats thesetorbjornAvgStats;

	public:
		const std::string getName() { return "TorbjÃ¶rn"; }
		torbjornStats() { internalSetup(false, true, false); }
		const torbjornSpecificStats getSpecific()  const { return this->thesetorbjornStats; }
		const torbjornAvgStats	     getAvgStats()  const { return this->thesetorbjornAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const torbjornStatInterface* statInterface = new torbjornStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Armor Packs Created")
						this->thesetorbjornStats.armorPacksCreated = statTable[index].second.second;
					if (statTable[index].second.first == "TorbjÃ¶rn Kills")
						this->thesetorbjornStats.torbKills = statTable[index].second.second;
					if (statTable[index].second.first == "TorbjÃ¶rn Kills - Most in Game")
						this->thesetorbjornStats.torbKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Turret Kills")
						this->thesetorbjornStats.turretKills = statTable[index].second.second;
					if (statTable[index].second.first == "Armor Packs Created - Most in Game")
						this->thesetorbjornStats.armorPacksCreatedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Turret Kills - Most in Game")
						this->thesetorbjornStats.turretKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Molten Core Kills")
						this->thesetorbjornStats.moltenCoreKills = statTable[index].second.second;
					if (statTable[index].second.first == "Molten Core Kills - Most in Game")
						this->thesetorbjornStats.moltenCoreKillsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesetorbjornAvgStats.torbKillsPerTen = this->thesetorbjornStats.torbKills / (float)timePlayed;
			this->thesetorbjornAvgStats.armorPacksCreatedPerTen = this->thesetorbjornStats.armorPacksCreated / (float)timePlayed;
			this->thesetorbjornAvgStats.turretKillsPerTen = this->thesetorbjornStats.turretKills / (float)timePlayed;
			this->thesetorbjornAvgStats.moltenCoreKillsPerTen = this->thesetorbjornStats.moltenCoreKills / (float)timePlayed;

			this->thesetorbjornAvgStats.torbKillsAvg = this->thesetorbjornStats.torbKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesetorbjornAvgStats.armorPacksCreatedAvg = this->thesetorbjornStats.armorPacksCreated / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesetorbjornAvgStats.turretKillsAvg = this->thesetorbjornStats.turretKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesetorbjornAvgStats.moltenCoreKillsAvg = this->thesetorbjornStats.moltenCoreKills / (float)this->baseStatInterface->game.gamesPlayed;


			this->statInterface = new torbjornStatInterface(*this);
		}
	};