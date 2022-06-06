#include "IMusic.h"

IMusic::IMusic(std::string szFilename)
{
	music=Mix_LoadMUS(szFilename.c_str());
}

IMusic::~IMusic()
{
	Mix_FreeMusic(music);
	music=NULL;
}

void IMusic::Load(std::string szFilename)
{
	music=Mix_LoadMUS(szFilename.c_str());
}

void IMusic::Play(int iStyle, int iLoop, int iMs)
{
	if (iStyle)
	{
		Mix_FadeInMusic(music, iLoop, iMs);
	}
	else
	{
		Mix_PlayMusic(music, iLoop);
	}
}

void IMusic::Pause()
{
	Mix_PauseMusic();
}

void IMusic::Resume()
{
	Mix_ResumeMusic();
}

void IMusic::Stop(int iStyle, int iMs)
{
	if (iStyle)
	{
		Mix_FadeOutMusic(iMs);
	}
	else
	{
		Mix_HaltMusic();
	}
}

void IMusic::Rewind()
{
	Mix_RewindMusic();
}

void IMusic::SetPosition(double dPos)
{
	Mix_SetMusicPosition(dPos);
}

void IMusic::SetVolume(int iVol)
{
	Mix_VolumeMusic(iVol);
}

int IMusic::IsPlaying()
{
	return Mix_PlayingMusic();
}

int IMusic::IsPaused()
{
	return Mix_PausedMusic();
}


// Sample

ISample::ISample(std::string szFilename)
{
	sample=Mix_LoadWAV(szFilename.c_str());
}

ISample::~ISample()
{
	Mix_FreeChunk(sample);
	sample=NULL;
}

void ISample::Load(std::string szFilename)
{
	sample=Mix_LoadWAV(szFilename.c_str());
}

void ISample::Play(int iStyle, int iLoop, int iMs)
{
	if (iStyle)
	{
		Mix_FadeInChannel(-1, sample, iLoop, iMs);
	}
	else
	{
		Mix_PlayChannel(-1, sample, iLoop);
	}
}

void ISample::Pause()
{
	Mix_Pause(-1);
}

void ISample::Resume()
{
	Mix_Resume(-1);
}

void ISample::Stop(int iStyle, int iMs)
{
	if (iStyle)
	{
		Mix_FadeOutChannel(-1, iMs);
	}
	else
	{
		Mix_HaltChannel(-1);
	}
}

void ISample::SetVolume(int iVol)
{
	Mix_Volume(-1, iVol);
}

int ISample::IsPlaying()
{
	return Mix_Playing(-1);
}

int ISample::IsPaused()
{
	return Mix_Paused(-1);
}
