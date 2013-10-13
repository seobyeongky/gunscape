//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.h
//
// 내용: 사운드- by audiere-1.9.4
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SOUND_H__
#define  __SOUND_H__

#include <dsound.h>
#include <math.h>
#pragma comment (lib, "dsound")

enum
{
	SOUND_BUFFER_MAX = 20
};



class SOUNDBUFFER
{
public:
	IDirectSoundBuffer8* SoundBuffer;
	IDirectSoundBuffer* PlusBuffer[SOUND_BUFFER_MAX];
	bool IsPlaying;
	bool IsLooping;
	bool IsStreaming;
	bool IsOverlab;
	long Volume;
	int stream_limit; //자동으로 곡이 끊기는 시간
	int play_time; //플레이 함수로 플레이후 지난시간

	SOUNDBUFFER();
	~SOUNDBUFFER();

	void Load(IDirectSound8* Sound, char* WaveFileName, bool Streaming, bool Looping, bool overlab);
	void Unload();
	void BufferUpdate();
	void PlaySound();
	void StopSound();
	void SetVolume();

private:
	HMMIO hmmio;
	DWORD WaveSize;
	DWORD BufferSize;
	DWORD DataStart;
	DWORD DataCursor;
	DWORD BytesRead;
};


class SOUNDMANAGER
{
public:
	IDirectSound8* Sound;

	bool bgm_on;
	bool se_on;


	float BackgroundVolume;
	float VoiceVolume;
	float EffectVolume;

	SOUNDMANAGER();
	~SOUNDMANAGER();

	void Initialize(HWND WindowHandle);
	void Duplicate(SOUNDBUFFER **buffer_);
	void Update();

	void SetBgmOn(bool on_){bgm_on = on_;};
	void SetBgmOnOff(){bgm_on = !bgm_on;};
	void SetSeOn(bool on_){se_on = on_;};
	void SetSeOnOff(){se_on = !se_on;};
};

//
extern SOUNDMANAGER soundmanager;

extern SOUNDBUFFER* se_pistol;
extern SOUNDBUFFER* se_flame_thrower;
extern SOUNDBUFFER* se_pistol_reload;
extern SOUNDBUFFER* se_shotgun_reload;
extern SOUNDBUFFER* se_bow;
extern SOUNDBUFFER* se_flame_reload;
extern SOUNDBUFFER* se_backstab;
extern SOUNDBUFFER* se_knife;
extern SOUNDBUFFER* se_sniper;
extern SOUNDBUFFER* se_silencer;
extern SOUNDBUFFER* bgm_dungeon_0;
extern SOUNDBUFFER* bgm_dungeon_1;
extern SOUNDBUFFER* bgm_dungeon_2;
extern SOUNDBUFFER* bgm_dungeon_3;


//#include <audiere.h>
//using namespace audiere;
//
//extern OutputStreamPtr se_pistol;
//extern OutputStreamPtr se_flame_thrower;
//extern OutputStreamPtr se_pistol_reload;
//extern OutputStreamPtr se_flame_reload;
//extern OutputStreamPtr bgm_dungeon_0;
//
//void InitSound();
//
//void PlaySE(OutputStreamPtr& sound_, bool init_ = true);
//
//void PlayBGM(OutputStreamPtr& sound_);
//void StopBGM(OutputStreamPtr& sound_);




void InitSound(HWND windowhandle_);

void PlaySE(SOUNDBUFFER* sound_, bool init_ = true);
void PlayBGM(SOUNDBUFFER* sound_);
void StopBGM(SOUNDBUFFER* sound_);

void UpdateBGM();

#endif // __SOUND_H__