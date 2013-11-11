//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.cpp
//
// 내용: 사운드- by audiere-1.9.4
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "sound.h"
#include <fstream>
#include <audiere.h>
using namespace std;

using namespace audiere;

SOUNDMANAGER soundmanager;

SOUNDBUFFER* se_pistol=0;
SOUNDBUFFER* se_flame_thrower=0;
SOUNDBUFFER* se_bow=0;
SOUNDBUFFER* se_pistol_reload=0;
SOUNDBUFFER* se_flame_reload=0;
SOUNDBUFFER* se_shotgun_reload=0;
SOUNDBUFFER* se_backstab=0;
SOUNDBUFFER* se_knife=0;
SOUNDBUFFER* se_silencer=0;
SOUNDBUFFER* se_ammo_pick=0;
SOUNDBUFFER* se_assknife=0;
SOUNDBUFFER* se_assknife_hit=0;
SOUNDBUFFER* se_asspistol=0;
SOUNDBUFFER* se_asspistol_reload=0;
SOUNDBUFFER* se_axe=0;
SOUNDBUFFER* se_axe_hit=0;
SOUNDBUFFER* se_bow2=0;
SOUNDBUFFER* se_bug_dead=0;
SOUNDBUFFER* se_bullet_flesh=0;
SOUNDBUFFER* se_club_hit=0;
SOUNDBUFFER* se_deagle_reload=0;
SOUNDBUFFER* se_doublepistol=0;
SOUNDBUFFER* se_fireball=0;
SOUNDBUFFER* se_gamestart=0;
SOUNDBUFFER* se_giant_dead=0;
SOUNDBUFFER* se_grenade_hit=0;
SOUNDBUFFER* se_grenadegun=0;
SOUNDBUFFER* se_hammer=0;
SOUNDBUFFER* se_hammer_hit=0;
SOUNDBUFFER* se_healthkit=0;
SOUNDBUFFER* se_human_dead=0;
SOUNDBUFFER* se_icegun_reload=0;
SOUNDBUFFER* se_knife_hit=0;
SOUNDBUFFER* se_monasspistol=0;
SOUNDBUFFER* se_monrifle=0;
SOUNDBUFFER* se_monsnipergun=0;
SOUNDBUFFER* se_portal=0;
SOUNDBUFFER* se_reload=0;
SOUNDBUFFER* se_rifle=0;
SOUNDBUFFER* se_rifle_reload=0;
SOUNDBUFFER* se_robot=0;
SOUNDBUFFER* se_rocket=0;
SOUNDBUFFER* se_rocket_reload=0;
SOUNDBUFFER* se_shout1=0;
SOUNDBUFFER* se_shout2=0;
SOUNDBUFFER* se_shout3=0;
SOUNDBUFFER* se_shout4=0;
SOUNDBUFFER* se_silencesnipergun=0;
SOUNDBUFFER* se_smoke=0;
SOUNDBUFFER* se_snipergun=0;
SOUNDBUFFER* se_snipergun_reload=0;
SOUNDBUFFER* se_snipermode=0;
SOUNDBUFFER* se_spear_hit=0;
SOUNDBUFFER* se_switch=0;
SOUNDBUFFER* se_zombie_dead1=0;
SOUNDBUFFER* se_zombie_dead2=0;
SOUNDBUFFER* se_minigun=0;
SOUNDBUFFER* se_monpistol=0;
SOUNDBUFFER* se_deagle=0;
SOUNDBUFFER* se_shotgun=0;
SOUNDBUFFER* se_shortshotgun=0;
SOUNDBUFFER* se_slashed1;
SOUNDBUFFER* se_slashed2;
SOUNDBUFFER* se_slashed3;
SOUNDBUFFER* se_slashed4;
SOUNDBUFFER* se_slashed5;
SOUNDBUFFER* se_slashed6;
SOUNDBUFFER* se_hello1;
SOUNDBUFFER* se_hello2;
SOUNDBUFFER* se_hello3;
SOUNDBUFFER* se_hello4;
SOUNDBUFFER* se_hello5;
SOUNDBUFFER* se_hello6;
SOUNDBUFFER* se_hello7;
SOUNDBUFFER* se_hello8;
SOUNDBUFFER* se_hello9;
SOUNDBUFFER* se_hello10;
SOUNDBUFFER* se_hello11;
SOUNDBUFFER* se_item1;
SOUNDBUFFER* se_item2;
SOUNDBUFFER* se_item3;
SOUNDBUFFER* se_pickup;


