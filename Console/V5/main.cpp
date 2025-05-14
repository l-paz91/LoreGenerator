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

void createLore(LoreGenerator& pLoreGenerator)
{
	using namespace std;

	cout << "----------------------------------------------------\n";
	cout << "Welcome to the Lore Generator!\n";
	cout << "This program generates random item lore based on templates.\n";
	cout << "----------------------------------------------------\n\n";

	cout << "Number of lore descriptions to generate:\n>>";
	int numDescriptions = 0;
	cin >> numDescriptions;

	for (int i = 0; i < numDescriptions; ++i)
	{
		std::string generatedItemLore;
		if (pLoreGenerator.generateItem(generatedItemLore))
		{
			cout << generatedItemLore << "\n\n";
		}
		else
		{
			break;
		}
	}
}

// -----------------------------------------------------------------------------

int main()
{
	using namespace std;

	LoreGenerator loreGenerator;

	// start loop
	bool continueLoop = true;
	do
	{
		system("cls");
		createLore(loreGenerator);
		cout << "----------------------------------------------------\n";
		cout << "Do you want to generate more lore? (y/n)\n>>";
		char choice;
		cin >> choice;
		if (choice == 'n' || choice == 'N')
		{
			continueLoop = false;
			break;
		}
		loreGenerator.resetNameProvided();

	} while (continueLoop);

	cout << "\n----------------------------------------------------\n";
	cout << "\nPress any key to quit...";
	char c;
	cin >> c;

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
