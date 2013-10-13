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


void ProfileInit( void ); //���α׷� �����Ҷ� ȣ���Ѵ�.
void ProfileBegin( char* name ); //�м��� ���ϴ� �������ۿ� ����.
void ProfileEnd( char* name ); //�� ������ ������ ����.(���ڴ� ProfileBegin�� ���ƾ���)
void ProfileDumpOutputToBuffer( void ); //�� �������� ������ ��ġ�� ����.

void ProfileSaveBuffer( void ); //������ profile.txt�� �����ϴ� �Լ�
const char* ProfileGetBuffer( void ); //������ char*�� ������. ( �̰� ����ϸ� �ǽð����� �ۼ�Ƽ�� Ȯ�ΰ���)



#endif