struct bgm_context_t
{
	AudioDevicePtr DevicePtr;
	OutputStreamPtr bgms[NR_BGM];
};

bgm_context_t * bc = nullptr;


SOUNDBUFFER :: SOUNDBUFFER()
{
	SoundBuffer = NULL;
	for(int i = 0; i< SOUND_BUFFER_MAX;i++)
		PlusBuffer[i] = NULL;
	IsPlaying = false;
	IsLooping = false;
	IsStreaming = false;
	IsOverlab = false;
	Volume = 100;
	stream_limit = 0;
	play_time = 0;

	hmmio = NULL;
	WaveSize = 0;
	BufferSize = 0;
	DataStart = 0;
	DataCursor = 0;
	BytesRead = 0;
}

SOUNDBUFFER :: ~SOUNDBUFFER()
{
	if(SoundBuffer != NULL)
	{
		SoundBuffer -> Release();
		SoundBuffer = NULL;
	}
	for(int i = 0; i< SOUND_BUFFER_MAX;i++)
	{		
		if(PlusBuffer[i] != NULL)
		{
			PlusBuffer[i] -> Release();
			PlusBuffer[i] = NULL;
		}
	}

	if(hmmio != NULL)
	{
		mmioClose(hmmio, 0);
		hmmio = NULL;
	}
}
void SOUNDBUFFER :: Load(IDirectSound8* Sound, char* WaveFileName, bool Streaming, bool Looping, bool overlab)
{ 
	ifstream infile;
	infile.open(WaveFileName);
	if(infile.fail())
	{
		return;
	}
	infile.close();

	hmmio = mmioOpenA(WaveFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

	MMCKINFO ckRIFF;
	ZeroMemory(&ckRIFF, sizeof(MMCKINFO));
	ckRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	MMRESULT a = mmioDescend(hmmio, &ckRIFF, NULL, MMIO_FINDRIFF);


	MMCKINFO ckChunk;
	ZeroMemory(&ckChunk, sizeof(MMCKINFO));
	ckChunk.fccType = mmioFOURCC('f', 'm', 't', ' ');
	MMRESULT b = mmioDescend(hmmio, &ckChunk, &ckRIFF, MMIO_FINDCHUNK);


	WAVEFORMATEX WaveFormat;
	ZeroMemory(&WaveFormat, sizeof(WAVEFORMATEX));
	MMRESULT c = mmioRead(hmmio, (char*)&WaveFormat, sizeof(WAVEFORMATEX));

	mmioAscend(hmmio, &ckChunk, 0);
	ckChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	MMRESULT d = mmioDescend(hmmio, &ckChunk, &ckRIFF, MMIO_FINDCHUNK);

	if(Streaming == true)
	{
		WaveSize = ckChunk.cksize;
		BufferSize = WaveFormat.nAvgBytesPerSec;
	}
	else
	{
		WaveSize = ckChunk.cksize;
		BufferSize = ckChunk.cksize;
	}
	DataStart = mmioSeek(hmmio, 0, SEEK_CUR);

	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(DSBUFFERDESC));

	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2;
	desc.lpwfxFormat = &WaveFormat;
	desc.dwBufferBytes = BufferSize;

	IDirectSoundBuffer* tempSoundBuffer;
	
	Sound -> CreateSoundBuffer(&desc, &tempSoundBuffer, NULL);
	tempSoundBuffer -> QueryInterface(IID_IDirectSoundBuffer8, (void**)&SoundBuffer);
	tempSoundBuffer -> Release();

	void* Ptr;
	DWORD Bytes;

	SoundBuffer -> Lock(0, 0, &Ptr, &Bytes, NULL, NULL, DSBLOCK_ENTIREBUFFER);
	mmioRead(hmmio, (char*)Ptr, Bytes);
	SoundBuffer -> Unlock(Ptr, Bytes, NULL, NULL);

	DataCursor += Bytes;
	BytesRead += Bytes;

	IsLooping = Looping;
	IsStreaming = Streaming;
	IsOverlab = overlab;

	if(overlab){
		for(int i = 1; i< SOUND_BUFFER_MAX; i++){			
			Sound->DuplicateSoundBuffer(SoundBuffer, &PlusBuffer[i]);
		}
	}
}

