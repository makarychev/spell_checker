#pragma once
#include "Load.h"
#include <map>
#include "types.h"
#include "def.h"

using namespace std;

class CVocabulary: Load
{
public:
	static CVocabulary *getInstance();
	void LoadFromFile(string filename);
	multimap<DWORD, string> vVocabulary;

protected:
	static CVocabulary *pVocabularyInst;

private:
	CVocabulary(void);
	~CVocabulary(void);
};

