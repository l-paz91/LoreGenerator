// -----------------------------------------------------------------------------
#ifndef MarkovWordGenerator_H
#define MarkovWordGenerator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <unordered_map>
#include <string>
#include <vector>

#include "MarkovGenerator.h"

// -----------------------------------------------------------------------------

class MarkovWordGenerator : MarkovGenerator
{
public:
	MarkovWordGenerator(int pOrder = 2)
		: MarkovGenerator(pOrder)
	{
	}

	// MarkovGenerator
	void train(const std::vector<std::string>& pWordPool) override;
	std::string generate() override;
	// ~MarkovGenerator

private:
	// a map from the key (a string of mOrder characters) to a vector of possible 
	// next characters
	std::unordered_map<std::string, std::vector<char>> mMarkovChain;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MarkovWordGenerator_H