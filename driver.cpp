/*
Author: Tyler Small 2/28/18

This class scrapes hero stats from the playoverwatch website and puts them into player profiles.

Because of the potential negatives scraping poses on a website, this code is not licensed under M.I.T.
And therefore not open to the general public.
Database is kept at <INSERT URL>

* Copyright (C) Tyler Small - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

///TODO FIX TIME PLAYED READIN
///A FLOAT IS USED IF THE TIME IS IN SECONDS. POTENTIAL FOR ERROR

#include <string>
#include <iostream>
#include "curl\curl.h"
#include <fstream>
#include <algorithm>
//#include <vector> Included with heroStats.h
#include "heroStats.h"

#define NUM_CATEGORIES 12
#define NUM_HEROES 26
#define BUFFER_SIZE 256
static const std::string BASE_URL = "https://playoverwatch.com/en-us/career/";
static const std::string PLATFORM_PC = "pc/";
//I guess we'll allow plebs on the platform...
static const std::string PLATFORM_XBL = "xbl/";
static const std::string PLATFORM_PSN = "psn/";
static std::string BATTLETAG = "Cee-11450";		///TEMP ASSIGNMENT

/*					-------PROJECT SETUP INSTRUCTIONS--------
  <projectName> Properties -> C/C++ -> PreProcessor -> add CURL_STATICLIB 
   With the preprocessor directive, all you need is the define statement and pragma to manually
   set up your project.

   WARNINGS:
   CURL_LIB_LOCATION changes with operating system / compiler you built on ...
   adjust to fit your build name

   Curl folder should be in your project folder with the source files
   in Curl Folder:
   include files provided by curl -> to use my header provided, don't have them in a nested folder, 
									 else just include "<folderName>\curl\curl.h"

	and your build folder : libcurl-vc14-x86-release-static-ipv6-sspi-winssl/lib/libcurl_a or something similiar
							-> should contain a lib folder, include folder, and bin
							-> curl does this for you
	CONTACT:
	Github.com/vxlk if you can't get your project set up

*/
#define CURL_LIB_LOCATION "curl/libcurl-vc14-x86-release-static-ipv6-sspi-winssl/lib/libcurl_a"
#pragma comment(lib, CURL_LIB_LOCATION)

//typedef std::pair<std::string, std::string> HeroHexID;
//typedef std::pair<std::string, int>			StatTable;

//may not contain every hero if not every hero is played during a comp season for at least 1 second
//only can scrape heroes played
//DoubleString* heroId = new DoubleString[NUM_HEROES + 1]; //+1 for the all_heroes category
//std::vector<std::pair<DoubleString, StatTable> > statTable;


//cURL buffer setup
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void fixPlatform(std::string& platform) {
	//fix characters and spacing and caps
	//also check for valid input
}

void fixBtag(std::string& btag) {
	//fix spacing
	//turn # into - for url
}

//returns the url of the player
const std::string makeURL(std::string& platform, std::string& btag) {
	fixPlatform(platform);
	fixBtag(btag);
	return BASE_URL + platform + btag;
}

///FIRST SCRAPE-----
/*
The blizzard website uses hero ids that are hex values, these change on orientation sometimes randomly it seems
so i just repopulate them every call to -get player stats-
get -> 0x02E00000FFFFFFFF this hex # represents the "ALL HEROES" selection on the drop down list from the site
cycle through getting hero name and assigned hex representation
stop -> 0x02E00000FFFFFFFF once you have seen this again, you are out of the name->hex category of the site data
*/

/*modifies the string!*/
void shortenBuffer(std::string& buffer) {
	if (buffer.find("value=\"0x02E00000FFFFFFFF\"") != buffer.npos)
		buffer.substr(buffer.find("value=\"0x02E00000FFFFFFFF\""));
}


void addStatsToHeroContainer(heroStats* hero) {
	
	std::string currentHero = hero->getName();
}

heroStats* castToHeroContainer(std::string name) {

	/*
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
	*/
	if (name == "Torbjorn")
		name = "TorbjÃ¶rn"; //make my life easier
	//buildHeroMap();
	int heroNameIndex;
	//if (name == heroList[1])
		//return (new doomFistStats);
	for (int i = 0; i < NUM_HEROES; ++i)
		if (name == heroList[i]) {
			heroNameIndex = i;
			break;
		}
	///NEED a fail safe here
	switch (heroNameIndex) {
	case 0:
		return new doomfistStats;
	case 1:
		return new genjiStats;
		break;
	case 2:
		return new mccreeStats;
		break;
	case 3:
		return new pharahStats;
		break;
	case 4:
		return new reaperStats;
		break;


	case 11:
		return new torbjornStats;
		break;
	case 12:
		return new widowStats;
		break;

	}
	
}

