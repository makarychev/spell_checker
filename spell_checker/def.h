#pragma once


#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SKIP_VOCABULARY	0x01

enum 
{
	SCH_ALPHABET_SIZE_EN	= 28,
	SCH_WORD_SIZE_MAX		= 50
};

enum 
{
	SCH_ERR_NULL_PTR		= 0x0003,
	SCH_ERR_BAD_ARGUMENT	= 0x0004
};