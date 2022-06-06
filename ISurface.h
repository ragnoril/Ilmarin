#ifndef ISURFACE_H
#define ISURFACE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>


class ISurface
{

public:
	ISurface();
	void Load(char *filename);
	void MaskedLoad(char *filename, int r, int g, int b);
	void Free();
	unsigned int GetWidth() { return uiWidth; }
	unsigned int GetHeight() { return uiHeight; }
	unsigned int * GetImageData() { return &uiImageData; }

private:
	unsigned int uiImageData;
	unsigned int uiWidth;
	unsigned int uiHeight;
	
};


#endif
