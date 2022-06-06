#include "IApplication.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <time.h>

IApplication::IApplication(void)
{
	uiStartClock = 0;
	uiDeltaClock = 0;
	uiCurrentFps = 0;
	iRunning = 1;
}

IApplication::~IApplication(void)
{

}

void IApplication::Breath()
{
	if (uiDeltaClock != 0)
		uiCurrentFps = 1000 / uiDeltaClock;
	uiDeltaClock = SDL_GetTicks() - uiStartClock;
    uiStartClock = SDL_GetTicks();
}




int IApplication::Run()
{
	uiStartClock = SDL_GetTicks();
	SDL_GetMouseState(&uiMouseX, &uiMouseY);
	return iRunning;
}

void IApplication::Stop()
{
	iRunning = 0;
}

std::string IApplication::GetWindowCaption()
{
	return szWindowCaption;
}

void IApplication::SetWindowCaption(std::string szCaption)
{
	szWindowCaption = szCaption;
	SDL_WM_SetCaption (szCaption.c_str(), NULL);
}

void IApplication::Init(std::string szCaption, int iW, int iH, int iBpp, int iFullscr)
{
	
  GLint iViewport[4];
  int iFlag = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL;
  szWindowCaption = szCaption;
    

    if (iFullscr == 1)
        iFlag = iFlag | SDL_FULLSCREEN;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Screen = SDL_SetVideoMode (iW, iH, iBpp, iFlag);
	iWidth = iW;
	iHeight = iH;
    SDL_WM_SetCaption (szCaption.c_str(), NULL);
    
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);

	glGetIntegerv( GL_VIEWPORT, iViewport );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();

	glOrtho( iViewport[0], iViewport[0]+iViewport[2],
			 iViewport[1]+iViewport[3], iViewport[1], -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );
	glEnable(GL_TEXTURE_2D);

	SDL_EnableKeyRepeat(1, 1);
	srand(time(0));

}

void IApplication::Quit()
{
  glPopAttrib();
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();

  SDL_FreeSurface(Screen);
  atexit(SDL_Quit);
}

void IApplication::InitMusic(int iFrec, int iChannel, int iChunk)
{
  Mix_OpenAudio(iFrec, MIX_DEFAULT_FORMAT, iChannel, iChunk);
}

void IApplication::QuitMusic()
{
  Mix_CloseAudio();
}

void IApplication::Delay(unsigned int uiMs)
{
  SDL_Delay(uiMs);
}

void IApplication::ClearScreen()
{
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
}

void IApplication::UpdateScreen()
{
	glFlush();
  SDL_GL_SwapBuffers();
}

void IApplication::EnableAlpha()
{
  glAlphaFunc(GL_GREATER, 0.0f);
  glEnable(GL_ALPHA_TEST);
}

int IApplication::GetFps()
{
	return uiCurrentFps;
}

#if _MSC_VER > 1000

void IApplication::SetVSync(bool sync)
{
	typedef bool (APIENTRY *PFNWGLSWAPINTERVALFARPROC)(int);

	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if( wglSwapIntervalEXT )
		wglSwapIntervalEXT(sync);
}

#else

void IApplication::SetVSync(bool sync)
{
	// do nothing yet
}

#endif
