#ifndef IAPP_H
#define IAPP_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>


class IApplication
{
public:
	IApplication(void);
	~IApplication(void);

    
	//System Calls
	void         Breath();
	std::string  GetWindowCaption();
	void         Init(std::string szCaption, int iW, int iH, int iBpp, int iFullscr);
	void         Quit(void);
	int          Run();
	void         SetWindowCaption(std::string szCaption);
	void         Stop();
	int          GetMouseX() { return uiMouseX; }
	int          GetMouseY() { return uiMouseY; }

	//Gfx
	void         ClearScreen();
	void         EnableAlpha();
	void         SetVSync(bool sync);
	void         UpdateScreen();
	int          GetWindowWidth() { return iWidth; }
	int          GetWindowHeight() { return iHeight; }

	void InitMusic(int iFrec, int iChannel, int iChunk);
	void QuitMusic(void);

	void Delay(unsigned int uiMs);

	int GetFps();

private:
	//System
	int iRunning;
	std::string szWindowCaption;
	int uiMouseX;
	int uiMouseY;

	//Gfx
	SDL_Surface * Screen;
	int iWidth, iHeight;

	//Fps
	unsigned int uiStartClock;
	unsigned int uiDeltaClock;
	unsigned int uiCurrentFps;
};

#endif