void SOUNDBUFFER :: Unload()
{
	if(SoundBuffer != NULL)
	{
		SoundBuffer -> Release();
		SoundBuffer = NULL;
	}
	for(int i = 0; i< SOUND_BUFFER_MAX;i++)
	{		
		if(PlusBuffer[i] != NULL)
		{
			PlusBuffer[i] -> Release();
			PlusBuffer[i] = NULL;
		}
	}
	IsPlaying = false;

	if(hmmio != NULL)
	{
		mmioClose(hmmio, 0);
		hmmio = NULL;
	}

	WaveSize = 0;
	BufferSize = 0;
	DataStart = 0;
	DataCursor = 0;
	BytesRead = 0;
}

void SOUNDBUFFER :: BufferUpdate()
{
	if(!SoundBuffer)
		return; 

	if(IsPlaying)
	{
		play_time++;
		if(stream_limit && play_time>stream_limit)
		{
			play_time=0;
			IsPlaying = false;
		}
	}

	if(IsPlaying)
	{
		if(IsStreaming)
		{
			DWORD CurrentPlayCursor;
			SoundBuffer -> GetCurrentPosition(&CurrentPlayCursor, NULL);

			DWORD DataToCopy;
			if(DataCursor < CurrentPlayCursor)
				DataToCopy = CurrentPlayCursor - DataCursor;
			else
				DataToCopy = BufferSize - DataCursor + CurrentPlayCursor;

			void* Ptr1;
			DWORD Bytes1;
			void* Ptr2;
			DWORD Bytes2;

			SoundBuffer -> Lock(DataCursor, DataToCopy, &Ptr1, &Bytes1, &Ptr2, &Bytes2, 0);
			BytesRead += Bytes1 + Bytes2;
			if(BytesRead > WaveSize)
			{
				BytesRead = 0;
				mmioSeek(hmmio, DataStart, SEEK_SET);
				memset(Ptr1, 0x00, Bytes1);
				if(Ptr2 != NULL)
					memset(Ptr2, 0x00, Bytes2);

				if(IsLooping == false)
					StopSound();
			}
			else
			{
				mmioRead(hmmio, (char*)Ptr1, Bytes1);
				if(Ptr2 != NULL)
					mmioRead(hmmio, (char*)Ptr2, Bytes2);
			}
			SoundBuffer -> Unlock(Ptr1, Bytes1, Ptr2, Bytes2);

			DataCursor += Bytes1 + Bytes2;
			DataCursor %= BufferSize;
		}
	}
	else
	{
		IsPlaying = true;
		StopSound();
	}

}

