#include "ITimer.h"
#include <SDL/SDL.h>



ITimer::ITimer(int _iInterval, int _iRunning, void (*_vfCallback)(int, int), int _iLParam, int _iRParam)
{
	iInterval = _iInterval;
	iRunning = _iRunning;
	vfCallback = _vfCallback;
	uiTicks = 0;
	iLParam = _iLParam;
	iRParam = _iRParam;
	lastTimerTrigger = SDL_GetTicks();
}

void ITimer::Update()
{
	if(iRunning != 0)
	{
		int timeSinceLastUpdate = SDL_GetTicks() - lastTimerTrigger;
		while(timeSinceLastUpdate > iInterval && vfCallback != NULL) {
			vfCallback(iLParam, iRParam);
                        timeSinceLastUpdate -= iInterval;
                }
                // timeSinceLastUpdate is now some left-over time. Push
                // back lastTimerTrigger to account for that amount of elapsed
                // time for the next time we get an Update
                lastTimerTrigger = SDL_GetTicks() - timeSinceLastUpdate;
	}        
}

int ITimer::GetTicks()
{
	return lastTimerTrigger;
}

void ITimer::Pause()
{
	iRunning = 0;
}

void ITimer::Resume()
{
	iRunning = 1;
}

void ITimer::Stop()
{
	iRunning = 0;
	uiTicks = 0;
}

void ITimer::Start()
{
	iRunning = 1;
	uiTicks = 0;
}

void ITimer::SetInterval(int _iInterval)
{
	iInterval = _iInterval;
}

int ITimer::GetInterval()
{
	return iInterval;
}


ITimer::~ITimer(void)
{
}

void ITimer::SetParams(int lParam, int rParam)
{
	iLParam = lParam;
	iRParam = rParam;
}
