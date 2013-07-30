#pragma once

#include "Load.h"
#include "types.h"


class CText: Load
{
public:
	static CText *getInstance();
	void LoadFromFile(std::string filename);
	TextContainer mText;

protected:
	static CText *pTextInst;

private:
	CText(void);
	~CText(void);

	void SkipVocabulary(std::fstream& f);
};

