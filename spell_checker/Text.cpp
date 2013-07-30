#include "Text.h"
#include <fstream>


using namespace std;

CText* CText::pTextInst = NULL;

CText *CText::getInstance()
{
	if(pTextInst == NULL)
		pTextInst = new CText();
	return pTextInst;
}

CText::CText(void)
{
}

CText::~CText(void)
{
}

void CText::SkipVocabulary(fstream& f)
{
	string strIn;
	do
	{
		getline(f, strIn);
	}
	while ((strcmp(strIn.c_str(), "==="))); // || f.eof());
}

void CText::LoadFromFile(string filename)
{
	DWORD nLine = 0;
	fstream file;
	file.open(filename.c_str(), fstream::in);
	if (!file.is_open())
		throw "Text file is not open";

	SkipVocabulary(file);

	string strIn;
	getline(file, strIn);
	while (strcmp(strIn.c_str(), "===")) //|| file.eof())
	{
		DWORD pos = 0;
		DWORD len = 0;
		len = strIn.find(' ', pos);
		while (len != 0)
		{
			mText.insert(TextPair(nLine, strIn.substr(pos, len)));
			pos += len + 1;
			if (pos == 0)
				break;
			len = strIn.find(' ', pos) - pos;
		}
		getline(file, strIn);
		nLine++;
	}

	file.close();
}