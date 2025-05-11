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

#include "MarkovWordGenerator.h"
#include "MarkovSentenceGenerator.h"

// -----------------------------------------------------------------------------

enum class EWordType
{
	eADJECTIVE,
	eNOUN,
	ePROPER_NOUN,
	eITEM,
	eSENTENCE
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
		, mItemTemplates()
		, mNameProvided()
		, mItemLoreGen(1)
		, mProperNounWordGen(2)
	{
		loadWordPools();
	}

	std::string generateItem();

private:
	void readIntoVector(std::vector<std::string>& pWordVector, const std::string& pFilename);
	void loadWordPools();

	std::string getRandomToken(EWordType pType, MarkovSentenceGenerator& pModel);
	std::string generateLoreFromTemplate(const std::vector<TemplateElement>& pTemplateVec, MarkovSentenceGenerator& pModel);
	void getRandomSentence(std::string& pOutLore, MarkovSentenceGenerator& pModel);
	void generateItemLore(std::string& pOutItemLore);

	void parseTemplateLine(std::vector<TemplateElement>& pOutTemplate, const std::string& pLine);

	std::unordered_map<EWordType, std::vector<std::string>> mWordPools;
	std::vector<std::vector<TemplateElement>> mItemTemplates;

	std::string mNameProvided;

	// Markov models
	MarkovSentenceGenerator mItemLoreGen;
	MarkovWordGenerator mProperNounWordGen;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !LoreGenerator_H