#pragma once
#include <string>
#include "types.h"
#include "Vocabulary.h"
#include "Text.h"
#include <list>



class CSpellChecker
{
public:
	CSpellChecker(void);
	~CSpellChecker(void);

	DWORD EvaluateRes(TextContainer *lStrRes); // predefine typedef of multimap<DWORD, string>

private:
	CVocabulary *pVocabulary;
	CText		*pText;
	DWORD DamerauLevenshteinDistance(std::string source, std::string target, BYTE errCount); // TODO: should be changed by strategy pattern
	std::string getResultWords(std::map<std::string, WORD> setRes, std::string sWord);
};

