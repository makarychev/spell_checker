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

void WriteResult(multimap<DWORD, string> *mResult, string filename)
{
	fstream file;
	DWORD nLine = 0;
	file.open(filename.c_str(), fstream::out);
	if (!file.is_open())
		throw "Output file is not open";
	
	for (multimap<DWORD, string>::iterator it = mResult->begin(); it != mResult->end(); ++it)
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
		multimap<DWORD, string> mResult;
		shared_ptr<CSpellChecker> pSpellChecker (new CSpellChecker); 
		
		CVocabulary *pVocablurary = CVocabulary::getInstance();
		pVocablurary->LoadFromFile(INPUT_FILE);

		CText *pText = CText::getInstance();
		pText->LoadFromFile(INPUT_FILE);

		pSpellChecker->EvaluateRes(&mResult);
		WriteResult(&mResult, OUTPUT_FILE);
#ifdef _CONSOLE_
		t = clock() - t;												//debug
		printf( "\tLoading vocabulary takes %d millisecond.\n", t );	//debug
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

