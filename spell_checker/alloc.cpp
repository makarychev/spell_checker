#include "stdafx.h"
#include "alloc.h"

//template <class TYPE>
//TYPE** AllocateArray(int rowSize, int colSize)
//{
//	//allocate the array
//	TYPE** arr = new TYPE*[rowSize];
//	for(int i = 0; i < rowSize; i++)
//		arr[i] = new T[colSize];
//	return arr;
//}
//
//template <class TYPE>
//void DeallocateArray(TYPE** arr, int rowSize)
//{
//	//deallocate the array
//	for(int i = 0; i < rowSize; i++)
//		delete[] arr[i];
//	delete[] arr;
//}