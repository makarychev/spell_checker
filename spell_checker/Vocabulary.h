#pragma once

#include "Load.h"
#include <map>
#include "types.h"
#include "def.h"


class CVocabulary: Load
{
public:
	static CVocabulary *getInstance();
	void LoadFromFile(std::string filename);
	WordsContainer vVocabulary;

protected:
	static CVocabulary *pVocabularyInst;

private:
	CVocabulary(void);
	~CVocabulary(void);
};