void SOUNDBUFFER :: PlaySound()
{
	if(!SoundBuffer)
		return; 

	IsPlaying = true;
	if(IsOverlab){
		DWORD state = 0;

		SoundBuffer->GetStatus(&state);
		if(state == DSBSTATUS_PLAYING)
		{
			for(int i = 1; i< SOUND_BUFFER_MAX; i++){
				PlusBuffer[i]->GetStatus(&state);
				if(state == DSBSTATUS_PLAYING)
					continue;

				if(IsLooping)
					PlusBuffer[i] -> Play(0, 0, DSBPLAY_LOOPING);
				else
					PlusBuffer[i] -> Play(0, 0, 0);
				break;

			}
			return;
		}
	}
	
	{		
		if(IsLooping)
			SoundBuffer -> Play(0, 0, DSBPLAY_LOOPING);
		else
			SoundBuffer -> Play(0, 0, 0);
	}
}

void SOUNDBUFFER :: StopSound()
{
	if(!SoundBuffer)
		return; 


	if(IsStreaming)
	{
		DWORD state = 0;
		SoundBuffer->GetStatus(&state);
		if(!IsPlaying)
			return;

		void* Ptr1;
		DWORD Bytes1;
		void* Ptr2;
		DWORD Bytes2;

		SoundBuffer -> Lock(0, 0, &Ptr1, &Bytes1, &Ptr2, &Bytes2, DSBLOCK_ENTIREBUFFER);

		BytesRead = 0;
		mmioSeek(hmmio, DataStart, SEEK_SET);
		memset(Ptr1, 0x00, Bytes1);
		if(Ptr2 != NULL)
			memset(Ptr2, 0x00, Bytes2);

		SoundBuffer -> Unlock(Ptr1, Bytes1, Ptr2, Bytes2);

		DataCursor += Bytes1 + Bytes2;
		DataCursor %= BufferSize;
	}
	
	IsPlaying = false;
	SoundBuffer -> SetCurrentPosition(0);
	SoundBuffer -> Stop();
	if(IsOverlab){
		for(int i = 1; i< SOUND_BUFFER_MAX; i++){
			PlusBuffer[i] -> Stop();
			PlusBuffer[i] -> SetCurrentPosition(0);
		}
	}
}

void SOUNDBUFFER :: SetVolume()
{
	if(!SoundBuffer)
		return; 

	if(Volume == 0)
		SoundBuffer -> SetVolume(-10000);
	else
		SoundBuffer -> SetVolume((long)((log10((float)Volume) - 2.0f) * 5000.0f));
}




