#ifndef ISPRITE_H
#define ISPRITE_H

#include <vector>
#include "ISurface.h"
#include "IPrimitive.h"
#include "ITimer.h"

#define SPRITE_STOPPED 0
#define SPRITE_PLAYING 1
#define SPRITE_PAUSED  2

class ISprite
{
public:
	ISprite(void);
	virtual ~ISprite(void);

	void Load(ISurface *srf, int w, int h, int r, int c, int fc);
	// w-> tilewidth, h->tileheight r-> tilesperrow c-> tilespercolumn
	// fc-> framecount

	void Render(float x, float y);
	void Render();
	void Render(IPoint * point);

	void SetPosition(float x, float y) { sPosition.x = x; sPosition.y = y; }
	void SetPosition(IPoint * point) { sPosition.x = point->x; sPosition.y = point->y; }
	IPoint * GetPosition() { return &sPosition; }
	float GetXPosition() { return sPosition.x; }
	float GetYPosition() { return sPosition.y; }
	void Warp(float offx, float offy) { sPosition.x += offx; sPosition.y += offy; }

	void SetCurrentSequence(int number) { uiCurrentSequence = number; }
	int GetCurrentSequence() { return uiCurrentSequence; }
	void SetLoop(bool b) { bLoopSequence = b; }
	bool GetLoop() { return bLoopSequence; }

	void OverrideInterval(int i) { iOverrideInterval = i; }
	int GetOverInterval() { return iOverrideInterval; }

	void SetCurrentFrame(int n) { uiCurrentFrame = n; }
	int GetCurrentFrame() { return uiCurrentFrame; }

	void Start() { iStatus = SPRITE_PLAYING; }
	void Stop() { iStatus = SPRITE_STOPPED; uiCurrentFrame = 0; }
	void Pause() { iStatus = SPRITE_PAUSED; }
	void Resume() { iStatus = SPRITE_PLAYING; }
	int GetStatus() { return iStatus; }
	void SetStatus(int n) { iStatus = n; }

	int GetSequenceCount() { return uiSequenceCount; }

	void SetRotation(float r) { this->fRotation = r; }
	float GetRotation(){ return fRotation; }
	void SetScaleFactor(float s) { fScale = s; }
	float GetScaleFactor() { return fScale; }

private:
	IPoint sPosition;
	
	ISurface *tileset;

	int iStatus;

	unsigned int uiTileWidth;
	unsigned int uiTileHeight;
	unsigned int uiTilePerRow;
	unsigned int uiTilePerCol;

	unsigned int uiCurrentFrame;
	unsigned int uiFrameCount;
	unsigned int uiSequenceCount;
	unsigned int uiCurrentSequence;
	bool bLoopSequence;
	int iOverrideInterval;
	
	int timeSinceLastUpdate;
	unsigned int lastTimerTrigger;

	void NextSequence();
	void NextFrame();

	float fRotation;
	float fScale;

	void BlitSurface(GLfloat x, GLfloat y, ISurface * surface, int index);

};


#endif
