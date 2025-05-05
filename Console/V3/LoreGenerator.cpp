// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "LoreGenerator.h"

// -----------------------------------------------------------------------------

int LoreGenerator::getRandomInt(int pMaxNum)
{
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	std::uniform_int_distribution<std::size_t> dist(0, pMaxNum - 1);
	return dist(rng);
}

// -----------------------------------------------------------------------------

void LoreGenerator::readIntoVector(std::vector<std::string>& pWordVector, const std::string& pFilename)
{
	if (std::ifstream inFile{ pFilename })
	{
		for (std::string line; std::getline(inFile, line); )
		{
			pWordVector.push_back(line);
		}
	}
	else
	{
		std::cout << "Error opening file " << pFilename << std::endl;
	}
}

// -----------------------------------------------------------------------------

void LoreGenerator::loadWordPools()
{
	std::vector<std::string> adjectivePool;
	readIntoVector(adjectivePool, "adjectives.txt");

	std::vector<std::string> nounPool;
	readIntoVector(nounPool, "nouns.txt");

	std::vector<std::string> properNounPool;
	readIntoVector(properNounPool, "properNouns.txt");
	mProperNounGen.train(properNounPool);

	mWordPools[EWordType::eADJECTIVE] = adjectivePool;
	mWordPools[EWordType::eNOUN] = nounPool;
	mWordPools[EWordType::ePROPER_NOUN] = properNounPool;
}

// -----------------------------------------------------------------------------

std::string LoreGenerator::getRandomWord(EWordType pType)
{
	if (pType == EWordType::ePROPER_NOUN)
	{
		return mProperNounGen.generate();
	}

	const auto& words = mWordPools[pType];
	const int index = getRandomInt(words.size());
	return words[index];
}

// -----------------------------------------------------------------------------

std::string LoreGenerator::generateLore(const std::vector<TemplateElement>& pTemplateVec)
{
	std::string result;

	for (const auto& elem : pTemplateVec)
	{
		// std::hold_alternative is a cool function that basically goes:
		// is this elements a string? If so we get the string using std::get<string>
		if (std::holds_alternative<std::string>(elem))
		{
			result += std::get<std::string>(elem);
		}
		// if it's an EWordType, we use std::get<EWordType> and then pass the result
		// to getRandomWord() to give us a random word of that WordType
		else if (std::holds_alternative<EWordType>(elem))
		{
			result += getRandomWord(std::get<EWordType>(elem));
		}
	}

	return result;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------