// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MarkovWordGenerator.h"

// -----------------------------------------------------------------------------

// take in a vector of words and 'train' the Markov model
void MarkovWordGenerator::train(const std::vector<std::string>& pWordPool)
{
	for (const std::string& word : pWordPool)
	{
		// adds padding at the start (__ for order-2) to mark the beginning of the word
		// adds an _ at the end to mark the end of the word
		std::string padded = std::string(mOrder, '_') + word + "_";
		for (uint32_t i = 0; i + mOrder < padded.size(); ++i)
		{
			std::string key = padded.substr(i, mOrder);
			char nextChar = padded[i + mOrder];
			mMarkovChain[key].push_back(nextChar);
		}
	}

	mIsTrained = true;
}

// -----------------------------------------------------------------------------

std::string MarkovWordGenerator::generate()
{
	// start with a blank padded key like '__' (if order-2), which matches the beginning
	// of the words it was trained on
	std::string result;
	std::string key(mOrder, '_');

	while (true)
	{
		// look up all the possible next characters for the current key
		const auto& options = mMarkovChain[key];
		if (options.empty())
		{
			break;
		}

		// randomly select one of them
		char nextChar = options[MarkovHelpers::getRandomInt(static_cast<int>(options.size()))];
		if (nextChar == '_')
		{
			break;
		}

		// append the character to the result
		result += nextChar;

		// update the key by removing the first character and adding the new one
		// stops if it reaches the end marker '_'
		key = key.substr(1) + nextChar;
	}

	if (result.empty())
	{
		return "No valid word generated";
	}
	else
	{
		return result;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------