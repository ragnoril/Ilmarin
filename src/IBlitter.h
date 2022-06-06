#ifndef IBLITTER_H
#define IBLITTER_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "ISurface.h"

class IBlitter
{

public:
	IBlitter();
	void SetSurface(ISurface * srf) { this->surface=srf; }
	void Blit(GLfloat x, GLfloat y);
	void Blit(GLfloat x, GLfloat y, int tx, int ty, int tw, int th);
	void SetRotation(float r) { this->fRotation = r; }
	float GetRotation(){ return fRotation; }
	void SetScale(float s) { fScale = s; }
	float GetScale() { return fScale; }

private:
	ISurface *surface;
	float fRotation;
	float fScale;
	
};


#endif