void populateHeroId(const std::string& buffer) {
	/*
	There is a dropdown menu you can see on the website -> this hex value represents All heroes
	So i use this to find the beginning of the list of choices, it also conveniently marks the end
	*/
	
	int loopIndex = buffer.find("value=\"0x02E00000FFFFFFFF\"");
	int end = buffer.find("data-category-id=\"0x02E00000FFFFFFFF\"");
	if (end == buffer.npos || loopIndex == buffer.npos) { std::cerr << "Invalid Reading From Hero ID"; return; }
	
	///GOAL---------------
	//read until the hex representation for all heroes scraped from the site
	//get the hex representation and the hero name it corresponds to
	//purge " " and extra characters

	int stringIndex = 0;
	int heroNameIndex = 0;
	int heroCountIndex = 0;
	std::string tempString(BUFFER_SIZE, '\0'); //holder
	std::string heroName(BUFFER_SIZE, '\0');
	std::string heroHexName(BUFFER_SIZE, '\0');
	
	while (loopIndex <= end) {
		
		tempString[stringIndex] = buffer[loopIndex];

		///SCRAPE HERO HEX VALUE
		/*
		Some complications here, the name check has an easy delimiter, a > appears after every name.
		the hex name is more complicated, it has no consistent delimiter, so i am reading past the first
		" ... then only reading until i encounter the next ". risky, and i hate it, but I don't see another
		clean way to do it right now.
		*/
		if (tempString.find("value=") != tempString.npos) {
			loopIndex += 2; //read past first "
			//read hero hex name
			while (heroHexName.find("\"") == heroHexName.npos) {
				heroHexName[heroNameIndex] = buffer[loopIndex];
				++heroNameIndex;
				++loopIndex;
			}

			//erase extra chars out of the name ... c++ is not the most elegant at this
			heroHexName.erase(std::remove(heroHexName.begin(), heroHexName.end(), '\"'), heroHexName.end());
			heroHexName.erase(std::remove(heroHexName.begin(), heroHexName.end(), '\0'), heroHexName.end());

			//put into the id structure
			heroId[heroCountIndex].second = heroHexName;

			//clean up for next round
			stringIndex = 0;
			heroNameIndex = 0;
			heroHexName.assign(BUFFER_SIZE, '\0'); //"empty" the string;
			tempString.assign(BUFFER_SIZE, '\0');
			continue; //skip the post increment
		}

		///SCRAPE HERO NAME
		if (tempString.find("option-id=") != tempString.npos) {
			//read heroName
			while (heroName.find(">") == heroName.npos) {
				heroName[heroNameIndex] = buffer[loopIndex];
				++heroNameIndex;
				++loopIndex;
			}

			//erase extra chars out of the name ... c++ is not the most elegant at this
			heroName.erase(std::remove(heroName.begin(), heroName.end(), '\"'), heroName.end());
			heroName.erase(std::remove(heroName.begin(), heroName.end(), '='), heroName.end());
			heroName.erase(std::remove(heroName.begin(), heroName.end(), '>'), heroName.end());
			heroName.erase(std::remove(heroName.begin(), heroName.end(), '\0'), heroName.end());
			

			//put into the id structure
			heroId[heroCountIndex].first = heroName;
			++heroCountIndex; //goto next hero

			//reset for next iterations...
			stringIndex = 0;
			heroNameIndex = 0;
			heroName.assign(BUFFER_SIZE, '\0'); //"empty" the string;
			tempString.assign(BUFFER_SIZE, '\0');
			continue; //skip the post increment
		}
		
		++stringIndex;
		++loopIndex;
	}
}