SOUNDMANAGER :: SOUNDMANAGER()
{
	Sound = NULL;

	se_pistol = new SOUNDBUFFER();
	se_flame_thrower = new SOUNDBUFFER();
	se_bow = new SOUNDBUFFER(); 
	se_pistol_reload = new SOUNDBUFFER();
	se_flame_reload = new SOUNDBUFFER();
	se_shotgun_reload = new SOUNDBUFFER();
	se_backstab = new SOUNDBUFFER();
	se_knife = new SOUNDBUFFER();
	se_silencer = new SOUNDBUFFER();
	se_ammo_pick = new SOUNDBUFFER();
	se_assknife=new SOUNDBUFFER();
	se_assknife_hit=new SOUNDBUFFER();
	se_asspistol=new SOUNDBUFFER();
	se_asspistol_reload=new SOUNDBUFFER();
	se_axe=new SOUNDBUFFER();
	se_axe_hit=new SOUNDBUFFER();
	se_bow2=new SOUNDBUFFER();
	se_bug_dead=new SOUNDBUFFER();
	se_bullet_flesh=new SOUNDBUFFER();
	se_club_hit=new SOUNDBUFFER();
	se_deagle_reload=new SOUNDBUFFER();
	se_doublepistol=new SOUNDBUFFER();
	se_fireball=new SOUNDBUFFER();
	se_gamestart=new SOUNDBUFFER();
	se_giant_dead=new SOUNDBUFFER();
	se_grenade_hit=new SOUNDBUFFER();
	se_grenadegun=new SOUNDBUFFER();
	se_hammer=new SOUNDBUFFER();
	se_hammer_hit=new SOUNDBUFFER();
	se_healthkit=new SOUNDBUFFER();
	se_human_dead=new SOUNDBUFFER();
	se_icegun_reload=new SOUNDBUFFER();
	se_knife_hit=new SOUNDBUFFER();
	se_monasspistol=new SOUNDBUFFER();
	se_monrifle=new SOUNDBUFFER();
	se_monsnipergun=new SOUNDBUFFER();
	se_portal=new SOUNDBUFFER();
	se_reload=new SOUNDBUFFER();
	se_rifle=new SOUNDBUFFER();
	se_rifle_reload=new SOUNDBUFFER();
	se_robot=new SOUNDBUFFER();
	se_rocket=new SOUNDBUFFER();
	se_rocket_reload=new SOUNDBUFFER();
	se_shout1=new SOUNDBUFFER();
	se_shout2=new SOUNDBUFFER();
	se_shout3=new SOUNDBUFFER();
	se_shout4=new SOUNDBUFFER();
	se_silencesnipergun=new SOUNDBUFFER();
	se_smoke=new SOUNDBUFFER();
	se_snipergun=new SOUNDBUFFER();
	se_snipergun_reload=new SOUNDBUFFER();
	se_snipermode=new SOUNDBUFFER();
	se_spear_hit=new SOUNDBUFFER();
	se_switch=new SOUNDBUFFER();
	se_zombie_dead1=new SOUNDBUFFER();
	se_zombie_dead2=new SOUNDBUFFER();
	se_minigun=new SOUNDBUFFER();
	se_monpistol=new SOUNDBUFFER();
	se_deagle=new SOUNDBUFFER();
	se_shotgun=new SOUNDBUFFER();
	se_shortshotgun=new SOUNDBUFFER();
	se_slashed1=new SOUNDBUFFER();
	se_slashed2=new SOUNDBUFFER();
	se_slashed3=new SOUNDBUFFER();
	se_slashed4=new SOUNDBUFFER();
	se_slashed5=new SOUNDBUFFER();
	se_slashed6=new SOUNDBUFFER();
	se_hello1=new SOUNDBUFFER();
	se_hello2=new SOUNDBUFFER();
	se_hello3=new SOUNDBUFFER();
	se_hello4=new SOUNDBUFFER();
	se_hello5=new SOUNDBUFFER();
	se_hello6=new SOUNDBUFFER();
	se_hello7=new SOUNDBUFFER();
	se_hello8=new SOUNDBUFFER();
	se_hello9=new SOUNDBUFFER();
	se_hello10=new SOUNDBUFFER();
	se_hello11=new SOUNDBUFFER();
	se_item1=new SOUNDBUFFER();
	se_item2=new SOUNDBUFFER();
	se_item3=new SOUNDBUFFER();
	se_pickup=new SOUNDBUFFER();

	se_on = true;
	BackgroundVolume = 0.0f;
	VoiceVolume = 0.0f;
	EffectVolume = 0.0f;
}

