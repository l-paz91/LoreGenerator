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

	for (int i = 0; i < 5; ++i)
	{
		std::string generatedItemLore = loreGenerator.generateItem();
		cout << generatedItemLore << "\n\n";
	}

	cout << "\nPress any key to continue...";
	char c;
	cin >> c;

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------