///SECOND SCRAPE----
void getHeroStats(const std::string& buffer) {

	const std::string statCategories[NUM_CATEGORIES] =
	{
		"Average", "Assists", "Best", "Combat", "Game", "Hero Specific", "Match Awards"
	};
	//data-category-id=""
	//int start = buffer.find("value=\"0x02E00000FFFFFFFF\"");
	int start = 0;
	//start @ 1 to skip ALL HEROES
	for (int index = 1; index < NUM_HEROES + 1; ++index) {
		//signals the end of the list -some players don't have play time on every hero, so will not have a stat record for every hero-
		if (heroId[index].first == "") break;

		int startParse = buffer.find(("data-category-id=\"" + heroId[index].second + "\""));
		int endParse = buffer.find("data-group-id=\"stats\"", startParse + 1);
		int test = buffer.size();
		if (startParse == buffer.npos) {
			std::cerr << "Hero Hex ID loaded incorrectly\n";
			break;
		}

		if (endParse == buffer.npos) {
			break; //you are done
		}

		start = startParse;
		//if find class="stat-title"> -> read until < and get name Average
		std::string currentCategory;
		std::string category;
		std::string statName;
		std::string statNum;
		std::string subString;
		int loopIndex = startParse;
		int subStringIndex = 0;
		int categoryType = -1;

		while (loopIndex <= endParse) {
			///TODO GIVE POPULATE HERO ID THIS STRUCTURE OF STRING, USING FIXED BUFFER IS NOT SAFE
			subString += buffer[loopIndex];

			///FIND CATEGORIES
			if (subString.find("class=\"stat-title\"") != subString.npos) {
				while (buffer[loopIndex] != '/') {
					category += buffer[loopIndex];
					++loopIndex;
				}

				//clean the string
				category.erase(std::remove(category.begin(), category.end(), '<'), category.end());
				category.erase(std::remove(category.begin(), category.end(), '>'), category.end());
				category.erase(std::remove(category.begin(), category.end(), '\"'), category.end());
				//find a match
				for (int i = 0; i < NUM_CATEGORIES; i++)
					if (statCategories[i] == category) categoryType = i;

				if (categoryType == -1) std::cerr << "Found a category type that was not in dataBase.." << category << "\n";

				//			matchCategoryToHero(categoryType, heroId[index].first);
							//skip the post increment
				
				currentCategory = category;
				category.clear();
				subString.clear();
				continue;
			}
			++subStringIndex;
			++loopIndex;

			//get stats\
			if find data-category-id=\ in string switch heroes

			//go thru each hero sample and just find these
			//<td> name </td> <td> # </td>

			///pseudocode for stat vector generation
			/*
			if u find a <td> read until </tr> or </td>
			name then stat #

			if <td> ends in </tr>
			remove all data, reset looking field back to name

			if <td> ends in </td> get the name
			then read until the next </td> and get the #
			*/

			///FIND STATS
			if (subString.find("<td>") != subString.npos) {
				subString.clear();
				while (statName.find("</td>") == statName.npos) {
					if (statName.find("</tr>") != statName.npos) {
						//abort
						subString.clear();
						statName.clear();
						break;
					}
					statName += buffer[loopIndex];
					++loopIndex;
				}
				
				/*
				//clean the string
				statName.erase(std::remove(statName.begin(), statName.end(), '<'), statName.end());
				statName.erase(std::remove(statName.begin(), statName.end(), '>'), statName.end());
				statName.erase(std::remove(statName.begin(), statName.end(), '/"'), statName.end());
				*/

				//a name was found, now find the stat value
				if (statName != "") {
					while (subString.find("</td>") == subString.npos) {
						//skip commas in integer
						if (buffer[loopIndex] == ',' || buffer[loopIndex] == ':') {
							++loopIndex;
							continue;
						}
						subString += buffer[loopIndex];
						statNum += buffer[loopIndex];
						++loopIndex;
					}

					subString.clear();

					//this assumes no spaces
					statName.erase(statName.find("</td>"), statName.find("</td>") + 5);
					statNum.erase(statNum.find("</td>"), statNum.find("</td>") + 5);
					statNum.erase(statNum.find("<td>"), statNum.find("<td>") + 4);

					if (statNum.find('%') != statNum.npos)
						statName.erase(std::remove(statName.begin(), statName.end(), '%'), statName.end());


					///TESTING
					//if (heroId[index].first == "Widowmaker")
					//std::cout << statName << " " << statNum << "\n";
					
					//stat table ->                                    heroName,           stat category                     stat Name, stat Value
					if (statNum.find("minutes") != statNum.npos)
						statTable.push_back(std::make_pair(std::make_pair(heroId[index].first, currentCategory), std::make_pair(statName, (stof(statNum)/100))));
					else if (statNum.find("seconds") != statNum.npos)
						statTable.push_back(std::make_pair(std::make_pair(heroId[index].first, currentCategory), std::make_pair(statName, (stof(statNum) / 10000))));
					else
						statTable.push_back(std::make_pair(std::make_pair(heroId[index].first, currentCategory) , std::make_pair(statName, stof(statNum))));

					//clear for next run
					statName.clear();
					statNum.clear();
				}

			}
		}
	}
}

