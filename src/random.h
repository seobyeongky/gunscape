//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: random.h
//
// 내용: 랜덤수 결정
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RANDOM_H__
#define  __RANDOM_H__

// network sync independant
float my_rand_float(float min, float max);
int my_rand_int(int min, int max);

// network sync dependent
float rand_float(float min, float max, const char * tag);
int rand_int(int min, int max, const char * tag);
int randA(int x, const char * tag);
int randA_1(int x, const char * tag);
bool randB(int x, int point, const char * tag);
int randC(int dice, int x, const char * tag);

#endif // __RANDOM_H__