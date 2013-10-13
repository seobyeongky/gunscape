//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.cpp
//
// 내용: 사운드- by audiere-1.9.4
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "sound.h"
#include <fstream>
using namespace std;

SOUNDMANAGER soundmanager;

SOUNDBUFFER* se_pistol=0;
SOUNDBUFFER* se_flame_thrower=0;
SOUNDBUFFER* se_bow=0;
SOUNDBUFFER* se_pistol_reload=0;
SOUNDBUFFER* se_flame_reload=0;
SOUNDBUFFER* se_shotgun_reload=0;
SOUNDBUFFER* se_backstab=0;
SOUNDBUFFER* se_knife=0;
SOUNDBUFFER* se_sniper=0;
SOUNDBUFFER* se_silencer=0;
SOUNDBUFFER* bgm_dungeon_0=0;
SOUNDBUFFER* bgm_dungeon_1=0;
SOUNDBUFFER* bgm_dungeon_2=0;
SOUNDBUFFER* bgm_dungeon_3=0;

//AudioDevicePtr DevicePtr = NULL;
//OutputStreamPtr se_pistol = NULL;
//OutputStreamPtr se_flame_thrower = NULL;
//OutputStreamPtr se_pistol_reload = NULL;
//OutputStreamPtr se_flame_reload = NULL;
//OutputStreamPtr bgm_dungeon_0 = NULL;
//
//void InitSound()
//{
//	DevicePtr = OpenDevice();
//	if ( !DevicePtr )
//		return;
//	se_pistol = OpenSound(DevicePtr, "sound\\총소리2.wav", false);
//	se_flame_thrower = OpenSound(DevicePtr, "sound\\fire.wav", false);
//	se_pistol_reload = OpenSound(DevicePtr, "sound\\총장전.wav", false);
//	se_flame_reload = OpenSound(DevicePtr, "sound\\fire_reload.wav", false);
//	bgm_dungeon_0 = OpenSound(DevicePtr, "sound\\bgm.mp3", true);
//	bgm_dungeon_0->setRepeat(true);
//}
//
//void PlaySE(OutputStreamPtr& sound_, bool init_)
//{
//	if(sound_)
//	{
//		if(init_)
//			sound_->setPosition(0);
//		sound_->play();
//	}
//}
//
//void PlayBGM(OutputStreamPtr& sound_)
//{
//	if(sound_)
//	{
//		sound_->play();
//	}
//}
//void StopBGM(OutputStreamPtr& sound_)
//{
//	if(sound_)
//	{
//		sound_->stop();
//	}
//}


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

	hmmio = mmioOpen(WaveFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

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
	se_sniper = new SOUNDBUFFER();
	se_silencer = new SOUNDBUFFER();
	bgm_dungeon_0 = new SOUNDBUFFER();
	bgm_dungeon_1 = new SOUNDBUFFER();
	bgm_dungeon_2 = new SOUNDBUFFER();
	bgm_dungeon_3 = new SOUNDBUFFER();
	bgm_on = true;
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
	delete se_sniper;
	delete se_silencer;
	delete bgm_dungeon_0;
	delete bgm_dungeon_1;
	delete bgm_dungeon_2;
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
	se_sniper -> Load(Sound, "sound\\se_sniper.wav", false, false, true);
	se_silencer -> Load(Sound, "sound\\se_silencer.wav", false, false, true);
	bgm_dungeon_0 -> Load(Sound, "sound\\bgm.wav", true, true, false);
	bgm_dungeon_1 -> Load(Sound, "sound\\bgm2.wav", true, true, false);
	bgm_dungeon_2 -> Load(Sound, "sound\\bgm3.wav", true, true, false);
	bgm_dungeon_3 -> Load(Sound, "sound\\bgm4.wav", true, true, false);

}

void SOUNDMANAGER :: Update()
{
	se_flame_thrower -> BufferUpdate();


	bgm_dungeon_0 -> BufferUpdate();
	bgm_dungeon_1 -> BufferUpdate();
	bgm_dungeon_2 -> BufferUpdate();
	bgm_dungeon_3 -> BufferUpdate();
}





void InitSound(HWND windowhandle_)
{
	soundmanager.Initialize(windowhandle_);
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
void PlayBGM(SOUNDBUFFER* sound_)
{
	if(sound_ && sound_->SoundBuffer && soundmanager.bgm_on)
	{
		sound_->PlaySound();
		sound_->play_time = 0;
	}
}
void StopBGM(SOUNDBUFFER* sound_)
{
	if(sound_ && sound_->SoundBuffer && soundmanager.bgm_on)
	{
		sound_->StopSound();
	}
}

void UpdateBGM()
{
	soundmanager.Update();
}