/*
Scrape the data, and read it into a string buffer
*/
void standardReadFromString() {

	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl) {
		//https://playoverwatch.com/en-us/career/pc/ZerG-11720
		curl_easy_setopt(curl, CURLOPT_URL, "https://playoverwatch.com/en-us/career/pc/Cee-11450");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);


		///LIST OF USEFUL COMMANDS
		/*

		competitive-rank    - comp rank image

		div id=\"competitive\"    -> get to comp

		*/

		///TESTING
		std::ofstream out;
		out.open("yeye.txt");

		
		///SHORTEN THE BUFFER TO ONLY COMP STATS
		int pos = readBuffer.find("div id=\"competitive\"");
		char* newBuffer = new char[readBuffer.size() - pos];
	
		int index = 0;
			if (pos != readBuffer.npos)
				for (int u = pos; u < readBuffer.size(); u++) {
					newBuffer[index] = readBuffer[u];
					++index;
				}
		
		//cURL uses c89, so when working with it we have to use char buffers
		//I am converting to a string for ease of use
		std::string str(newBuffer);
		
		//shortenBuffer(str);

		//get hex value representations - used to find hero specifics in buffer
		populateHeroId(str);
		getHeroStats(str);

		///TESTING
		std::replace(str.begin(), str.end(), 'Í', '/');
		out << str << std::endl;
		

	}
}

int main(void)
{
	standardReadFromString();
	
	std::ofstream out;
	out.open("yeya.txt");

	//heroStats* test = new heroStats;
	heroStats* test;
	test = castToHeroContainer("Torbjorn");
	//*test = dynamic_cast<widowStats*>(test);
	
	//statsToHeroContainer();

	/*
	for (int i = 0; i < NUM_HEROES + 1; ++i) {
		out << heroId[i].first << " " << heroId[i].second << "\n";
	}
	*/

	for (int i = 0; i < statTable.size(); ++i) {
		if (statTable[i].first.first == "TorbjÃ¶rn")
		out << statTable[i].first.first << " " << statTable[i].first.second << " " << statTable[i].second.first << " " << statTable[i].second.second << "\n";
	}
	std::cout << test->getName() << "\n";
	test->updateStats();

	//widowStats* newTest = test;

	std::cout << dynamic_cast<torbjornStats*>(test)->statInterface->specificStats.torbKills;
	


	/*
		//debug
		for (int i = 0; i < NUM_HEROES + 1; i++) {
			std::cout << "data-category-id=\"" + heroId[i].second + "\"" << "\n";
			std::cout << heroId[i].first << " " << heroId[i].second << "\n";
		}
		*/
	//int x;
	//std::cin >> x;

	return 0;
}

///EXAMPLE OF WHAT THE SOURCE BUFFER LOOKS LIKE...
/*
value="0x02E00000FFFFFFFF"
option-id="ALL HEROES">ALL HEROES</option><option value="0x02E0000000000003" 
option-id="Tracer">Tracer</option><option value="0x02E0000000000004" 
option-id="Mercy">Mercy</option><option value="0x02E0000000000005" 
option-id="Hanzo">Hanzo</option><option value="0x02E0000000000006" 
option-id="Torbjörn">Torbjörn</option><option value="0x02E0000000000008" 
option-id="Pharah">Pharah</option><option value="0x02E0000000000009" 
option-id="Winston">Winston</option><option value="0x02E000000000000A" 
option-id="Widowmaker">Widowmaker</option><option value="0x02E0000000000020" 
option-id="Zenyatta">Zenyatta</option><option value="0x02E0000000000029" 
option-id="Genji">Genji</option><option value="0x02E0000000000040" 
option-id="Roadhog">Roadhog</option><option value="0x02E0000000000042" 
option-id="McCree">McCree</option><option value="0x02E000000000006E" 
option-id="Soldier: 76">Soldier: 76</option><option value="0x02E0000000000079" 
option-id="Lúcio">Lúcio</option><option value="0x02E000000000007A" 
option-id="D.Va">D.Va</option><option value="0x02E000000000012F" 
option-id="Doomfist">Doomfist</option><option value="0x02E000000000013B" 
option-id="Ana">Ana</option><option value="0x02E000000000013E" 
option-id="Orisa">Orisa</option></select></div></div><hr/><div 
data-group-id="stats" data-category-id="0x02E00000FFFFFFFF"
							^^^ THIS IS WHERE THE ACTUAL STAT DATA BEGINS ... END 1st SCRAPE HERE
*/


