#pragma once

#include "string"


class Load
{
public: 
		virtual void LoadFromFile(std::string filename) = 0;
};