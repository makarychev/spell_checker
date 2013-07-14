#pragma once

#include "Load.h"
#include <map>
#include "types.h"

using namespace std;

class CText: Load
{
public:
	static CText *getInstance();
	void LoadFromFile(string filename);
	multimap<DWORD, string> mText;

protected:
	static CText *pTextInst;

private:
	CText(void);
	~CText(void);

	void SkipVocabulary(fstream& f);
};

