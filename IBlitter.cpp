#include "IBlitter.h"

IBlitter::IBlitter()
{
  fScale=1.0f;
  fRotation=0.0f;
}

void IBlitter::Blit(GLfloat x, GLfloat y)
{
  //float halfWidth = (float)surface->GetWidth() / 2, halfHeight = (float)surface->GetHeight() / 2; /* So, taking half width and height values as offset from center */
  float halfWidth = (float)surface->GetWidth(), halfHeight = (float)surface->GetHeight();
	glEnable(GL_TEXTURE_2D); /* Enable texture and alpha */
	glEnable(GL_ALPHA_TEST);
	glPushMatrix(); /* Save current matrix */
	    glTranslatef(x, y, 0.0f); /* Move cursor to the position */
	    glRotatef(fRotation, 0.0, 0.0, 1.0);
	    glScalef(fScale, fScale, 1.0f);
		glBindTexture(GL_TEXTURE_2D, *surface->GetImageData());
		    glBegin(GL_QUADS);
			    glColor3f(1.0f, 1.0f, 1.0f);

			    glTexCoord2d(0,0);
			    glVertex3f(0.0, 0.0, 0.0);

			    glTexCoord2d(1,0);
			    glVertex3f(halfWidth, 0.0, 0.0);	

			    glTexCoord2d(1,1);
			    glVertex3f(halfWidth, halfHeight, 0.0);	

			    glTexCoord2d(0,1);
			    glVertex3f(0.0, halfHeight, 0.0);
			glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}

void IBlitter::Blit(GLfloat x, GLfloat y, int tx, int ty, int tw, int th)
{
  //float halfWidth = (float)tileset->GetTileSize() / 2, halfHeight = (float)tileset->GetTileSize() / 2; /* So, taking half width and height values as offset from center */
  float halfWidth = (float)surface->GetWidth(), halfHeight = (float)surface->GetHeight();

  float i=(1.0/halfWidth); float j=(1.0/halfHeight);

	glEnable(GL_TEXTURE_2D); /* Enable texture and alpha */
	glEnable(GL_ALPHA_TEST);
	glPushMatrix(); /* Save current matrix */
	    glTranslatef(x, y, 0.0f); /* Move cursor to the position */
		glRotatef(fRotation, 0.0, 0.0, 1.0);
		glScalef(fScale, fScale, 1.0f);
		glBindTexture(GL_TEXTURE_2D, *surface->GetImageData());
		    glBegin(GL_QUADS);
			    glColor3f(1.0f, 1.0f, 1.0f);

			    glTexCoord2f((i*tx),(j*ty));
			    glVertex3f(0.0, 0.0, 0.0);

			    glTexCoord2f((i*tx)+(i*tw),(j*ty));
			    glVertex3f(tw, 0.0, 0.0);	

			    glTexCoord2f((i*tx)+(i*tw),(j*ty)+(j*th));
			    glVertex3f(tw, th, 0.0);	

			    glTexCoord2f((i*tx),(j*ty)+(j*th));
			    glVertex3f(0.0, th, 0.0);
			glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}

