#pragma once
#include <vector>
//#include "curl_Get.h"
///TODO: CHECK FOR ENVIORNMENTAL KILLS AND OTHER STUFF THAT IS HERO SPECIFIC BUT NOT IN HERO SPECIFIC
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
		int criticalHits;
		int critAcc;
		int weaponAccuracy;

		int weaponAccuracyBestInGame;
		int bestKillStreak;
		int critBestLife;
		int critBestGame;

		float accuracyAvg;
		float critAvg;
		float critPerTen;
	
	};

	struct healer {
		int offensiveAssists;
		int	offensiveAssistsMostInGame;
		int defensiveAssists;
		int	defensiveAssistsMostInGame;
		int healingDone;
		int healingDoneMostInGame;

		float healingDonePerTen;
		float offensiveAssistsPerTen;
		float defensiveAssistsPerTen;
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
		int soloKills;
		int allDamageDone;
		int heroDamageDone;
		int barrierDamageDone;
		int deaths;
		int objectiveTime;
		int objectiveKills;
		int eliminations;
		int timeOnFire;
		int killStreakBest;
		int finalBlows;
		int multiKills;
		int environmentalKills;

		int soloKillsBestGame;
		int finalBlowsBestGame;
		int multiKillsBestGame;
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
		float avgSoloKills;
		float avgMultiKills;
		float avgFinalBlows;
		float avgEnvironmentalKills;
		
		float elimsPerLife;

		float environmentalKillsPerTen;
		float finalBlowsPerTen;
		float multiKillsPerTen;
		float soloKillsPerTen;
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
			damageDealer* dpsInterface;
			tank* tankInterface;
			healer* healInterface;
			const baseStatI updateI(const baseStatI* those) {
				this->tankInterface = those->tankInterface;
				this->dpsInterface = those->dpsInterface;
				this->healInterface = those->healInterface;
				this->match = those->match;
				this->averages = those->averages;
				this->combat = those->combat;
				this->game = those->game;
				return *this;
			}

			baseStatI() {}

			//heroStat copy
			baseStatI(heroStats those) {
				if (those.dpsStats) {
					this->dpsInterface = new damageDealer;
					this->dpsInterface = those.dpsStats;
				}
				if (those.tankStats) {
					this->tankInterface = new tank;
					this->tankInterface = those.tankStats;
				}
				if (those.healerStats) {
					this->healInterface = new healer;
					this->healInterface = those.healerStats;
				}
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
						
						if (statTable[index].second.first == "Critical Hit Accuracy")
							this->dpsStats->critAcc = statTable[index].second.second;
						if (statTable[index].second.first == "Weapon Accuracy")
							this->dpsStats->weaponAccuracy = statTable[index].second.second;
						if (statTable[index].second.first == "Weapon Accuracy - Best in Game")
							this->dpsStats->weaponAccuracyBestInGame = statTable[index].second.second;
						if (statTable[index].second.first == "Critical Hits - Most in Game")
							this->dpsStats->critBestGame = statTable[index].second.second;
						if (statTable[index].second.first == "Critical Hits - Most in Life")
							this->dpsStats->critBestLife = statTable[index].second.second;
						if (statTable[index].second.first == "Kill Streak - Best")
							this->dpsStats->bestKillStreak = statTable[index].second.second;

						//dps averages
						this->dpsStats->accuracyAvg = this->dpsStats->weaponAccuracy / (float)this->game_.gamesPlayed;
						this->dpsStats->critAvg = this->dpsStats->critAvg / (float)this->game_.gamesPlayed;

						this->dpsStats->critPerTen = this->dpsStats->criticalHits / (float)timePlayed;

					}

					if (this->healerStats) {
						if (statTable[index].second.first == "Healing Done")
							this->healerStats->healingDone = statTable[index].second.second;
						if (statTable[index].second.first == "Healing Done - Most in Game")
							this->healerStats->healingDoneMostInGame = statTable[index].second.second;
						if (statTable[index].second.first == "Offensive Assists")
							this->healerStats->offensiveAssists = statTable[index].second.second;
						if (statTable[index].second.first == "Defensive Assists")
							this->healerStats->defensiveAssists = statTable[index].second.second;
						if (statTable[index].second.first == "Offensive Assists - Most in Game")
							this->healerStats->offensiveAssistsMostInGame = statTable[index].second.second;
						if (statTable[index].second.first == "Defensive Assists - Most in Game")
							this->healerStats->defensiveAssistsMostInGame = statTable[index].second.second;

						//tank avgs
						this->healerStats->healingDoneAvg = this->healerStats->healingDone / (float)this->game_.gamesPlayed;
						this->healerStats->offensiveAssistsAvg = this->healerStats->offensiveAssists / (float)this->game_.gamesPlayed;
						this->healerStats->defensiveAssistsAvg = this->healerStats->healingDone / (float)this->game_.gamesPlayed;

						this->healerStats->healingDonePerTen = this->healerStats->healingDone / (float)timePlayed;
						this->healerStats->offensiveAssistsPerTen = this->healerStats->offensiveAssists / (float)timePlayed;
						this->healerStats->defensiveAssists = this->healerStats->defensiveAssists / (float)timePlayed;
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
					if (statTable[index].second.first == "Solo Kills")
						this->combat_.soloKills = statTable[index].second.second;
					if (statTable[index].second.first == "Final Blows")
						this->combat_.finalBlows = statTable[index].second.second;
					if (statTable[index].second.first == "Multikills")
						this->combat_.multiKills = statTable[index].second.second;
					if (statTable[index].second.first == "Final Blows - Most in Game")
						this->combat_.finalBlowsBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Multikill - Best")
						this->combat_.multiKillsBestGame = statTable[index].second.second;
					if (statTable[index].second.first == "Solo Kills - Most in Game")
						this->combat_.soloKillsBestGame = statTable[index].second.second;
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
					if (statTable[index].second.first == "Environmental Kills")
						this->combat_.environmentalKills = statTable[index].second.second;
					
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
					this->averages_.avgEnvironmentalKills = this->combat_.environmentalKills / (float)this->game_.gamesPlayed;
					this->averages_.avgMultiKills	  = this->combat_.multiKills / (float)this->game_.gamesPlayed;
					this->averages_.avgSoloKills	  = this->combat_.soloKills / (float)this->game_.gamesPlayed;
					this->averages_.avgFinalBlows	  = this->combat_.finalBlows / (float)this->game_.gamesPlayed;
					this->averages_.elimsPerLife	  = this->combat_.eliminations / (float)this->combat_.deaths;
					this->averages_.winPercent		  = this->game_.gamesLost / (float)this->game_.gamesWon;
					this->averages_.avgHeroDamage	  = this->combat_.heroDamageDone / (float)this->game_.gamesPlayed;
					this->averages_.avgBarrierDamage  = this->combat_.barrierDamageDone / (float)this->game_.gamesPlayed;
					this->averages_.avgDeaths		  = this->combat_.deaths / (float)this->game_.gamesPlayed;
					this->averages_.avgObjectiveTime  = this->combat_.objectiveTime / (float)this->game_.gamesPlayed;
					this->averages_.avgObjectiveKills = this->combat_.objectiveKills / (float)this->game_.gamesPlayed;
					this->averages_.avgEliminations	  = this->combat_.eliminations / (float)this->game_.gamesPlayed;
					this->averages_.avgTimeOnFire	  = this->combat_.timeOnFire / (float)this->game_.gamesPlayed;

					this->averages_.environmentalKillsPerTen = this->combat_.environmentalKills / (float)timePlayed;
					this->averages_.soloKillsPerTen		= this->combat_.soloKills / (float)timePlayed;
					this->averages_.multiKillsPerTen	= this->combat_.multiKills / (float)timePlayed;
					this->averages_.finalBlowsPerTen	= this->combat_.finalBlows / (float)timePlayed;
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

	class dvaStats : public heroStats {

	private:
		struct dvaSpecificStats {
			int selfDestructKills;
			int selfDestructKillsMostInGame;
			int mechsCalled;
			int mechsCalledMostInGame;
			int mechDeaths;
		};

		struct dvaAvgStats {
			float selfDestructKillsAvg;
			float selfDestructKillsPerTen;
			float mechsCalledAvg;
			float mechsCalledPerTen;
			float mechDeathsAvg;
			float mechDeathsPerTen;
		};

		/*the values the implementer can see*/
		struct dvaStatInterface {
			dvaSpecificStats specificStats;
			dvaAvgStats avgStats;
			baseStatI baseStats;
			dvaStatInterface(dvaStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		dvaSpecificStats thesedvaStats;
		dvaAvgStats thesedvaAvgStats;

	public:
		const std::string getName() { return "D.Va"; }
		dvaStats() { internalSetup(false, true, true); }
		const dvaSpecificStats getSpecific()  const { return this->thesedvaStats; }
		const dvaAvgStats	     getAvgStats()  const { return this->thesedvaAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const dvaStatInterface* statInterface = new dvaStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Self-Destruct Kills")
						this->thesedvaStats.selfDestructKills = statTable[index].second.second;
					if (statTable[index].second.first == "Self-Destruct Kills - Most in Game")
						this->thesedvaStats.selfDestructKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Mechs Called")
						this->thesedvaStats.mechsCalled = statTable[index].second.second;
					if (statTable[index].second.first == "Mechs Called - Most in Game")
						this->thesedvaStats.mechsCalledMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Mech Deaths")
						this->thesedvaStats.mechDeaths = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesedvaAvgStats.mechDeathsPerTen = this->thesedvaStats.mechDeaths / (float)timePlayed;
			this->thesedvaAvgStats.selfDestructKillsPerTen = this->thesedvaStats.selfDestructKills / (float)timePlayed;
			this->thesedvaAvgStats.mechsCalledPerTen = this->thesedvaStats.mechsCalled / (float)timePlayed;

			this->thesedvaAvgStats.mechDeathsAvg = this->thesedvaStats.mechDeaths / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesedvaAvgStats.selfDestructKillsAvg = this->thesedvaStats.selfDestructKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesedvaAvgStats.mechsCalledAvg = this->thesedvaStats.mechsCalled / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new dvaStatInterface(*this);
		}
	};

	class orisaStats : public heroStats {

	private:
		struct orisaSpecificStats {
			int damageAmplified;
			int damageAmplifiedMostInGame;
			int superchargerAssists;
			int superchargerAssistsMostInGame;
		};

		struct orisaAvgStats {
			float damageAmplifiedAvg;
			float damageAmplifiedPerTen;
			float superchargerAssistsAvg;
			float superchargerAsssistsPerTen;
		};

		/*the values the implementer can see*/
		struct orisaStatInterface {
			orisaSpecificStats specificStats;
			orisaAvgStats avgStats;
			baseStatI baseStats;
			orisaStatInterface(orisaStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		orisaSpecificStats theseorisaStats;
		orisaAvgStats theseorisaAvgStats;

	public:
		const std::string getName() { return "Orisa"; }
		orisaStats() { internalSetup(false, true, true); }
		const orisaSpecificStats getSpecific()  const { return this->theseorisaStats; }
		const orisaAvgStats	     getAvgStats()  const { return this->theseorisaAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const orisaStatInterface* statInterface = new orisaStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Damage Amplified")
						this->theseorisaStats.damageAmplified = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Amplified - Most in Game")
						this->theseorisaStats.damageAmplifiedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Supercharger Assists")
						this->theseorisaStats.superchargerAssists = statTable[index].second.second;
					if (statTable[index].second.first == "Supercharger Assists - Most in Game")
						this->theseorisaStats.superchargerAssistsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->theseorisaAvgStats.superchargerAsssistsPerTen = this->theseorisaStats.superchargerAssists / (float)timePlayed;
			this->theseorisaAvgStats.damageAmplifiedPerTen = this->theseorisaStats.damageAmplified / (float)timePlayed;

			this->theseorisaAvgStats.superchargerAssistsAvg = this->theseorisaStats.superchargerAssists / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseorisaAvgStats.damageAmplifiedAvg = this->theseorisaStats.damageAmplified / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new orisaStatInterface(*this);
		}
	};

	class reinhardtStats : public heroStats {

	private:
		struct reinhardtSpecificStats {
			int chargeKills;
			int chargeKillsMostInGame;
			int fireStrikeKills;
			int fireStrikeKillsMostInGame;
			int earthStrikeKills;
			int earthStrikeKIllsMostInGame;
		};

		struct reinhardtAvgStats {
			float chargeKillsAvg;
			float chargeKillsPerTen;
			float fireStrikeKillsAvg;
			float fireStrikeKillsPerTen;
			float earthStrikeKillsAvg;
			float earthStrikeKillsPerTen;
		};

		/*the values the implementer can see*/
		struct reinhardtStatInterface {
			reinhardtSpecificStats specificStats;
			reinhardtAvgStats avgStats;
			baseStatI baseStats;
			reinhardtStatInterface(reinhardtStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		reinhardtSpecificStats thesereinhardtStats;
		reinhardtAvgStats thesereinhardtAvgStats;

	public:
		const std::string getName() { return "Reinhardt"; }
		reinhardtStats() { internalSetup(false, false, true); }
		const reinhardtSpecificStats getSpecific()  const { return this->thesereinhardtStats; }
		const reinhardtAvgStats	     getAvgStats()  const { return this->thesereinhardtAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const reinhardtStatInterface* statInterface = new reinhardtStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Charge Kills")
						this->thesereinhardtStats.chargeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Charge Kills - Most in Game")
						this->thesereinhardtStats.chargeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Fire Strike Kills")
						this->thesereinhardtStats.fireStrikeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Fire Strike Kills - Most in Game")
						this->thesereinhardtStats.fireStrikeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Earthshatter Kills")
						this->thesereinhardtStats.earthStrikeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Earthshatter Kills - Most in Game")
						this->thesereinhardtStats.earthStrikeKIllsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesereinhardtAvgStats.chargeKillsPerTen = this->thesereinhardtStats.chargeKills / (float)timePlayed;
			this->thesereinhardtAvgStats.earthStrikeKillsPerTen = this->thesereinhardtStats.earthStrikeKills / (float)timePlayed;
			this->thesereinhardtAvgStats.fireStrikeKillsPerTen = this->thesereinhardtStats.fireStrikeKills / (float)timePlayed;

			this->thesereinhardtAvgStats.chargeKillsAvg = this->thesereinhardtStats.chargeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesereinhardtAvgStats.earthStrikeKillsAvg = this->thesereinhardtStats.earthStrikeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesereinhardtAvgStats.fireStrikeKillsAvg = this->thesereinhardtStats.fireStrikeKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new reinhardtStatInterface(*this);
		}
	};

	class roadhogStats : public heroStats {

	private:
		struct roadhogSpecificStats {
			int enemiesHooked;
			int enemiesHookedMostInGame;
			int hooksAttempted;
			int wholeHogKills;
			int wholeHogKillsMostInGame;
			int hookAccBestInGame;
			int selfHealing;
			int selfHealingMostInGame;
			int hookAcc;
		};

		struct roadhogAvgStats {
			float enemiesHookedAvg;
			float enemiesHookedPerTen;
			float hooksAttemptedAvg;
			float hooksAttemptedPerTen;
			float wholeHogKillsAvg;
			float wholeHogKillsPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
		};

		/*the values the implementer can see*/
		struct roadhogStatInterface {
			roadhogSpecificStats specificStats;
			roadhogAvgStats avgStats;
			baseStatI baseStats;
			roadhogStatInterface(roadhogStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		roadhogSpecificStats theseroadhogStats;
		roadhogAvgStats theseroadhogAvgStats;

	public:
		const std::string getName() { return "Roadhog"; }
		roadhogStats() { internalSetup(false, true, true); }
		const roadhogSpecificStats getSpecific()  const { return this->theseroadhogStats; }
		const roadhogAvgStats	     getAvgStats()  const { return this->theseroadhogAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const roadhogStatInterface* statInterface = new roadhogStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Enemies Hooked - Most in Game")
						this->theseroadhogStats.enemiesHookedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies Hooked")
						this->theseroadhogStats.enemiesHooked = statTable[index].second.second;
					if (statTable[index].second.first == "Hooks Attempted")
						this->theseroadhogStats.hooksAttempted = statTable[index].second.second;
					if (statTable[index].second.first == "Whole Hog Kills - Most in Game")
						this->theseroadhogStats.wholeHogKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Whole Hog Kills")
						this->theseroadhogStats.wholeHogKills = statTable[index].second.second;
					if (statTable[index].second.first == "Hook Accuracy - Best in Game")
						this->theseroadhogStats.hookAccBestInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->theseroadhogStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->theseroadhogStats.selfHealingMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Hook Accuracy")
						this->theseroadhogStats.hookAcc = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->theseroadhogAvgStats.enemiesHookedPerTen = this->theseroadhogStats.enemiesHooked / (float)timePlayed;
			this->theseroadhogAvgStats.hooksAttemptedPerTen = this->theseroadhogStats.hooksAttempted / (float)timePlayed;
			this->theseroadhogAvgStats.selfHealingPerTen = this->theseroadhogStats.selfHealing / (float)timePlayed;
			this->theseroadhogAvgStats.wholeHogKillsPerTen = this->theseroadhogStats.wholeHogKills / (float)timePlayed;

			this->theseroadhogAvgStats.enemiesHookedAvg = this->theseroadhogStats.enemiesHooked / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseroadhogAvgStats.hooksAttemptedAvg = this->theseroadhogStats.hooksAttempted / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseroadhogAvgStats.selfHealingAvg = this->theseroadhogStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseroadhogAvgStats.wholeHogKillsAvg = this->theseroadhogStats.wholeHogKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new roadhogStatInterface(*this);
		}
	};

	class winstonStats : public heroStats {

	private:
		struct winstonSpecificStats {
			int playersKnockedBack;
			int playersKnockedBackMostInGame;
			int meleeKills;
			int meleeKillsMostInGame;
			int jumpPackKills;
			int jumpPackKillsMostInGame;
			int primalRageKills;
			int primalRageKillsMostInGame;
		};

		struct winstonAvgStats {
			float playersKnockedBackAvg;
			float playersKnockedBackPerTen;
			float meleeKillsAvg;
			float meleeKillsPerTen;
			float jumpPackKillsAvg;
			float jumpPackKillsPerTen;
			float primalRageKillsAvg;
			float primalRageKillsPerTen;
		};

		/*the values the implementer can see*/
		struct winstonStatInterface {
			winstonSpecificStats specificStats;
			winstonAvgStats avgStats;
			baseStatI baseStats;
			winstonStatInterface(winstonStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		winstonSpecificStats thesewinstonStats;
		winstonAvgStats thesewinstonAvgStats;

	public:
		const std::string getName() { return "Winston"; }
		winstonStats() { internalSetup(false, false, true); }
		const winstonSpecificStats getSpecific()  const { return this->thesewinstonStats; }
		const winstonAvgStats	     getAvgStats()  const { return this->thesewinstonAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const winstonStatInterface* statInterface = new winstonStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Players Knocked Back")
						this->thesewinstonStats.playersKnockedBack = statTable[index].second.second;
					if (statTable[index].second.first == "Players Knocked Back - Most in Game")
						this->thesewinstonStats.playersKnockedBackMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Melee Kills")
						this->thesewinstonStats.meleeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Melee Kills - Most in Game")
						this->thesewinstonStats.meleeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Jump Pack Kills")
						this->thesewinstonStats.jumpPackKills = statTable[index].second.second;
					if (statTable[index].second.first == "Jump Pack Kills - Most in Game")
						this->thesewinstonStats.jumpPackKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Primal Rage Kills")
						this->thesewinstonStats.primalRageKills = statTable[index].second.second;
					if (statTable[index].second.first == "Primal Rage Kills - Most in Game")
						this->thesewinstonStats.primalRageKillsMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesewinstonAvgStats.jumpPackKillsPerTen = this->thesewinstonStats.jumpPackKills / (float)timePlayed;
			this->thesewinstonAvgStats.meleeKillsPerTen = this->thesewinstonStats.meleeKills / (float)timePlayed;
			this->thesewinstonAvgStats.playersKnockedBackPerTen = this->thesewinstonStats.playersKnockedBack / (float)timePlayed;
			this->thesewinstonAvgStats.primalRageKillsPerTen = this->thesewinstonStats.primalRageKills / (float)timePlayed;

			this->thesewinstonAvgStats.jumpPackKillsAvg = this->thesewinstonStats.jumpPackKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesewinstonAvgStats.meleeKillsAvg = this->thesewinstonStats.meleeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesewinstonAvgStats.playersKnockedBackAvg = this->thesewinstonStats.playersKnockedBack / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesewinstonAvgStats.primalRageKillsAvg = this->thesewinstonStats.primalRageKills / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new winstonStatInterface(*this);
		}
	};

	class zaryaStats : public heroStats {

	private:
		struct zaryaSpecificStats {
			int gravitonSurgeKills;
			int gravitonSurgeKillsMostInGame;
			int highEnergyKills;
			int highEnergyKillsMostInGame;
			int projectedBarriersApplied;
			int projectedBarriersAppliedMostInGame;
			float avgEnergy;
		};

		struct zaryaAvgStats {
			float gravitonKillsAvg;
			float gravitonKillsPerTen;
			float highEnergyKillsAvg;
			float highEnergyKillsPerTen;
			float projectedBarriersAppliedAvg;
			float projectedBarriersAppliedPerTen;
		};

		/*the values the implementer can see*/
		struct zaryaStatInterface {
			zaryaSpecificStats specificStats;
			zaryaAvgStats avgStats;
			baseStatI baseStats;
			zaryaStatInterface(zaryaStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		zaryaSpecificStats thesezaryaStats;
		zaryaAvgStats thesezaryaAvgStats;

	public:
		const std::string getName() { return "Zarya"; }
		zaryaStats() { internalSetup(false, false, true); }
		const zaryaSpecificStats getSpecific()  const { return this->thesezaryaStats; }
		const zaryaAvgStats	     getAvgStats()  const { return this->thesezaryaAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const zaryaStatInterface* statInterface = new zaryaStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Graviton Surge Kills")
						this->thesezaryaStats.gravitonSurgeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Graviton Surge Kills - Most in Game")
						this->thesezaryaStats.gravitonSurgeKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "High Energy Kills - Most in Game")
						this->thesezaryaStats.highEnergyKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "High Energy Kills")
						this->thesezaryaStats.highEnergyKills = statTable[index].second.second;
					if (statTable[index].second.first == "Projected Barriers Applied")
						this->thesezaryaStats.projectedBarriersApplied = statTable[index].second.second;
					if (statTable[index].second.first == "Projected Barriers Applied - Most in Game")
						this->thesezaryaStats.projectedBarriersAppliedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Average Energy")
						this->thesezaryaStats.avgEnergy = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesezaryaAvgStats.gravitonKillsPerTen = this->thesezaryaStats.gravitonSurgeKills / (float)timePlayed;
			this->thesezaryaAvgStats.highEnergyKillsPerTen = this->thesezaryaStats.highEnergyKills / (float)timePlayed;
			this->thesezaryaAvgStats.projectedBarriersAppliedPerTen = this->thesezaryaStats.projectedBarriersApplied / (float)timePlayed;

			this->thesezaryaAvgStats.gravitonKillsAvg = this->thesezaryaStats.gravitonSurgeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesezaryaAvgStats.highEnergyKillsAvg = this->thesezaryaStats.highEnergyKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesezaryaAvgStats.projectedBarriersAppliedAvg = this->thesezaryaStats.projectedBarriersApplied / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new zaryaStatInterface(*this); 
		}
	};

	class anaStats : public heroStats {

	private:
		struct anaSpecificStats {
			int scopedAccBestInGame;
			int selfHealing;
			int selfHealingMostInGame;
			int enemiesSlept;
			int nanoBoostsApplied;
			int nanoBoostAssists;
			int enemiesSleptMostInGame;
			int nanoBoostAssistsMostInGame;
			int nanoBoostsAppliedMostInGame;
			int bioticGrenadeKills;
			int scopedAcc;
		};

		struct anaAvgStats {
			float selfHealingAvg;
			float selfHealingPerTen;
			float enemiesSleptAvg;
			float enemiesSleptPerTen;
			float nanoBoostsAppliedAvg;
			float nanoBoostsAppliedPerTen;
			float nanoBoostAssistsAvg;
			float nanoBoostAssistsPerTen;
			float bioticGrenadeKillsAvg;
			float bioticGrenadeKillsPerTen;
		};

		/*the values the implementer can see*/
		struct anaStatInterface {
			anaSpecificStats specificStats;
			anaAvgStats avgStats;
			baseStatI baseStats;
			anaStatInterface(anaStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		anaSpecificStats theseanaStats;
		anaAvgStats theseanaAvgStats;

	public:
		const std::string getName() { return "Ana"; }
		anaStats() { internalSetup(true, false, false); }
		const anaSpecificStats getSpecific()  const { return this->theseanaStats; }
		const anaAvgStats	     getAvgStats()  const { return this->theseanaAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const anaStatInterface* statInterface = new anaStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Scoped Accuracy - Best in Game")
						this->theseanaStats.scopedAccBestInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->theseanaStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->theseanaStats.selfHealingMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies Slept")
						this->theseanaStats.enemiesSlept = statTable[index].second.second;
					if (statTable[index].second.first == "Nano Boosts Applied")
						this->theseanaStats.nanoBoostsApplied = statTable[index].second.second;
					if (statTable[index].second.first == "Nano Boost Assists")
						this->theseanaStats.nanoBoostAssists = statTable[index].second.second;
					if (statTable[index].second.first == "Enemies Slept - Most in Game")
						this->theseanaStats.enemiesSleptMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Nano Boost Assists - Most in Game")
						this->theseanaStats.nanoBoostAssistsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Nano {count, plural, one {Boost} other {Boosts}} Applied - Most in Game")
						this->theseanaStats.nanoBoostsAppliedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Biotic Grenade Kills")
						this->theseanaStats.bioticGrenadeKills = statTable[index].second.second;
					if (statTable[index].second.first == "Scoped Accuracy")
						this->theseanaStats.scopedAcc = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->theseanaAvgStats.selfHealingPerTen = this->theseanaStats.selfHealing / (float)timePlayed;
			this->theseanaAvgStats.bioticGrenadeKillsPerTen = this->theseanaStats.bioticGrenadeKills / (float)timePlayed;
			this->theseanaAvgStats.enemiesSleptPerTen = this->theseanaStats.enemiesSlept / (float)timePlayed;
			this->theseanaAvgStats.nanoBoostAssistsPerTen = this->theseanaStats.nanoBoostAssists / (float)timePlayed;
			this->theseanaAvgStats.nanoBoostsAppliedPerTen = this->theseanaStats.nanoBoostsApplied / (float)timePlayed;

			this->theseanaAvgStats.selfHealingAvg = this->theseanaStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseanaAvgStats.bioticGrenadeKillsAvg = this->theseanaStats.bioticGrenadeKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseanaAvgStats.enemiesSleptAvg = this->theseanaStats.enemiesSlept / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseanaAvgStats.nanoBoostAssistsAvg = this->theseanaStats.nanoBoostAssists / (float)this->baseStatInterface->game.gamesPlayed;
			this->theseanaAvgStats.nanoBoostsAppliedAvg = this->theseanaStats.nanoBoostsApplied / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new anaStatInterface(*this);
		}
	};

	class lucioStats : public heroStats {

	private:
		struct lucioSpecificStats {
			int soundBarriersProvided;
			int soundBarriersProvidedMostInGame;
			int selfHealing;
			int selfHealingMostInGame;
		};

		struct lucioAvgStats {
			float soundBarriersProvidedAvg;
			float soundBarriersProvidedPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
		};

		/*the values the implementer can see*/
		struct lucioStatInterface {
			lucioSpecificStats specificStats;
			lucioAvgStats avgStats;
			baseStatI baseStats;
			lucioStatInterface(lucioStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		lucioSpecificStats theselucioStats;
		lucioAvgStats theselucioAvgStats;

	public:
		const std::string getName() { return "Lúcio"; }
		lucioStats() { internalSetup(true, true, false); }
		const lucioSpecificStats getSpecific()  const { return this->theselucioStats; }
		const lucioAvgStats	     getAvgStats()  const { return this->theselucioAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const lucioStatInterface* statInterface = new lucioStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Sound Barriers Provided")
						this->theselucioStats.soundBarriersProvided = statTable[index].second.second;
					if (statTable[index].second.first == "Sound Barriers Provided - Most in Game")
						this->theselucioStats.soundBarriersProvidedMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->theselucioStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->theselucioStats.selfHealingMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->theselucioAvgStats.selfHealingPerTen = this->theselucioStats.selfHealing / (float)timePlayed;
			this->theselucioAvgStats.soundBarriersProvidedPerTen = this->theselucioStats.soundBarriersProvided / (float)timePlayed;

			this->theselucioAvgStats.selfHealingAvg = this->theselucioStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->theselucioAvgStats.soundBarriersProvidedAvg = this->theselucioStats.soundBarriersProvided / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new lucioStatInterface(*this);
		}
	};

	class mercyStats : public heroStats {

	private:
		struct mercySpecificStats {
			int blasterKills;
			int blasterKillsMostInGame;
			int resurrects;
			int resurrectsMostInGame;
			int selfHealing;
			int selfHealingMostInGame;
			int damageAmped;
			int damageAmpedMostInGame;

		};

		struct mercyAvgStats {
			float blasterKillsAvg;
			float blasterKillsPerTen;
			float resurrectsAvg;
			float resurrectsPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
			float damageAmpedAvg;
			float damageAmpedPerTen;
		};

		/*the values the implementer can see*/
		struct mercyStatInterface {
			mercySpecificStats specificStats;
			mercyAvgStats avgStats;
			baseStatI baseStats;
			mercyStatInterface(mercyStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		mercySpecificStats thesemercyStats;
		mercyAvgStats thesemercyAvgStats;

	public:
		const std::string getName() { return "Mercy"; }
		mercyStats() { internalSetup(true, true, false); }
		const mercySpecificStats getSpecific()  const { return this->thesemercyStats; }
		const mercyAvgStats	     getAvgStats()  const { return this->thesemercyAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const mercyStatInterface* statInterface = new mercyStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Blaster Kills")
						this->thesemercyStats.blasterKills = statTable[index].second.second;
					if (statTable[index].second.first == "Blaster Kills - Most in Game")
						this->thesemercyStats.blasterKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Players Resurrected")
						this->thesemercyStats.resurrects = statTable[index].second.second;
					if (statTable[index].second.first == "Players Resurrected - Most in Game")
						this->thesemercyStats.resurrectsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->thesemercyStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->thesemercyStats.selfHealingMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Amplified")
						this->thesemercyStats.damageAmped = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Amplified - Most in Game")
						this->thesemercyStats.damageAmpedMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesemercyAvgStats.selfHealingPerTen = this->thesemercyStats.selfHealing / (float)timePlayed;
			this->thesemercyAvgStats.blasterKillsPerTen = this->thesemercyStats.blasterKills / (float)timePlayed;
			this->thesemercyAvgStats.resurrectsPerTen = this->thesemercyStats.resurrects / (float)timePlayed;
			this->thesemercyAvgStats.damageAmpedPerTen = this->thesemercyStats.damageAmped / (float)timePlayed;

			this->thesemercyAvgStats.selfHealingAvg = this->thesemercyStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemercyAvgStats.blasterKillsAvg = this->thesemercyStats.blasterKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemercyAvgStats.damageAmpedAvg = this->thesemercyStats.damageAmped / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemercyAvgStats.resurrectsAvg = this->thesemercyStats.resurrects / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new mercyStatInterface(*this);
		}
	};

	class moiraStats : public heroStats {

	private:
		struct moiraSpecificStats {
			int blasterKills;
			int blasterKillsMostInGame;
			int resurrects;
			int resurrectsMostInGame;
			int selfHealing;
			int selfHealingMostInGame;
			int damageAmped;
			int damageAmpedMostInGame;

		};

		struct moiraAvgStats {
			float blasterKillsAvg;
			float blasterKillsPerTen;
			float resurrectsAvg;
			float resurrectsPerTen;
			float selfHealingAvg;
			float selfHealingPerTen;
			float damageAmpedAvg;
			float damageAmpedPerTen;
		};

		/*the values the implementer can see*/
		struct moiraStatInterface {
			moiraSpecificStats specificStats;
			moiraAvgStats avgStats;
			baseStatI baseStats;
			moiraStatInterface(moiraStats those) {
				this->specificStats = those.getSpecific();
				baseStats = baseStats.updateI(those.baseStatInterface);
				this->avgStats = those.getAvgStats();
			}
		};

		/*the values that can be changed*/
		moiraSpecificStats thesemoiraStats;
		moiraAvgStats thesemoiraAvgStats;

	public:
		const std::string getName() { return "Moira"; }
		moiraStats() { internalSetup(true, true, false); }
		const moiraSpecificStats getSpecific()  const { return this->thesemoiraStats; }
		const moiraAvgStats	     getAvgStats()  const { return this->thesemoiraAvgStats; }
		const baseStatI*		 getBaseStats() const { return this->baseStatInterface; }

		/*implementer of the function gets access to a const'd version of the stats*/
		const moiraStatInterface* statInterface = new moiraStatInterface(*this);

		void updateStats() override {

			this->updateBaseStats(this->getName());

			//update specific stats
			for (int index = 0; index < statTable.size(); ++index) {
				if (statTable[index].first.first == this->getName()) {
					if (statTable[index].second.first == "Blaster Kills")
						this->thesemoiraStats.blasterKills = statTable[index].second.second;
					if (statTable[index].second.first == "Blaster Kills - Most in Game")
						this->thesemoiraStats.blasterKillsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Players Resurrected")
						this->thesemoiraStats.resurrects = statTable[index].second.second;
					if (statTable[index].second.first == "Players Resurrected - Most in Game")
						this->thesemoiraStats.resurrectsMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing")
						this->thesemoiraStats.selfHealing = statTable[index].second.second;
					if (statTable[index].second.first == "Self Healing - Most in Game")
						this->thesemoiraStats.selfHealingMostInGame = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Amplified")
						this->thesemoiraStats.damageAmped = statTable[index].second.second;
					if (statTable[index].second.first == "Damage Amplified - Most in Game")
						this->thesemoiraStats.damageAmpedMostInGame = statTable[index].second.second;
				}
			}

			//cast to minutes
			float timePlayed = this->baseStatInterface->game.timePlayed * 60;
			//no need to process
			if (timePlayed == 0.0) return;
			//cast to ten minute intervals
			timePlayed /= 10;

			this->thesemoiraAvgStats.selfHealingPerTen = this->thesemoiraStats.selfHealing / (float)timePlayed;
			this->thesemoiraAvgStats.blasterKillsPerTen = this->thesemoiraStats.blasterKills / (float)timePlayed;
			this->thesemoiraAvgStats.resurrectsPerTen = this->thesemoiraStats.resurrects / (float)timePlayed;
			this->thesemoiraAvgStats.damageAmpedPerTen = this->thesemoiraStats.damageAmped / (float)timePlayed;

			this->thesemoiraAvgStats.selfHealingAvg = this->thesemoiraStats.selfHealing / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemoiraAvgStats.blasterKillsAvg = this->thesemoiraStats.blasterKills / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemoiraAvgStats.damageAmpedAvg = this->thesemoiraStats.damageAmped / (float)this->baseStatInterface->game.gamesPlayed;
			this->thesemoiraAvgStats.resurrectsAvg = this->thesemoiraStats.resurrects / (float)this->baseStatInterface->game.gamesPlayed;

			this->statInterface = new moiraStatInterface(*this);
		}
	};