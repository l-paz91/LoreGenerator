// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MarkovSentenceGenerator.h"

// -----------------------------------------------------------------------------

void MarkovSentenceGenerator::train(const std::vector<std::string>& pWordPool)
{
	for (const auto& line : pWordPool)
	{
		std::vector<std::string> tokens;
		MarkovHelpers::tokenise(line, tokens);
		tokens.push_back(MarkovHelpers::END_TOKEN);
		
		std::vector<std::string> key(mOrder, MarkovHelpers::START_TOKEN);

		for (const auto& token : tokens)
		{
			mMarkovChain[key].push_back(token);
			key.erase(key.begin());
			key.push_back(token);
		}
	}

	mIsTrained = true;
}

// -----------------------------------------------------------------------------

std::string MarkovSentenceGenerator::generate()
{
	if (!mIsTrained)
	{
		return "Model needs to be trained.";
	}

	std::vector<std::string> key(mOrder, MarkovHelpers::START_TOKEN);
	std::vector<std::string> result;

	while (true)
	{
		const auto& options = mMarkovChain[key];
		if (options.empty())
		{
			break;
		}

		std::string nextWord = options[MarkovHelpers::getRandomInt(static_cast<int>(options.size()))];
		if (nextWord == MarkovHelpers::END_TOKEN)
		{
			break;
		}

		result.push_back(nextWord);
		key.erase(key.begin());
		key.push_back(nextWord);
	}

	std::stringstream ss;
	for (unsigned int i = 0; i < result.size(); ++i)
	{
		if (i > 0)
		{
			ss << " ";
		}

		ss << result[i];
	}

	return ss.str();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------