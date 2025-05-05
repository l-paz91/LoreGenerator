// -----------------------------------------------------------------------------
#ifndef MarkovGenerator_H
#define MarkovGenerator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <ctime>
#include <random>
#include <unordered_map>
#include <string>


// -----------------------------------------------------------------------------

class MarkovGenerator
{
public:
	MarkovGenerator(int pOrder = 2)
		: mOrder(pOrder)
		, mIsTrained(false)
	{}

	void train(const std::vector<std::string>& pWordPool);

	std::string generate();

	bool isTrained() const { return mIsTrained; }

private:
	int getRandomInt(int pMaxNum)
	{
		static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
		std::uniform_int_distribution<std::size_t> dist(0, pMaxNum - 1);
		return dist(rng);
	}

	// a map from the key (a string of mOrder characters) to a vector of possible 
	// next characters
	std::unordered_map<std::string, std::vector<char>> mMarkovChain;

	// how many previous characters it considers. So a value of 2 means it will
	// 'remember' the last 2 characters when deciding what comes next
	int mOrder;

	bool mIsTrained;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MarkovGenerator_H