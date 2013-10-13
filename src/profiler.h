/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */

#ifndef _PROFILE_H
#define _PROFILE_H

//#define __PROFILE__


void ProfileInit( void ); //프로그램 시작할때 호출한다.
void ProfileBegin( char* name ); //분석을 원하는 범위시작에 쓴다.
void ProfileEnd( char* name ); //그 범위가 끝날때 쓴다.(인자는 ProfileBegin랑 같아야함)
void ProfileDumpOutputToBuffer( void ); //한 프레임이 끝나는 위치에 쓴다.

void ProfileSaveBuffer( void ); //정보를 profile.txt에 저장하는 함수
const char* ProfileGetBuffer( void ); //정보를 char*로 리턴함. ( 이걸 출력하면 실시간으로 퍼센티지 확인가능)



#endif