SOUNDMANAGER :: ~SOUNDMANAGER()
{
	delete se_pistol;
	delete se_flame_thrower;
	delete se_bow;
	delete se_pistol_reload;
	delete se_flame_reload;
	delete se_shotgun_reload;
	delete se_backstab;
	delete se_knife;
	delete se_silencer;
	delete se_ammo_pick;
	delete se_assknife;
	delete se_assknife_hit;
	delete se_asspistol;
	delete se_asspistol_reload;
	delete se_axe;
	delete se_axe_hit;
	delete se_bow2;
	delete se_bug_dead;
	delete se_bullet_flesh;
	delete se_club_hit;
	delete se_deagle_reload;
	delete se_doublepistol;
	delete se_fireball;
	delete se_gamestart;
	delete se_giant_dead;
	delete se_grenade_hit;
	delete se_grenadegun;
	delete se_hammer;
	delete se_hammer_hit;
	delete se_healthkit;
	delete se_human_dead;
	delete se_icegun_reload;
	delete se_knife_hit;
	delete se_monasspistol;
	delete se_monrifle;
	delete se_monsnipergun;
	delete se_portal;
	delete se_reload;
	delete se_rifle;
	delete se_rifle_reload;
	delete se_robot;
	delete se_rocket;
	delete se_rocket_reload;
	delete se_shout1;
	delete se_shout2;
	delete se_shout3;
	delete se_shout4;
	delete se_silencesnipergun;
	delete se_smoke;
	delete se_snipergun;
	delete se_snipergun_reload;
	delete se_snipermode;
	delete se_spear_hit;
	delete se_switch;
	delete se_zombie_dead1;
	delete se_zombie_dead2;
	delete se_minigun;
	delete se_monpistol;
	delete se_deagle;
	delete se_shotgun;
	delete se_shortshotgun;
	delete se_slashed1;
	delete se_slashed2;
	delete se_slashed3;
	delete se_slashed4;
	delete se_slashed5;
	delete se_slashed6;
	delete se_hello1;
	delete se_hello2;
	delete se_hello3;
	delete se_hello4;
	delete se_hello5;
	delete se_hello6;
	delete se_hello7;
	delete se_hello8;
	delete se_hello9;
	delete se_hello10;
	delete se_hello11;
	delete se_item1;
	delete se_item2;
	delete se_item3;
	delete se_pickup;

	if(Sound != NULL)
	{
		Sound -> Release();
		Sound = NULL;
	}
}

