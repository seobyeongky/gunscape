//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: random.cpp
//
// 내용: 랜덤수 결정
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "random.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

unsigned int m_w = static_cast<unsigned int>(time(nullptr));
unsigned int m_z = static_cast<unsigned int>(time(nullptr));

FILE *fp = NULL;

unsigned int GetUint()
{
	m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

float GetUniform()
{
	unsigned int u = GetUint();
	return (u + 1.0f) * 2.328306435454494e-10f;
}

//
// network independent functions
//
int my_rand_int(int min, int max)
{
	if(min == max)
		return min;

	unsigned int n = GetUint();
	if (max - min+1 == 0) return 0; 
	return n % (max - min+1) + min;
}

float my_rand_float(float min, float max)
{
	return GetUniform() * (max - min) + min;
}

void create_dumper()
{
	if (!fp)
	{
		fopen_s(&fp, "random_log.txt", "w");
		assert(fp && "random log text not initialized");
		atexit([](){
			fclose(fp);
		});
	}
}

//
// network dependant functions
//
float rand_float(float min, float max, const char * tag)
{
	create_dumper();
	fprintf_s(fp, "rand_float : %f, %f with tag %s\n", min, max, tag);
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

int rand_int(int min, int max, const char * tag)
{
	create_dumper();
	fprintf_s(fp, "rand_int : %d, %d with tag %s\n", min, max, tag);

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


int randA(int x, const char * tag)
{
	create_dumper();
	fprintf_s(fp, "randA : %d with tag %s\n", x, tag);

	if(x>0)
		return rand_int(0,x,tag);
	else
		return 0;
}

int randA_1(int x, const char * tag)
{
	create_dumper();
	fprintf_s(fp, "randA_1 : %d with tag %s\n", x, tag);

	if(x>1)
		return rand_int(1,x,tag);
	else
		return 1;
}


bool randB(int x, int point, const char * tag)
{
	create_dumper();
	fprintf_s(fp, "randB : %d, %d with tag %s\n", x, point, tag);

	return (randA(x,tag) <= point);
}

int randC(int dice, int x, const char * tag)
{
	create_dumper();
	fprintf_s(fp, "rand_float : %d, %d with tag %s\n", dice, x, tag);

	int a=0;
	for(int i=0;i<dice;i++)
		a += randA_1(x,tag);
	return a;
}