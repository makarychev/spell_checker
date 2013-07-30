#include "SpellChecker.h"
#include "alloc.h"
#include <map>
#include "def.h"

#ifdef _CONSOLE_
#include <time.h> // debug
#include "iostream"
#endif


using namespace std;

CSpellChecker::CSpellChecker(void)
{
	pVocabulary = CVocabulary::getInstance();
	pText		= CText::getInstance();
}

CSpellChecker::~CSpellChecker(void)
{
}

DWORD CSpellChecker::DamerauLevenshteinDistance(string source, string target, BYTE errCount)
{
	DWORD Res = -1;

	if (source.length() == 0)
	{
		if (target.length() == 0)
			return 0;
		else
			return target.length();
	}
	else if (target.length() == 0)
		return source.length();
	
	DWORD **score = NULL;
	score = AllocateArray<DWORD>(source.length() + 2, target.length() +2);

	if (score == NULL)
		return SCH_ERR_NULL_PTR;
	
	DWORD INF = source.length() + target.length();
	score[0][0] = INF;
	for (DWORD i = 0; i <= source.length(); i++)
	{
		score[i + 1][1] = i; 
		score[i + 1][0] = INF;
	}
	for (DWORD i = 0; i <= target.length(); i++)
	{
		score[1][i + 1] = i; 
		score[0][i + 1] = INF;
	}

	map<char, DWORD> sd;

	for each (char letter in (source + target))
	{
		if (sd.find(letter) == sd.end())
			sd.insert(std::pair<char,DWORD>(letter, 0));
	}

	for (DWORD i = 1; i<= source.length(); i++)
	{
		int DB = 0;
		for (DWORD j = 1; j <= target.length(); j++)
		{
			DWORD i1 = sd[target[j - 1]];
			DWORD j1 = DB;

			if (source[i - 1]  == tolower(target[j - 1]))
			{
				score[i + 1][j + 1] = score[i][j];
				DB = j;
			}
			else
			{
				score[i + 1][j + 1] = min(score[i][j], min(score[i + 1][j], score[i][j +1])) + 1;
			}

			score[i + 1][j + 1] = min(score[i + 1][j + 1], score[i1][j1] + (i - i1 - 1) + 1 + (j - j1 - 1));
		}

		sd[source[i - 1]] = i;
		if (source.length() > target.length())
		{
			if (score[i+1][i] > errCount)
			{	
				Res = errCount + 1;
				goto lblEnd;
			}
		}
		else if (source.length() < target.length())
		{
			if (score[i][i+1] > errCount)
			{	
				Res = errCount + 1;
				goto lblEnd;
			}
		}
		else
		{
			if (score[i+1][i+1] > errCount)
			{	
				Res = errCount + 1;
				goto lblEnd;
			}
		}
	}
	Res = score[source.length() + 1][target.length() + 1];
	
lblEnd:
	DeallocateArray<DWORD>(score, source.length() + 2);

	return Res;
}

DWORD CSpellChecker::EvaluateRes(std::multimap<DWORD, string> *lStrRes)
{
#ifdef _CONSOLE_
	long t;							//debug
	t = clock();					//debug
#endif
	DWORD nLine = -1;
	if (lStrRes == NULL)
		return SCH_ERR_NULL_PTR;

	DWORD wordsCounter = 0;

	for (TextContainer::iterator it = pText->mText.begin(); it != pText->mText.end(); ++it)
	{
		if (it->second.empty())
			continue;
		string strRes;
		DWORD start = 0, end = 0;
		map<string, WORD> lStrResult;

		if ((*it).second.length() == 1)
			start = 1;
		else
			start = (*it).second.length() - 1;

		if ((*it).second.length() == SCH_WORD_SIZE_MAX)
			end = (*it).second.length() + 1;
		else
			end = (*it).second.length() + 2;

		wordsCounter++;
		
		// get only 3-length word (current.length - 1, current.length, current.length + 1)
		for (WordsContainer::iterator it1 = pVocabulary->vVocabulary.find(start); it1 != pVocabulary->vVocabulary.find(end); ++it1)   
		{
			if (it1->second.empty())
				continue;
			if ((*it1).second.length() > 1)
			{
				char cTmp = tolower((*it).second[1]);
				//optimization skip words
				if (((*it1).second[0] != cTmp) && ((*it1).second[0] != tolower((*it).second[0])) && ((*it1).second[1] != cTmp))
					continue;
			}
			DWORD res = DamerauLevenshteinDistance((*it).second, (*it1).second, 1); 
			if (res == 0) 
			{
				lStrResult.clear();
				lStrResult.insert(pair<string, WORD>((*it).second, (*it).second.length()));
				break;
			}
			else if (res == 1)
				lStrResult.insert(pair<string, WORD>((*it1).second, (*it1).second.length()));
			else 
				continue;
		}
		strRes += getResultWords(lStrResult, (*it).second);
		lStrRes->insert(pair<DWORD, string>((*it).first, strRes));
	}

#ifdef _CONSOLE_
	t = clock() - t;												//debug
	printf("\tVocabulary size (words count): %ld .\n", pVocabulary->vVocabulary.size());
	printf( "\tEvaluated algorithm takes %d millisecond.\n", t );	//debug
	printf("\tWords processed: %ld .\n", wordsCounter);
	printf("\tOne word requires time millisec: %ld .\n", (t / wordsCounter));

#endif
}

string CSpellChecker::getResultWords(map<string, WORD> setRes, string sWord)
{
	string strRes;
	
	// construct line
	if (setRes.empty()) //TODO: 
		return "{" + sWord + "?}"; 
	else if (setRes.size() == 1) // TODO: review?
		return (*setRes.begin()).first; 
	else
	{
		strRes += "{";
		for (map<string, WORD>::iterator iter = setRes.begin(); iter != setRes.end(); ++iter)
			strRes += (*iter).first + " ";
		//strRes[strRes.length() - 1] = '}';
		strRes += '}';
	}

	return strRes;
}