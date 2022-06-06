#ifndef IFONT_H
#define IFONT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <string>
#include "IApplication.h"

class IText
{
        GLuint LoadTexture(char * file);
public:
	IText();
	~IText();

	GLuint	base;
	GLuint FontTex;
	float fR;
	float fG;
	float fB;

	void Load(char *filename);
	void Print(int sx, int sx2, int sy, int sy2, GLint x, GLint y, char *string, int set);	
	void Print(IApplication * app, GLint x, GLint y, char *string, int set);	

	void SetColor(float _fR, float _fG, float _fB);

};



#endif
