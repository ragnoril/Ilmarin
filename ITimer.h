/*
timer s�n�f�:

zamanlay�c� i�te...

construct: interval de�eri, timer'�n �al���p �al��mad��� 
de�eri, vakti gelince �al��t�raca�� fonksiyon, fonksiyona 
verilecek ilk ve ikinci parametreler girilerek olu�turulur.

update: callback vakti geldi mi diye bakan fonksiyon. bunsuz 
olmaz.

pause: timer'� duraklat�r. ticks s�f�rlanmaz.

resume: devam ettirir timer'�.

stop: timer'� tam dururur. ticks'ide s�f�rlar, am�na bile kor.

start: timer'� ba�lat�r. bunsuzda olmaz san�r�m?

getticks: ticks'i d�nd�r�r, elimize verir.

getinterval: "la bunun interval'i neydi la?" diye kendimize 
sordu�umuzda imdad�m�za yeti�ir, interval verisini d�nd�r�r.

setinterval: interval verisini b�z�klat�r, de�i�tirtir.

*/

#ifndef ITIMER_H
#define ITIMER_H

class ITimer
{
public:
	ITimer(int _iInterval, int _iRunning, void (*_vfCallback)(int, int), int _iLParam, int _iRParam);
	virtual ~ITimer(void);

	void (*vfCallback)(int, int); //callback fonksiyonuna pointer
	int iLParam; //callback fonksiyonuna ge�ilecek ilk parametre
	int iRParam; //callback fonksiyonuna ge�ilecek ikinci parametre
	
	void Update(void); //update
	void Pause(void); //ticks i s�f�rlamadan durdurur
	void Resume(void); //basit�e, iRunning = 1 yapar
	void Stop(void); //hem timer � durdurur hem de ticks i s�f�rlar
	void Start(void); //timer � ba�lat�r ama ticksi de s�f�rlar
	int GetTicks(void); //ticksi d�nd�r�r
	int GetInterval(void); //intervali d�nd�r�r
	void SetInterval(int _iInterval); //intervali ayarlar

	void SetParams(int lParam, int rParam);

private:
	unsigned int lastTimerTrigger;
	unsigned int uiTicks;
	int iRunning;
	int iInterval;

};

#endif
