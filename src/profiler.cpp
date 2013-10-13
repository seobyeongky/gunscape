/* Copyright (C) Steve Rabin, 2000. 
* All rights reserved worldwide.
*
* This software is provided "as is" without express or implied
* warranties. You may freely copy and compile this source into
* applications you distribute provided that the copyright text
* below is included in the resulting source code, for example:
* "Portions Copyright (C) Steve Rabin, 2000"
*/


#include "profiler.h"
#include <string>
#include <assert.h>
#include <stdio.h>
#include <float.h>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#else
#include <stdio.h>
#include <sys/timeb.h>
#endif


#ifdef _WIN32
double g_StartTime = -1.0;
#else
struct timeb   g_StartTimeb;
#endif
double g_CurrentTime = -1.0;
double g_TimeLastTick = -1.0;



typedef struct {
	bool bValid;                 //Whether this data is valid
	unsigned int iProfileInstances;      //# of times ProfileBegin called
	int iOpenProfiles;           //# of times ProfileBegin w/o ProfileEnd
	char szName[256];            //Name of sample
	double fStartTime;            //The current open profile start time
	double fAccumulator;          //All samples this frame added together
	double fChildrenSampleTime;   //Time taken by all children
	unsigned int iNumParents;            //Number of profile parents
} ProfileSample;

typedef struct {
	bool bValid;        //Whether the data is valid
	char szName[256];   //Name of the sample
	double fAve;         //Average time per frame (percentage)
	double fMin;         //Minimum time per frame (percentage)
	double fMax;         //Maximum time per frame (percentage)
} ProfileSampleHistory;



#define NUM_PROFILE_SAMPLES 50
ProfileSample g_samples[NUM_PROFILE_SAMPLES];
ProfileSampleHistory g_history[NUM_PROFILE_SAMPLES];
double g_startProfile = 0.0;
double g_endProfile = 0.0;


void StoreProfileInHistory( char* name, double percent );
void GetProfileFromHistory( char* name, double* ave, double* min, double* max );
void InitTime( void );
double GetElapsedTime( void );
double GetExactTime( void );
void MarkTimeThisTick( void );

void ClearTextBuffer();
void PutTextBuffer(const char* c);

void ProfileInit( void )
{
#ifdef _DEBUG
	unsigned int i;

	for( i=0; i<NUM_PROFILE_SAMPLES; i++ ) {
		g_samples[i].bValid = false;
		g_history[i].bValid = false;
	}

	g_startProfile = GetExactTime();

	g_StartTime = GetExactTime();
#endif
}




void ProfileBegin( char* name )
{
#ifdef _DEBUG
	unsigned int i = 0;

	while( i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true ) {
		if( strcmp( g_samples[i].szName, name ) == 0 ) {
			//Found the sample
			g_samples[i].iOpenProfiles++;
			g_samples[i].iProfileInstances++;
			g_samples[i].fStartTime = GetExactTime();
			assert( g_samples[i].iOpenProfiles == 1 ); //max 1 open at once
			return;
		}
		i++;	
	}

	if( i >= NUM_PROFILE_SAMPLES ) {
		assert( !"Exceeded Max Available Profile Samples" );
		return;
	}

	strcpy_s( g_samples[i].szName, 256,  name );
	g_samples[i].bValid = true;
	g_samples[i].iOpenProfiles = 1;
	g_samples[i].iProfileInstances = 1;
	g_samples[i].fAccumulator = 0.0;
	g_samples[i].fStartTime = GetExactTime();
	g_samples[i].fChildrenSampleTime = 0.0;
#endif
}


void ProfileEnd( char* name )
{
#ifdef _DEBUG
	unsigned int i = 0;
	unsigned int numParents = 0;

	while( i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true )
	{
		if( strcmp( g_samples[i].szName, name ) == 0 )
		{  //Found the sample
			unsigned int inner = 0;
			int parent = -1;
			double fEndTime = GetExactTime();
			g_samples[i].iOpenProfiles--;

			//Count all parents and find the immediate parent
			while( g_samples[inner].bValid == true ) {
				if( g_samples[inner].iOpenProfiles > 0 )
				{  //Found a parent (any open profiles are parents)
					numParents++;
					if( parent < 0 )
					{  //Replace invalid parent (index)
						parent = inner;
					}
					else if( g_samples[inner].fStartTime >=
						g_samples[parent].fStartTime )
					{  //Replace with more immediate parent
						parent = inner;
					}
				}
				inner++;
			}

			//Remember the current number of parents of the sample
			g_samples[i].iNumParents = numParents;

			if( parent >= 0 )
			{  //Record this time in fChildrenSampleTime (add it in)
				g_samples[parent].fChildrenSampleTime += fEndTime -
					g_samples[i].fStartTime;
			}

			//Save sample time in accumulator
			g_samples[i].fAccumulator += fEndTime - g_samples[i].fStartTime;
			return;
		}
		i++;	
	}
#endif
}



