#include "ISprite.h"

ISprite::ISprite(void)
{
	uiSequenceCount = 0;
	uiFrameCount = 0;
	iStatus = SPRITE_STOPPED;
	lastTimerTrigger = 0;
	timeSinceLastUpdate = 0;
	uiCurrentSequence = 0;
	bLoopSequence = false;
	uiCurrentFrame = 0;
	iOverrideInterval = 0;

	uiTileWidth = 0;
	uiTileHeight = 0;
	uiTilePerRow = 0;
	uiTilePerCol = 0;


	sPosition.x = 0;
	sPosition.y = 0;

	fRotation = 0.0f;
	fScale = 1.0f;

	
}

ISprite::~ISprite(void)
{
  //vecSequences.empty();
}

void ISprite::Load(ISurface *srf, int w, int h, int r, int c, int fc)
{
  tileset=srf;

  uiTileWidth = w;
  uiTileHeight = h;
  uiTilePerRow = r;
  uiTilePerCol = c;
  uiFrameCount = fc;

  uiSequenceCount=(r*c)/fc;
}

void ISprite::Render(float x, float y)
{
  //int interval = (iOverrideInterval != 0) ? iOverrideInterval : vecSequences[uiCurrentSequence]->GetInterval();
  // düzeltene kadar böyle kalsın
  int interval = iOverrideInterval;
	
  if (uiCurrentFrame >= uiFrameCount)
    uiCurrentFrame = 0;

  if (uiFrameCount > 0)
  {
    //    BlitSurface(x, y, vecSequences[uiCurrentSequence]->GetFrame(uiCurrentFrame));
    BlitSurface(x, y, tileset, (uiCurrentSequence*uiFrameCount)+uiCurrentFrame);     // x,y,surface,index

    if (iStatus != SPRITE_STOPPED && iStatus != SPRITE_PAUSED)
    {
      timeSinceLastUpdate = SDL_GetTicks() - lastTimerTrigger;
      while (timeSinceLastUpdate > interval)
      {
	if (bLoopSequence == false)
	{
	  NextFrame();
	}
	else
	{
	  if (uiCurrentFrame == uiFrameCount - 1)
	    NextSequence();
	  else
	    uiCurrentFrame++;
	}
	timeSinceLastUpdate -= interval;
      }
      lastTimerTrigger = SDL_GetTicks() - timeSinceLastUpdate;
    }
  }
  else
  {
    NextSequence();
  }

}

void ISprite::Render()
{
	Render(sPosition.x, sPosition.y);
}

void ISprite::Render(IPoint * point)
{
	Render(point->x, point->y);
}

void ISprite::NextSequence()
{
	if (uiCurrentSequence < uiSequenceCount - 1)
	{
		uiCurrentSequence++;
		uiCurrentFrame = 0;
	}
	else
	{
		uiCurrentSequence = 0;
		uiCurrentFrame = 0;
	}
}

void ISprite::NextFrame()
{
	if (uiCurrentFrame < uiFrameCount - 1)
		uiCurrentFrame++;
	else
		uiCurrentFrame = 0;
}


void ISprite::BlitSurface(GLfloat x, GLfloat y, ISurface * surface, int index)
{
  //	float halfWidth = (float)surface->GetWidth() / 2, halfHeight = (float)surface->GetHeight() / 2; /* So, taking half width and height values as offset from center */
  float halfWidth = (float)(surface->GetWidth()/uiTilePerRow);
  float halfHeight = (float)(surface->GetHeight()/uiTilePerCol);

  int i=index%uiTilePerRow; int j=index/uiTilePerRow;
  int r=uiTilePerRow;
	glEnable(GL_TEXTURE_2D); /* Enable texture and alpha */
	glEnable(GL_ALPHA_TEST);
	glPushMatrix(); /* Save current matrix */
	    glTranslatef(x, y, 0.0f); /* Move cursor to the position */
		glRotatef(fRotation, 0.0, 0.0, 1.0);
		glScalef(fScale, fScale, 1.0f);
		glBindTexture(GL_TEXTURE_2D, *surface->GetImageData());
		    glBegin(GL_QUADS);
		      glColor3f(1.0f, 1.0f, 1.0f);


		      glTexCoord2f((1.0/r)*i,(1.0/r)*j);
		      glVertex3f(0.0, 0.0, 0.0);

		      glTexCoord2f(((1.0/r)*i)+(1.0/r),(1.0/r)*j);
		      glVertex3f(halfWidth, 0.0, 0.0);

		      glTexCoord2f(((1.0/r)*i)+(1.0/r),((1.0/r)*j)+(1.0/r));
		      glVertex3f(halfWidth, halfHeight, 0.0);

		      glTexCoord2f((1.0/r)*i,((1.0/r)*j)+(1.0/r));
		      glVertex3f(0.0, halfHeight, 0.0);
		    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
}
