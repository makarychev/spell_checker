#pragma once

#include <map>

typedef unsigned short int	WORD;
typedef unsigned int		DWORD;
typedef unsigned char		BYTE;

typedef std::multimap<BYTE, std::string> WordsContainer;
typedef std::pair<BYTE, std::string> pairByteStr;

typedef std::multimap<DWORD, std::string> TextContainer;
typedef std::pair<DWORD, std::string> TextPair;


