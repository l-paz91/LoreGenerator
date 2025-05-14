// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "LoreGenerator.h"

// -----------------------------------------------------------------------------

void LoreGenerator::readIntoVector(std::vector<std::string>& pWordVector, const std::string& pFilename)
{
	if (std::ifstream inFile{ pFilename })
	{
		for (std::string line; std::getline(inFile, line); )
		{
			pWordVector.push_back(line);
		}
	}
	else
	{
		std::cout << "Error opening file " << pFilename << std::endl;
	}
}

// -----------------------------------------------------------------------------

void LoreGenerator::loadWordPools()
{
	std::vector<std::string> adjectivePool;
	readIntoVector(adjectivePool, "adjectives.txt");

	std::vector<std::string> nounPool;
	readIntoVector(nounPool, "nouns.txt");

	std::vector<std::string> properNounPool;
	readIntoVector(properNounPool, "properNouns.txt");
	mProperNounWordGen.train(properNounPool);

	std::vector<std::string> itemLorePool;
	readIntoVector(itemLorePool, "itemLore.txt");
	mItemLoreGen.train(itemLorePool);

	std::vector<std::string> itemPool;
	readIntoVector(itemPool, "simple_items.txt");

	std::ifstream inFile("ItemTemplates.txt");
	for (std::string line; std::getline(inFile, line); ) 
	{
		std::vector<TemplateElement> temp;
		parseTemplateLine(temp, line);
		mItemTemplates.push_back(temp);
	}

	mWordPools[EWordType::eADJECTIVE] = adjectivePool;
	mWordPools[EWordType::eNOUN] = nounPool;
	mWordPools[EWordType::ePROPER_NOUN] = properNounPool;
	mWordPools[EWordType::eITEM] = itemPool;
}

// -----------------------------------------------------------------------------

std::string LoreGenerator::getRandomToken(EWordType pType, MarkovSentenceGenerator& pModel)
{
	if (pType == EWordType::ePROPER_NOUN)
	{
		return mProperNounWordGen.generate();
	}
	
	if (pType == EWordType::eSENTENCE)
	{
		std::string sentence;
		getRandomSentence(sentence, pModel);
		return sentence;
	}

	const auto& words = mWordPools[pType];
	if (!words.size())
	{
		std::cerr << "You've missed training/filling a word pool";
	}

	const int index = MarkovHelpers::getRandomInt(static_cast<int>(words.size()));

	if (pType == EWordType::eITEM)
	{
		if (!mNameProvided.empty())
		{
			return mNameProvided;
		}

		mNameProvided = words[index];
	}

	return words[index];
}

// -----------------------------------------------------------------------------

std::string LoreGenerator::generateLoreFromTemplate(
	const std::vector<TemplateElement>& pTemplateVec,
	MarkovSentenceGenerator& pModel)
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
			result += getRandomToken(std::get<EWordType>(elem), pModel);
		}
	}

	return result;
}

// -----------------------------------------------------------------------------

void LoreGenerator::getRandomSentence(std::string& pOutLore, MarkovSentenceGenerator& pModel)
{
	pOutLore = pModel.generate();
}

// -----------------------------------------------------------------------------

void LoreGenerator::generateItemLore(std::string& pOutItemLore)
{
	using namespace std;

	const int index = static_cast<int>(MarkovHelpers::getRandomInt(mItemTemplates.size()));
	auto itemTemplate = mItemTemplates[index];
	pOutItemLore = generateLoreFromTemplate(itemTemplate, mItemLoreGen);
}

// -----------------------------------------------------------------------------

bool LoreGenerator::generateItem(std::string& pOutLore)
{
	using namespace std;

	if (mNameProvided.empty())
	{
		cout << "Choose and option:\n";
		cout << "1 - Enter Item name\n";
		cout << "2 - Generate random item\n";
		cout << "3 - Exit\n";
		cout << ">> ";

		int selection;
		cin >> selection;

		switch (selection)
		{
		case 1:
		{
			cout << "\n\nEnter item name: ";
			string itemName;

			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, itemName);

			mNameProvided = itemName;
			break;
		}
		case 2: default:
		{
			mNameProvided = "";
			break;
		}
		case 3:
		{
			return false;
		}
		}
	}

	generateItemLore(pOutLore);
	cin.clear();

	return true;
}

// -----------------------------------------------------------------------------

void LoreGenerator::parseTemplateLine(std::vector<TemplateElement>& pOutTemplate, const std::string& pLine)
{
	std::string buffer;

	for (unsigned int i = 0; i < pLine.length(); ++i)
	{
		if (pLine[i] == '{' && i + 1 < pLine.length() && pLine[i + 1] == '{')
		{
			// flush buffer as a literal string
			if (!buffer.empty())
			{
				pOutTemplate.push_back(buffer);
				buffer.clear();
			}

			// extract token
			unsigned int end = pLine.find("}}", i);
			if (end != std::string::npos)
			{
				std::string token = pLine.substr(i + 2, end - (i + 2));

				if (token == "item")
				{
					pOutTemplate.push_back(EWordType::eITEM);
				}
				else if (token == "adjective")
				{
					pOutTemplate.push_back(EWordType::eADJECTIVE);
				}
				else if (token == "noun")
				{
					pOutTemplate.push_back(EWordType::eNOUN);
				}
				else if (token == "proper_noun")
				{
					pOutTemplate.push_back(EWordType::ePROPER_NOUN);
				}
				else if (token == "sentence")
				{
					pOutTemplate.push_back(EWordType::eSENTENCE);
				}
				// add more mappings here if needed
				i = end + 1; // skip to end of token
			}
		}
		else
		{
			buffer += pLine[i];
		}
	}

	if (!buffer.empty())
	{
		pOutTemplate.push_back(buffer);
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------