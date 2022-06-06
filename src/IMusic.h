/*
Ses ve M�zik s�n�f�:

�imdi burda iki s�n�f var Music m�zik ve Sample ise
ses efektleri i�in (ciyuv ciyuvlar var ya onlar) 
kullan�lacak. Kullan�lmadan �nce IWindow'dan InitMusic
ile ses sistemi init edilmeli.

IMusic:

construct: y�klenecek dosyan�n ad� girilir. 

play: style 0 iken direk �alar 1 oldu�unda fade in ile girer.
loop -1 iken sonsuza dek tekrar eder, ms ise fadein in milisaniye
cinsinden s�residir.

pause: �ark�y� duraklat�r.

resume: �ark�n�n kald��� yerden devam etmesini sa�lar. �ark� 
pause durumunda de�ilken �al��t�r�lmas� sorun olmaz.

stop: style 0 iken direk durur, 1 iken fade out ile ve 
ms ise fade out'un milisaniye cinsinden s�residir.

rewind: �ark�y� ba�a sarar.

setposition: mod, ogg ve mp3'lerde �al���r. mod'ta uint16'ya
�evrilip pattern nosuna atlamas�n� sa�lar. di�erlerinde �ark�n�n
o saniyesine atlamay� sa�lar.

setvolume: ses de�erini ayarlar. 0 - 128 aras�d�r. min ve max
de�erleri a�maz.

isplaying: �al�yorsa 1 d�nd�r�r, yoksa 0.

ispaused: duraklat�lm��sa 1 d�nd�r�r, yoksa 0.

ISample: 

construct: sadece y�klenecek dosyan�n ad� girilir.

play: ayn� ama tek fark imusic'te loop default olarak -1
iken burada 1.

pause: ayn�

resume: ayn�

stop: ayn�

setvolume: ayn�

isplaying: ayn�

ispaused: ayn�

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
