// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	main.cpp
*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <ctime>
#include <iostream>
#include <random>
#include <unordered_map>
#include <string>
#include <variant>
#include <vector>

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

int getRandomInt(int pMaxNum)
{
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	std::uniform_int_distribution<std::size_t> dist(0, pMaxNum - 1);
	return dist(rng);
}

// -----------------------------------------------------------------------------

std::unordered_map<EWordType, std::vector<std::string>> gWordPools =
{
	{ EWordType::eADJECTIVE, { "Ancient", "Forgotten", "Cursed", "Glorious" } },
	{ EWordType::eNOUN, { "Blade", "Crown", "Relic", "Scroll" } },
	{ EWordType::ePROPER_NOUN, { "Aldur", "Thalor", "Ekran", "Zorath" } }
};

// -----------------------------------------------------------------------------

std::string getRandomWord(EWordType pType)
{
	const auto& words = gWordPools[pType];
	const int index = getRandomInt(words.size());
	return words[index];
}

// -----------------------------------------------------------------------------

std::string generateLore(const std::vector<TemplateElement>& pTemplateVec) 
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

int main()
{
	using namespace std;

	vector<vector<TemplateElement>> templateVec =
	{
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " was said to possess unspeakable power." },
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " will consume all who wield it." },
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " comes with a free warranty." },
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " is cursed with vanishing." }
	};

	// choose a template
	const int index = getRandomInt(templateVec.size());
	const auto& chosenTemplate = templateVec[index];

	cout << generateLore(chosenTemplate) << std::endl;

	cout << "\nPress any key to continue...";
	char c;
	cin >> c;

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
