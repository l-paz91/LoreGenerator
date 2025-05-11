// -----------------------------------------------------------------------------
#ifndef MarkovSentenceGenerator_H
#define MarkovSentenceGenerator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <unordered_map>
#include <string>
#include <vector>

#include "MarkovGenerator.h"

// -----------------------------------------------------------------------------

struct VectorHash
{
	std::size_t operator()(const std::vector<std::string>& pVector) const 
	{
		std::size_t seed = pVector.size();

		for (const auto& word : pVector)
		{
			for (char letter : word)
			{
				seed ^= std::hash<char>{}(letter) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
		}

		return seed;
	}
};

// -----------------------------------------------------------------------------

class MarkovSentenceGenerator : MarkovGenerator
{
public:
	MarkovSentenceGenerator(int pOrder = 2)
		: MarkovGenerator(pOrder)
	{
	}

	// MarkovGenerator
	void train(const std::vector<std::string>& pWordPool) override;
	std::string generate() override;
	// ~MarkovGenerator

private:
	std::unordered_map<std::vector<std::string>, std::vector<std::string>, VectorHash> mMarkovChain;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MarkovSentenceGenerator_H