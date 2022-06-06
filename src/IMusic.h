/*
Ses ve Müzik sýnýfý:

þimdi burda iki sýnýf var Music müzik ve Sample ise
ses efektleri için (ciyuv ciyuvlar var ya onlar) 
kullanýlacak. Kullanýlmadan önce IWindow'dan InitMusic
ile ses sistemi init edilmeli.

IMusic:

construct: yüklenecek dosyanýn adý girilir. 

play: style 0 iken direk çalar 1 olduðunda fade in ile girer.
loop -1 iken sonsuza dek tekrar eder, ms ise fadein in milisaniye
cinsinden süresidir.

pause: þarkýyý duraklatýr.

resume: þarkýnýn kaldýðý yerden devam etmesini saðlar. þarký 
pause durumunda deðilken çalýþtýrýlmasý sorun olmaz.

stop: style 0 iken direk durur, 1 iken fade out ile ve 
ms ise fade out'un milisaniye cinsinden süresidir.

rewind: þarkýyý baþa sarar.

setposition: mod, ogg ve mp3'lerde çalýþýr. mod'ta uint16'ya
çevrilip pattern nosuna atlamasýný saðlar. diðerlerinde þarkýnýn
o saniyesine atlamayý saðlar.

setvolume: ses deðerini ayarlar. 0 - 128 arasýdýr. min ve max
deðerleri aþmaz.

isplaying: çalýyorsa 1 döndürür, yoksa 0.

ispaused: duraklatýlmýþsa 1 döndürür, yoksa 0.

ISample: 

construct: sadece yüklenecek dosyanýn adý girilir.

play: ayný ama tek fark imusic'te loop default olarak -1
iken burada 1.

pause: ayný

resume: ayný

stop: ayný

setvolume: ayný

isplaying: ayný

ispaused: ayný

*/

#ifndef IMUSIC_H
#define IMUSIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string>

class IMusic
{
public:
	IMusic() { };
	IMusic(std::string szFilename);
	~IMusic(void);

	Mix_Music *music;
	
	void Load(std::string szFilename);
	void Play(int iStyle=0, int iLoop=-1, int iMs=2000);
	void Pause(void);
	void Resume(void);
	void Stop(int iStyle=0, int iMs=2000);
	void Rewind(void);
	void SetPosition(double dPos);
	void SetVolume(int iVol);
	int IsPlaying(void);
	int IsPaused(void);

};

class ISample
{
public:
        ISample() { };
	ISample(std::string szFilename);
	~ISample(void);

	Mix_Chunk *sample;

	void Load(std::string szFilename);
	void Play(int iStyle=0, int iLoop=1, int iMs=2000);
	void Pause(void);
	void Resume(void);
	void Stop(int iStyle=0, int iMs=2000);
	void SetVolume(int iVol);
	int IsPlaying(void);
	int IsPaused(void);
};

#endif
