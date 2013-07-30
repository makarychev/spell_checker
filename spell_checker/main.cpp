// spell_checker.cpp : 
// Maksym Makarychev.
// 13.07.2013

#include "SpellChecker.h"
#include "Vocabulary.h"
#include "Text.h"
#include <memory> // shared_ptr
#include <fstream>

#ifdef _CONSOLE_
#include "iostream"
#include <time.h>
#endif

using namespace std;

void WriteResult(TextContainer *mResult, string filename)
{
	fstream file;
	DWORD nLine = 0;
	file.open(filename.c_str(), fstream::out);
	if (!file.is_open())
		throw "Output file is not open";
	
	for (TextContainer::iterator it = mResult->begin(); it != mResult->end(); ++it)
	{
		if (nLine != (*it).first)
		{
			file << endl;
			nLine = (*it).first;
		}
		file << (*it).second << " ";
	}
	
	file.close();
}

int main()
{
	try
	{
#ifdef _CONSOLE_
		long t;							//debug
		t = clock();					//debug
#endif
		TextContainer mResult;

		{

			shared_ptr<CSpellChecker> pSpellChecker (new CSpellChecker); 
		
			CVocabulary *pVocablurary = CVocabulary::getInstance();
			pVocablurary->LoadFromFile(INPUT_FILE);

			CText *pText = CText::getInstance();
			pText->LoadFromFile(INPUT_FILE);

			DWORD result = pSpellChecker->EvaluateRes(&mResult);
			printf( "\tEvaluateRes: %ld\n", result);	//debug
			WriteResult(&mResult, OUTPUT_FILE);
		}
#ifdef _CONSOLE_
		t = clock() - t; // single function delta meter					//debug 
		printf( "\tProgram takes %d millisecond.\n", t );	//debug
#endif
	}
	catch (const char* sErr)
	{
		printf("Error description: %s\n", sErr);
	}
	catch (...)
	{
		printf("Undefined error!\n");
	}
	return 0;
}

