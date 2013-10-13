//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: random.cpp
//
// 내용: 랜덤수 결정
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

float rand_float(float min, float max)
{
	if(min == max)
		return min;

	if(min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	//min = (float)(random_number % (int)((max - min)*100 + 1)) /100 + min;
	//random_number = (((random_number*214013L + 2531011L)>>16)&0x7fff);
	min = (float)(rand() % (int)((max - min)*100 + 1)) /100 + min;

	return min;
}

int rand_int(int min, int max)
{
	if(min == max)
		return min;

	if(min > max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	//min = (random_number % (max - min+1)) + min;

	//random_number = (((random_number*214013L + 2531011L)>>16)&0x7fff);
	min = (rand() % (max - min+1)) + min;


	return min;
}


int randA(int x)
{
	if(x>0)
		return rand_int(0,x);
	else
		return 0;
}

int randA_1(int x)
{
	if(x>1)
		return rand_int(1,x);
	else
		return 1;
}


bool randB(int x, int point)
{
	return (randA(x) <= point);
}

int randC(int dice, int x)
{
	int a=0;
	for(int i=0;i<dice;i++)
		a += randA_1(x);
	return a;
}