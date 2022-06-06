#include "IText.h"


IText::IText()
{
	fR = 1.0f;
	fG = 0.0f;
	fB = 0.0f;
}

IText::~IText()
{
	glDeleteLists(base,256);
}

void IText::Load(char *filename)
{
	glPushMatrix();
	int loop;
	float	cx;											// Holds Our X Character Coord
	float	cy;											// Holds Our Y Character Coord

	FontTex=LoadTexture(filename);
	base=glGenLists(256);								// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, FontTex);				// Select Our Font Texture
	for (loop=0; loop<256; loop++)						// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;						// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);				// Start Building A List
			glBegin(GL_QUADS);							// Use A Quad For Each Character
			
			glTexCoord2f(cx,1-cy);
			glVertex2i(0,0);
			glTexCoord2f(cx,1-cy-0.0625f);
			glVertex2i(0,16);
			glTexCoord2f(cx+0.0625f,1-cy-0.0625f);
			glVertex2i(16,16);
			glTexCoord2f(cx+0.0625f,1-cy);
			glVertex2i(16,0);
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(13,0,0);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
	glPopMatrix();
}

void IText::Print(int sx, int sx2, int sy, int sy2, GLint x, GLint y, char *string, int set)
{
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, FontTex);			// Select Our Font Texture
		glColor3f(fR, fG, fB);
		glTranslated(x, y, 0);								// Position The Text (0,0 - Bottom Left)
		glListBase(base-32+(128*set));						// Choose The Font Set (0 or 1)
		glCallLists((GLsizei)strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}

void IText::Print(IApplication * app, GLint x, GLint y, char *string, int set)
{
	Print(0, app->GetWindowWidth(), 0, app->GetWindowHeight(), x, y, string, set);
}

GLuint IText::LoadTexture(char * file)
{
  GLuint img;
  int i, j;

  // Load texture using SDL_Image
  SDL_Surface *srfTemp = IMG_Load(file);


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

  int uiWidth = tm->w;
  int uiHeight = tm->h;

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

  glGenTextures(1, &img);
  glBindTexture(GL_TEXTURE_2D, img);


  // Tell OpenGL to read the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tm->w, tm->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)src);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


  // Unlock..
  SDL_UnlockSurface(tm);

  // and cleanup.
  SDL_FreeSurface(tm);

  return img;
}

void IText::SetColor(float _fR, float _fG, float _fB)
{
	fR = _fR;
	fG = _fG;
	fB = _fB;
}
