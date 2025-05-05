// -----------------------------------------------------------------------------
#ifndef LoreGenerator_H
#define LoreGenerator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>
#include <string>
#include <variant>
#include <vector>

#include "MarkovGenerator.h"

// -----------------------------------------------------------------------------

enum class EWordType
{
	eADJECTIVE,
	eNOUN,
	ePROPER_NOUN
};

// -----------------------------------------------------------------------------

// I'm using a std::variant here as it will allow us to make vector hold elements
// of different types. So here, each element in the template can be a literal string
// or a WordType
using TemplateElement = std::variant<std::string, EWordType>;

// -----------------------------------------------------------------------------

class LoreGenerator
{
public:
	LoreGenerator() 
		: mWordPools()
		, mProperNounGen(2)
	{}

	int getRandomInt(int pMaxNum);
	void readIntoVector(std::vector<std::string>& pWordVector, const std::string& pFilename);

	void loadWordPools();

	std::string getRandomWord(EWordType pType);
	std::string generateLore(const std::vector<TemplateElement>& pTemplateVec);

private:
	std::unordered_map<EWordType, std::vector<std::string>> mWordPools;

	// Markov models
	MarkovGenerator mProperNounGen;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !LoreGenerator_H