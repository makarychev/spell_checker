#pragma once
#include <string>
#include "types.h"
#include "Vocabulary.h"
#include "Text.h"
#include <list>

using namespace std;

class CSpellChecker
{
public:
	CSpellChecker(void);
	~CSpellChecker(void);

	DWORD DamerauLevenshteinDistance(string source, string target);
	void EvaluateRes(multimap<DWORD,string> *lStrRes);

private:
	CVocabulary *pVocabulary;
	CText		*pText;

	string GetWordRes(map<string, WORD> setRes, string sWord);
};

