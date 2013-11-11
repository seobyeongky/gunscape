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
float rand_float(float min, float max);
int rand_int(int min, int max);
int randA(int x);
int randA_1(int x);
bool randB(int x, int point);
int randC(int dice, int x);


#endif // __RANDOM_H__