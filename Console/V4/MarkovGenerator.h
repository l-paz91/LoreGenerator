// -----------------------------------------------------------------------------
#ifndef MarkovGenerator_H
#define MarkovGenerator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <ctime>
#include <random>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

// -----------------------------------------------------------------------------

namespace MarkovHelpers
{
	inline int getRandomInt(int pMaxNum)
	{
		static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
		std::uniform_int_distribution<std::size_t> dist(0, pMaxNum - 1);
		return static_cast<int>(dist(rng));
	}

	// -----------------------------------------------------------------------------

	inline void tokenise(const std::string& pSentence, std::vector<std::string>& pOutTokens)
	{
		std::istringstream iss(pSentence);
		std::string word;
		
		while (iss >> word)
		{
			pOutTokens.push_back(word);
		}
	}

	// -----------------------------------------------------------------------------

	inline void replaceTokens(std::string& pOutString, const std::string& pWord, const std::string& pWordType)
	{
		auto replace = [](std::string& pStr, const std::string& pFrom, const std::string& pTo) 
			{
				size_t pos = 0;
				while ((pos = pStr.find(pFrom, pos)) != std::string::npos)
				{
					pStr.replace(pos, pFrom.length(), pTo);
					pos += pTo.length();
				}
			};

		replace(pOutString, pWordType, pWord);
	}

	// -----------------------------------------------------------------------------

	inline const std::string START_TOKEN = "<START>";
	inline const std::string END_TOKEN = "<END>";
}

// -----------------------------------------------------------------------------

class MarkovGenerator abstract
{
public:
	MarkovGenerator(int pOrder = 2)
		: mOrder(pOrder)
		, mIsTrained(false)
	{}

	virtual ~MarkovGenerator() = default;

	virtual void train(const std::vector<std::string>& pWordPool) = 0;
	virtual std::string generate() = 0;

	virtual bool isTrained() const { return mIsTrained; }

protected:
	// how many previous characters it considers. So a value of 2 means it will
	// 'remember' the last 2 characters when deciding what comes next
	int mOrder;

	bool mIsTrained;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MarkovGenerator_H