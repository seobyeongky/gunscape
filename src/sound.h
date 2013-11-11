//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.h
//
// 내용: 사운드- by audiere-1.9.4
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SOUND_H__
#define  __SOUND_H__

#include "coord_def.h"

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

	bool se_on;


	float BackgroundVolume;
	float VoiceVolume;
	float EffectVolume;

	SOUNDMANAGER();
	~SOUNDMANAGER();

	void Initialize(HWND WindowHandle);
	void Duplicate(SOUNDBUFFER **buffer_);
	void Update();

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
extern SOUNDBUFFER* se_silencer;
extern SOUNDBUFFER* se_ammo_pick;
extern SOUNDBUFFER* se_assknife;
extern SOUNDBUFFER* se_assknife_hit;
extern SOUNDBUFFER* se_asspistol;
extern SOUNDBUFFER* se_asspistol_reload;
extern SOUNDBUFFER* se_axe;
extern SOUNDBUFFER* se_axe_hit;
extern SOUNDBUFFER* se_bow2;
extern SOUNDBUFFER* se_bullet_flesh;
extern SOUNDBUFFER* se_club_hit;
extern SOUNDBUFFER* se_deagle_reload;
extern SOUNDBUFFER* se_doublepistol;
extern SOUNDBUFFER* se_fireball;
extern SOUNDBUFFER* se_gamestart;
extern SOUNDBUFFER* se_giant_dead;
extern SOUNDBUFFER* se_grenade_hit;
extern SOUNDBUFFER* se_grenadegun;
extern SOUNDBUFFER* se_hammer;
extern SOUNDBUFFER* se_hammer_hit;
extern SOUNDBUFFER* se_healthkit;
extern SOUNDBUFFER* se_human_dead;
extern SOUNDBUFFER* se_icegun_reload;
extern SOUNDBUFFER* se_knife_hit;
extern SOUNDBUFFER* se_monasspistol;
extern SOUNDBUFFER* se_monrifle;
extern SOUNDBUFFER* se_monsnipergun;
extern SOUNDBUFFER* se_portal;
extern SOUNDBUFFER* se_reload;
extern SOUNDBUFFER* se_rifle;
extern SOUNDBUFFER* se_rifle_reload;
extern SOUNDBUFFER* se_robot;
extern SOUNDBUFFER* se_rocket;
extern SOUNDBUFFER* se_rocket_reload;
extern SOUNDBUFFER* se_shout1;
extern SOUNDBUFFER* se_shout2;
extern SOUNDBUFFER* se_shout3;
extern SOUNDBUFFER* se_shout4;
extern SOUNDBUFFER* se_silencesnipergun;
extern SOUNDBUFFER* se_smoke;
extern SOUNDBUFFER* se_snipergun;
extern SOUNDBUFFER* se_snipergun_reload;
extern SOUNDBUFFER* se_snipermode;
extern SOUNDBUFFER* se_spear_hit;
extern SOUNDBUFFER* se_switch;
extern SOUNDBUFFER* se_zombie_dead1;
extern SOUNDBUFFER* se_zombie_dead2;
extern SOUNDBUFFER* se_minigun;
extern SOUNDBUFFER* se_monpistol;
extern SOUNDBUFFER* se_deagle;
extern SOUNDBUFFER* se_shotgun;
extern SOUNDBUFFER* se_shortshotgun;
extern SOUNDBUFFER* se_slashed1;
extern SOUNDBUFFER* se_slashed2;
extern SOUNDBUFFER* se_slashed3;
extern SOUNDBUFFER* se_slashed4;
extern SOUNDBUFFER* se_slashed5;
extern SOUNDBUFFER* se_slashed6;
extern SOUNDBUFFER* se_hello1;
extern SOUNDBUFFER* se_hello2;
extern SOUNDBUFFER* se_hello3;
extern SOUNDBUFFER* se_hello4;
extern SOUNDBUFFER* se_hello5;
extern SOUNDBUFFER* se_hello6;
extern SOUNDBUFFER* se_hello7;
extern SOUNDBUFFER* se_hello8;
extern SOUNDBUFFER* se_hello9;
extern SOUNDBUFFER* se_hello10;
extern SOUNDBUFFER* se_hello11;
extern SOUNDBUFFER* se_item1;
extern SOUNDBUFFER* se_item2;
extern SOUNDBUFFER* se_item3;
extern SOUNDBUFFER* se_pickup;


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

enum bgm_t
{
	BGM_MAIN,
	BGM_ZOMBIE,
	BGM_3,
	BGM_4,
	NR_BGM
};


void InitSound(HWND windowhandle_);

void PlaySE(SOUNDBUFFER* sound_, bool init_ = true);
void PlaySE2(SOUNDBUFFER* sound_1, SOUNDBUFFER* sound_2);
void PlaySE3(SOUNDBUFFER* sound_1, SOUNDBUFFER* sound_2, SOUNDBUFFER* sound_3);

void PlayBGM(bgm_t bgm_);
void StopBGM();

void UpdateBGM();

#endif // __SOUND_H__