void SOUNDMANAGER :: Initialize(HWND WindowHandle)
{
	DirectSoundCreate8(NULL, &Sound, NULL);

	Sound -> SetCooperativeLevel(WindowHandle, DSSCL_PRIORITY);
	se_pistol -> Load(Sound, "sound\\se_pistol.wav", false, false, true);	
	se_flame_thrower -> Load(Sound, "sound\\se_flame_thrower.wav", true, true, false);
	se_bow -> Load(Sound, "sound\\se_bow.wav", false, false, true);
	se_flame_thrower -> stream_limit = 10;
	se_pistol_reload -> Load(Sound, "sound\\se_pistol_reload.wav", false, false, false);
	se_flame_reload -> Load(Sound, "sound\\se_flame_reload.wav", false, false, false);
	se_shotgun_reload -> Load(Sound, "sound\\se_shotgun_reload.wav", false, false, false);
	se_backstab -> Load(Sound, "sound\\se_backstab.wav", false, false, true);
	se_knife -> Load(Sound, "sound\\se_knife.wav", false, false, true);
	se_silencer -> Load(Sound, "sound\\se_silencer.wav", false, false, true);
	se_ammo_pick -> Load(Sound, "sound\\se_ammo_pick.wav", false, false, true);
	se_assknife -> Load(Sound, "sound\\se_assknife.wav", false, false, true);
	se_assknife_hit -> Load(Sound, "sound\\se_assknife_hit.wav", false, false, true);
	se_asspistol -> Load(Sound, "sound\\se_asspistol.wav", false, false, true);
	se_asspistol_reload -> Load(Sound, "sound\\se_asspistol_reload.wav", false, false, true);
	se_axe -> Load(Sound, "sound\\se_axe.wav", false, false, true);
	se_axe_hit -> Load(Sound, "sound\\se_axe_hit.wav", false, false, true);
	se_bow2 -> Load(Sound, "sound\\se_bow2.wav", false, false, true);
	se_bug_dead -> Load(Sound, "sound\\se_bug_dead.wav", false, false, true);
	se_bullet_flesh -> Load(Sound, "sound\\se_bullet_flesh.wav", false, false, true);
	se_club_hit -> Load(Sound, "sound\\se_club_hit.wav", false, false, true);
	se_deagle_reload -> Load(Sound, "sound\\se_deagle_reload.wav", false, false, true);
	se_doublepistol -> Load(Sound, "sound\\se_doublepistol.wav", false, false, true);
	se_fireball -> Load(Sound, "sound\\se_fireball.wav", false, false, true);
	se_gamestart -> Load(Sound, "sound\\se_gamestart.wav", false, false, true);
	se_giant_dead -> Load(Sound, "sound\\se_giant_dead.wav", false, false, true);
	se_grenade_hit -> Load(Sound, "sound\\se_grenade_hit.wav", false, false, true);
	se_grenadegun -> Load(Sound, "sound\\se_grenadegun.wav", false, false, true);
	se_hammer -> Load(Sound, "sound\\se_hammer.wav", false, false, true);
	se_hammer_hit -> Load(Sound, "sound\\se_hammer_hit.wav", false, false, true);
	se_healthkit -> Load(Sound, "sound\\se_healthkit.wav", false, false, true);
	se_human_dead -> Load(Sound, "sound\\se_human_dead.wav", false, false, true);
	se_icegun_reload -> Load(Sound, "sound\\se_icegun_reload.wav", false, false, true);
	se_knife_hit -> Load(Sound, "sound\\se_knife_hit.wav", false, false, true);
	se_monasspistol -> Load(Sound, "sound\\se_monasspistol.wav", false, false, true);
	se_monrifle -> Load(Sound, "sound\\se_monrifle.wav", false, false, true);
	se_monsnipergun -> Load(Sound, "sound\\se_monsnipergun.wav", false, false, true);
	se_portal -> Load(Sound, "sound\\se_portal.wav", false, false, true);
	se_reload -> Load(Sound, "sound\\se_reload.wav", false, false, true);
	se_rifle -> Load(Sound, "sound\\se_rifle.wav", false, false, true);
	se_rifle_reload -> Load(Sound, "sound\\se_rifle_reload.wav", false, false, true);
	se_robot -> Load(Sound, "sound\\se_robot.wav", false, false, true);
	se_rocket -> Load(Sound, "sound\\se_rocket.wav", false, false, true);
	se_rocket_reload -> Load(Sound, "sound\\se_rocket_reload.wav", false, false, true);
	se_shout1 -> Load(Sound, "sound\\se_shout1.wav", false, false, true);
	se_shout2 -> Load(Sound, "sound\\se_shout2.wav", false, false, true);
	se_shout3 -> Load(Sound, "sound\\se_shout3.wav", false, false, true);
	se_shout4 -> Load(Sound, "sound\\se_shout4.wav", false, false, true);
	se_silencesnipergun -> Load(Sound, "sound\\se_silencesnipergun.wav", false, false, true);
	se_smoke -> Load(Sound, "sound\\se_smoke.wav", false, false, true);
	se_snipergun -> Load(Sound, "sound\\se_snipergun.wav", false, false, true);
	se_snipergun_reload -> Load(Sound, "sound\\se_snipergun_reload.wav", false, false, true);
	se_snipermode -> Load(Sound, "sound\\se_snipermode.wav", false, false, true);
	se_spear_hit -> Load(Sound, "sound\\se_spear_hit.wav", false, false, true);
	se_switch -> Load(Sound, "sound\\se_switch.wav", false, false, true);
	se_zombie_dead1 -> Load(Sound, "sound\\se_zombie_dead1.wav", false, false, true);
	se_zombie_dead2 -> Load(Sound, "sound\\se_zombie_dead2.wav", false, false, true);
	se_minigun -> Load(Sound, "sound\\se_minigun.wav", false, false, true);
	se_monpistol-> Load(Sound, "sound\\se_monpistol.wav", false, false, true);
	se_deagle -> Load(Sound, "sound\\se_deagle.wav", false, false, true);
	se_shotgun -> Load(Sound, "sound\\se_shotgun.wav", false, false, true);
	se_shortshotgun -> Load(Sound, "sound\\se_shortshotgun.wav", false, false, true);
	se_slashed1 -> Load(Sound, "sound\\se_slashed1.wav", false, false, true);
	se_slashed2 -> Load(Sound, "sound\\se_slashed2.wav", false, false, true);
	se_slashed3 -> Load(Sound, "sound\\se_slashed3.wav", false, false, true);
	se_slashed4 -> Load(Sound, "sound\\se_slashed4.wav", false, false, true);
	se_slashed5 -> Load(Sound, "sound\\se_slashed5.wav", false, false, true);
	se_slashed6 -> Load(Sound, "sound\\se_slashed6.wav", false, false, true);
	se_hello1 -> Load(Sound, "sound\\se_hello1.wav", false, false, true);
	se_hello2 -> Load(Sound, "sound\\se_hello2.wav", false, false, true);
	se_hello3 -> Load(Sound, "sound\\se_hello3.wav", false, false, true);
	se_hello4 -> Load(Sound, "sound\\se_hello4.wav", false, false, true);
	se_hello5 -> Load(Sound, "sound\\se_hello5.wav", false, false, true);
	se_hello6 -> Load(Sound, "sound\\se_hello6.wav", false, false, true);
	se_hello7 -> Load(Sound, "sound\\se_hello7.wav", false, false, true);
	se_hello8 -> Load(Sound, "sound\\se_hello8.wav", false, false, true);
	se_hello9 -> Load(Sound, "sound\\se_hello9.wav", false, false, true);
	se_hello10 -> Load(Sound, "sound\\se_hello10.wav", false, false, true);
	se_hello11 -> Load(Sound, "sound\\se_hello11.wav", false, false, true);
	se_item1 -> Load(Sound, "sound\\item1.wav", false, false, true);
	se_item2 -> Load(Sound, "sound\\item2.wav", false, false, true);
	se_item3 -> Load(Sound, "sound\\item3.wav", false, false, true);
	se_pickup -> Load(Sound, "sound\\pickup.wav", false, false, true);
}