void ProfileDumpOutputToBuffer( void )
{
#ifdef _DEBUG
	unsigned int i = 0;

	g_endProfile = GetExactTime();
	ClearTextBuffer();

	PutTextBuffer( "  Ave :   Min :   Max :   # : Profile Name\n" );
	PutTextBuffer( "--------------------------------------------\n" );

	while( i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true ) {
		if(g_startProfile > g_endProfile)
			break;
 
		unsigned int indent = 0;
		double sampleTime, percentTime, aveTime, minTime, maxTime;
		char line[256], name[256], indentedName[256];
		char ave[256], min[256], max[256], num[256];

		if( g_samples[i].iOpenProfiles < 0 ) {
			assert( !"ProfileEnd() called without a ProfileBegin()" );	
		}
		else if( g_samples[i].iOpenProfiles > 0 ) {
			assert( !"ProfileBegin() called without a ProfileEnd()" );
		}

		sampleTime = g_samples[i].fAccumulator - g_samples[i].fChildrenSampleTime;
		if(g_endProfile == g_startProfile )
			percentTime = 0.0;
		else
			percentTime = ( sampleTime / (g_endProfile - g_startProfile ) ) * 100.0;


		aveTime = minTime = maxTime = percentTime;

		//Add new measurement into the history and get the ave, min, and max
		StoreProfileInHistory( g_samples[i].szName, percentTime );
		GetProfileFromHistory( g_samples[i].szName, &aveTime, &minTime, &maxTime );

		//Format the data
		sprintf_s( ave,256, "%3.1lf", aveTime );
		sprintf_s( min,256, "%3.1lf", minTime );
		sprintf_s( max,256, "%3.1lf", maxTime );
		sprintf_s( num,256, "%3d", g_samples[i].iProfileInstances );

		strcpy_s( indentedName, 256, g_samples[i].szName );
		for( indent=0; indent<g_samples[i].iNumParents; indent++ ) {
			sprintf_s( name, 256, "   %s", indentedName );
			strcpy_s( indentedName, 256, name );
		}

		sprintf_s(line, 256,"%5s : %5s : %5s : %3s : %s\n", ave, min, max, num, indentedName);
		PutTextBuffer( line );	//Send the line to text buffer
		i++;
	}

	{  //Reset samples for next frame
		unsigned int i;
		for( i=0; i<NUM_PROFILE_SAMPLES; i++ ) {
			g_samples[i].bValid = false;
		}
		g_startProfile = GetExactTime();
	}
#endif
}




void StoreProfileInHistory( char* name, double percent )
{
#ifdef _DEBUG
	MarkTimeThisTick();
	unsigned int i = 0;
	double oldRatio;
	double newRatio = 0.8f * GetElapsedTime();
	if( newRatio > 1.0f ) {
		newRatio = 1.0f;
	}
	oldRatio = 1.0f - newRatio;

	while( i < NUM_PROFILE_SAMPLES && g_history[i].bValid == true ) {
		if( strcmp( g_history[i].szName, name ) == 0 )
		{  //Found the sample
			g_history[i].fAve = (g_history[i].fAve*oldRatio) + (percent*newRatio);
			if( percent < g_history[i].fMin ) {
				g_history[i].fMin = percent;
			}
			else {
				g_history[i].fMin = (g_history[i].fMin*oldRatio) + (percent*newRatio);
			}

			if( g_history[i].fMin < 0.0f ) {
				g_history[i].fMin = 0.0f;
		 }


			if( percent > g_history[i].fMax ) {
				g_history[i].fMax = percent;
			}
			else {
				g_history[i].fMax = (g_history[i].fMax*oldRatio) + (percent*newRatio);
			}
			return;
		}
		i++;
	}

	if( i < NUM_PROFILE_SAMPLES )
	{  //Add to history
		strcpy_s( g_history[i].szName, 256, name );
		g_history[i].bValid = true;
		g_history[i].fAve = g_history[i].fMin = g_history[i].fMax = percent;
	}
	else {
		assert( !"Exceeded Max Available Profile Samples!");
	}
#endif
}

void GetProfileFromHistory( char* name, double* ave, double* min, double* max )
{
#ifdef _DEBUG
	unsigned int i = 0;
	while( i < NUM_PROFILE_SAMPLES && g_history[i].bValid == true ) {
		if( strcmp( g_history[i].szName, name ) == 0 )
		{  //Found the sample
			*ave = g_history[i].fAve;
			*min = g_history[i].fMin;
			*max = g_history[i].fMax;
			return;
		}
		i++;
	}	
	*ave = *min = *max = 0.0f;
#endif
}


void MarkTimeThisTick( void )
{
#ifdef _WIN32
	double newTime = GetExactTime() - g_StartTime;
#else
	struct timeb tp;

	ftime(&tp);

	double newTime = tp.time - g_StartTimeb.time +
		(tp.millitm/1000.0) - (g_StartTimeb.millitm/1000.0);

#endif

	g_TimeLastTick = newTime - g_CurrentTime;
	g_CurrentTime = newTime;

	if( g_TimeLastTick <= 0.0f ) {
		g_TimeLastTick = 0.001f;
	}

}

double GetElapsedTime( void )
{
	return( g_TimeLastTick );
}


double GetExactTime( void )
{
#ifdef _WIN32
	return( (double)(timeGetTime()%10000)/1000.0 );
#else
	struct timeb tp;

	ftime(&tp);

	return tp.time - g_StartTimeb.time +
		(tp.millitm/1000.0) - (g_StartTimeb.millitm/1000.0);
#endif
}

string ProfileBuffer;

void ClearTextBuffer()
{
	ProfileBuffer.clear();
}
void PutTextBuffer(const char* c)
{
	ProfileBuffer += c;
}



void ProfileSaveBuffer( void )
{
	char temp[128];
	FILE* fp;	
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t,&now);

	sprintf_s(temp,128,"profile_%04d%02d%02d_%02d%02d%02d.txt",1900+t.tm_year,t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);
	fopen_s(&fp,temp,"w");
	fprintf(fp,"%s",ProfileBuffer.c_str());
	fclose(fp);
}


const char* ProfileGetBuffer( void )
{
	return ProfileBuffer.c_str();
}