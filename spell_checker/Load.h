#pragma once

#include "string"
using namespace std;

class Load
{
public: 
		virtual void LoadFromFile(string filename) = 0;
};