void SOUNDMANAGER :: Update()
{
	se_flame_thrower -> BufferUpdate();
}





void InitSound(HWND windowhandle_)
{
	soundmanager.Initialize(windowhandle_);

	// 메모리 셈 그래도 괜챃...?
	bc = new bgm_context_t();

	bc->DevicePtr = OpenDevice();

	auto addbgm = [](bgm_t key, const string & filename){
		bc->bgms[key] = OpenSound(bc->DevicePtr, string("sound\\" + filename).c_str(), true);
	};
	
	addbgm(BGM_MAIN, "bgm.ogg");
	addbgm(BGM_ZOMBIE, "bgm2.ogg");
	addbgm(BGM_3, "bgm3.ogg");
	addbgm(BGM_4, "bgm4.mp3");

	for (auto stream : bc->bgms)
	{
		if (stream)
		{
			stream->setRepeat(true);
		}
	}
}

void PlaySE(SOUNDBUFFER* sound_, bool init_)
{
	if(sound_ && soundmanager.se_on)
	{
		//if(init_)
		//	sound_->StopSound();
		sound_->PlaySound();
		sound_->play_time = 0;
	}
}

#include "random.h"

void PlaySE2(SOUNDBUFFER* sound_1, SOUNDBUFFER* sound_2)
{
	int r = my_rand_int(0, 100);
	if (r < 50)
		PlaySE(sound_1, false);
	else
		PlaySE(sound_2, false);
}

void PlaySE3(SOUNDBUFFER* sound_1, SOUNDBUFFER* sound_2, SOUNDBUFFER* sound_3)
{
	int r = my_rand_int(0, 100);
	if (r < 33)
		PlaySE(sound_1, false);
	else if (r < 67)
		PlaySE(sound_2, false);
	else
		PlaySE(sound_3, false);
}

void PlayBGM(bgm_t bgm_)
{
	auto stream = bc->bgms[bgm_];
	if (stream)
	{
		stream->play();
	}
}
void StopBGM()
{
	for (auto stream : bc->bgms)
	{
		if (stream)
		{
			stream->stop();
		}
	}
}

void UpdateBGM()
{
	soundmanager.Update();
}