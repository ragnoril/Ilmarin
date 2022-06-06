#include "ISurface.h"

ISurface::ISurface()
{

}

void ISurface::Load(char *filename)
{
  int i, j;

  // Load texture using SDL_Image
  SDL_Surface *srfTemp = IMG_Load(filename);

  if (srfTemp == NULL)
    return;

  // Set up opengl-compatible pixel format
  SDL_PixelFormat pf;
  pf.palette = NULL;
  pf.BitsPerPixel = 32;
  pf.BytesPerPixel = 4;
  pf.alpha = 0;
  pf.colorkey = 0;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  pf.Rmask = 0x000000ff;
  pf.Rshift = 0;
  pf.Rloss = 0;
  pf.Gmask = 0x0000ff00;
  pf.Gshift = 8;
  pf.Gloss = 0;
  pf.Bmask = 0x00ff0000;
  pf.Bshift = 16;
  pf.Bloss = 0;
  pf.Amask = 0xff000000;
  pf.Ashift = 24;
  pf.Aloss = 0;
#else    
  pf.Amask = 0x000000ff;
  pf.Ashift = 0;
  pf.Aloss = 0;
  pf.Bmask = 0x0000ff00;
  pf.Bshift = 8;
  pf.Bloss = 0;
  pf.Gmask = 0x00ff0000;
  pf.Gshift = 16;
  pf.Gloss = 0;
  pf.Rmask = 0xff000000;
  pf.Rshift = 24;
  pf.Rloss = 0;
#endif
  // Convert texture to said format
  SDL_Surface *tm = SDL_ConvertSurface(srfTemp, &pf,SDL_SWSURFACE);

  // Cleanup
  SDL_FreeSurface(srfTemp);

  // Lock the converted surface for reading
  SDL_LockSurface(tm);

  uiWidth = tm->w;
  uiHeight = tm->h;

  unsigned int * src = (unsigned int *)tm->pixels;


  // mark all pixels with alpha = 0 to black
  for (i = 0; i < uiHeight; i++)
  {
    for (j = 0; j < uiWidth; j++)
    {
      if ((src[i*uiWidth+j] & pf.Amask) == 0)
	src[i*uiWidth+j] = 0;
    }
  }

  glGenTextures(1, &uiImageData);
  glBindTexture(GL_TEXTURE_2D, uiImageData);


  // Tell OpenGL to read the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tm->w, tm->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)src);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


  // Unlock..
  SDL_UnlockSurface(tm);

  // and cleanup.
  SDL_FreeSurface(tm);

}

void ISurface::MaskedLoad(char *filename, int r, int g, int b)
{
  int i, j;

  // Load texture using SDL_Image
  SDL_Surface *srfTemp = IMG_Load(filename);

  if (srfTemp == NULL)
    return;

  // Set up opengl-compatible pixel format
  SDL_PixelFormat pf;
  pf.palette = NULL;
  pf.BitsPerPixel = 32;
  pf.BytesPerPixel = 4;
  pf.alpha = 0;
  pf.colorkey = 0;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  pf.Rmask = 0x000000ff;
  pf.Rshift = 0;
  pf.Rloss = 0;
  pf.Gmask = 0x0000ff00;
  pf.Gshift = 8;
  pf.Gloss = 0;
  pf.Bmask = 0x00ff0000;
  pf.Bshift = 16;
  pf.Bloss = 0;
  pf.Amask = 0xff000000;
  pf.Ashift = 24;
  pf.Aloss = 0;
#else    
  pf.Amask = 0x000000ff;
  pf.Ashift = 0;
  pf.Aloss = 0;
  pf.Bmask = 0x0000ff00;
  pf.Bshift = 8;
  pf.Bloss = 0;
  pf.Gmask = 0x00ff0000;
  pf.Gshift = 16;
  pf.Gloss = 0;
  pf.Rmask = 0xff000000;
  pf.Rshift = 24;
  pf.Rloss = 0;
#endif
  // Convert texture to said format
  SDL_Surface *tm = SDL_ConvertSurface(srfTemp, &pf,SDL_SWSURFACE);

  // Cleanup
  SDL_FreeSurface(srfTemp);

  // Lock the converted surface for reading
  SDL_LockSurface(tm);

  uiWidth = tm->w;
  uiHeight = tm->h;

  unsigned int * src = (unsigned int *)tm->pixels;


  // mark all pixels with alpha = 0 to black
  for (i = 0; i < uiHeight; i++)
  {
    for (j = 0; j < uiWidth; j++)
    {
      if ((src[i*uiWidth+j] & pf.Amask) == 0)
	src[i*uiWidth+j] = 0;
    }
  }



  unsigned char *buffer;
  unsigned char *p;
  unsigned char cR, cG, cB;

  int iSize = tm->w * tm->h * 4;
  buffer = new unsigned char[tm->w * tm->h * 4];
  p=(unsigned char *)tm->pixels;
  for(int i = 0, j = 0; i < iSize; i += 4, j += 4)
  {
	  cR = p[i];
	  cG = p[i + 1];
	  cB = p[i + 2];
	  buffer[j]=cR;
	  buffer[j+1]=cG;
	  buffer[j+2]=cB;
	  if(cB == b && cG == g && cR == r)
		  buffer[j + 3] = 0;
	  else
		  buffer[j + 3] = 255;
  }
  glGenTextures(1, &uiImageData);
  glBindTexture(GL_TEXTURE_2D, uiImageData);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tm->w, tm->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Unlock..
  SDL_UnlockSurface(tm);

  if (tm)
	  SDL_FreeSurface(tm);
  delete[] buffer;
}


void ISurface::Free()
{
  glDeleteTextures(1, &uiImageData);
  uiImageData = NULL;
}
