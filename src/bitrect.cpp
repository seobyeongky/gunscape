//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: BitRect.cpp
//
// 내용: 비트배열을 저장하는 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "bitrect.h"


const int BitRect::int_bit = sizeof(int)*8;


BitRect::BitRect(int width_, int height_):
width(width_), height(height_)
{
	int hei_size = (height+int_bit-1)/int_bit;
	bit_field = new int*[width];
	for(int i=0; i< width; i++)
		bit_field[i] = new int[hei_size];
	for(int i=0; i< width; i++)
		for(int j=0; j< hei_size; j++)
			bit_field[i][j] = 0;
}	

BitRect::~BitRect()
{
	for(int i=0; i< width; i++)
		delete [] bit_field[i];
	delete [] bit_field;
}

void BitRect::AllUnset()
{
	int hei_size = (height+int_bit-1)/int_bit;
	for(int i=0; i< width; i++)
		for(int j=0; j< hei_size; j++)
			bit_field[i][j] = 0;
}