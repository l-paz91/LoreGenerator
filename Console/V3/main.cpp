// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	main.cpp
*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iostream>
#include <string>

#include "LoreGenerator.h"

// -----------------------------------------------------------------------------

int main()
{
	using namespace std;

	LoreGenerator loreGenerator;

	// Load the word pools from files
	loreGenerator.loadWordPools();

	vector<vector<TemplateElement>> templateVec =
	{
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " was said to possess unspeakable power." },
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " will consume all who wield it." },
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " comes with a free warranty." },
		{ "The ", EWordType::eADJECTIVE, " ", EWordType::eNOUN, " of ", EWordType::ePROPER_NOUN, " is cursed with vanishing." }
	};

	// choose a template
	const int index = loreGenerator.getRandomInt(templateVec.size());
	const auto& chosenTemplate = templateVec[index];

	cout << loreGenerator.generateLore(chosenTemplate) << std::endl;

	cout << "\nPress any key to continue...";
	char c;
	cin >> c;

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
