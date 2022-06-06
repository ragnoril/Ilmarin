/*
timer sýnýfý:

zamanlayýcý iþte...

construct: interval deðeri, timer'ýn çalýþýp çalýþmadýðý 
deðeri, vakti gelince çalýþtýracaðý fonksiyon, fonksiyona 
verilecek ilk ve ikinci parametreler girilerek oluþturulur.

update: callback vakti geldi mi diye bakan fonksiyon. bunsuz 
olmaz.

pause: timer'ý duraklatýr. ticks sýfýrlanmaz.

resume: devam ettirir timer'ý.

stop: timer'ý tam dururur. ticks'ide sýfýrlar, amýna bile kor.

start: timer'ý baþlatýr. bunsuzda olmaz sanýrým?

getticks: ticks'i döndürür, elimize verir.

getinterval: "la bunun interval'i neydi la?" diye kendimize 
sorduðumuzda imdadýmýza yetiþir, interval verisini döndürür.

setinterval: interval verisini býzýklatýr, deðiþtirtir.

*/

#ifndef ITIMER_H
#define ITIMER_H

class ITimer
{
public:
	ITimer(int _iInterval, int _iRunning, void (*_vfCallback)(int, int), int _iLParam, int _iRParam);
	virtual ~ITimer(void);

	void (*vfCallback)(int, int); //callback fonksiyonuna pointer
	int iLParam; //callback fonksiyonuna geçilecek ilk parametre
	int iRParam; //callback fonksiyonuna geçilecek ikinci parametre
	
	void Update(void); //update
	void Pause(void); //ticks i sýfýrlamadan durdurur
	void Resume(void); //basitçe, iRunning = 1 yapar
	void Stop(void); //hem timer ý durdurur hem de ticks i sýfýrlar
	void Start(void); //timer ý baþlatýr ama ticksi de sýfýrlar
	int GetTicks(void); //ticksi döndürür
	int GetInterval(void); //intervali döndürür
	void SetInterval(int _iInterval); //intervali ayarlar

	void SetParams(int lParam, int rParam);

private:
	unsigned int lastTimerTrigger;
	unsigned int uiTicks;
	int iRunning;
	int iInterval;

};

#endif
