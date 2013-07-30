#include "Vocabulary.h"
#include <fstream>
#include <algorithm>

#ifdef _CONSOLE_
#include <time.h> // debug
#include <iostream>
#endif

using namespace std;

CVocabulary* CVocabulary::pVocabularyInst = NULL;

CVocabulary *CVocabulary::getInstance()
{
	if(pVocabularyInst == NULL)
		pVocabularyInst = new CVocabulary();
	return pVocabularyInst;
}

CVocabulary::CVocabulary(void)
{
	string str;
	// for coordination find(length)
	for (int i = 0; i < SCH_WORD_SIZE_MAX + 1; ++i)
	{
		str += " ";
		vVocabulary.insert(pair<DWORD, string>(i, str)); //TODO: What a cheat?
	}
}


CVocabulary::~CVocabulary(void)
{
	std::cout << "~CVocabulary FUUUKCKCKCKCKCCK!";
}

void CVocabulary::LoadFromFile(string filename)
{
#ifdef _CONSOLE_
	long t;							//debug
	t = clock();					//debug
#endif
	fstream file;
	file.open(filename.c_str(), fstream::in);
	if (!file.is_open())
		throw "Vocabulary file is not open";

	string strIn;
	file >> strIn;
	while (strcmp(strIn.c_str(), "==="))// || file.eof()) //TODO: optimize here?
	{
		transform(strIn.begin(), strIn.end(), strIn.begin(), ::tolower);
		vVocabulary.insert(pairByteStr(strIn.length(), strIn)); //TODO: such pair will be better to specify as typedef in header

		file >> strIn;
	}
	file.close();

#ifdef _CONSOLE_
	t = clock() - t;												//debug
	printf( "\tLoading vocabulary takes %d millisecond.\n", t );	//debug
#endif
}


// Reviewed by Dimitris 15/07/2013