#pragma once


#include "types.h"

template <class TYPE>
TYPE** AllocateArray(DWORD rowSize, DWORD colSize)
{
	//allocate the array
	TYPE** arr = new TYPE*[rowSize];
	for(DWORD i = 0; i < rowSize; i++)
		arr[i] = new TYPE[colSize];
	return arr;
}

template <class TYPE>
void DeallocateArray(TYPE** arr, DWORD rowSize)
{
	//deallocate the array
	for(DWORD i = 0; i < rowSize; i++)
		delete[] arr[i];
	delete[] arr;
}

template <typename InIt1, typename InIt2, typename OutIt>
OutIt unordered_set_intersection(InIt1 b1, InIt1 e1, InIt2 b2, InIt2 e2, OutIt out) {
	while (!(b1 == e1)) {
		if (!(std::find(b2, e2, *b1) == e2)) {
			*out = *b1;
			++out;
		}

		++b1;
	}

	return out;
}