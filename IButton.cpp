
#include "IButton.h"


IButton::IButton(char *file, int x, int y, int w, int h, bool v, bool e, void (*click)(), void (*hover)())
{
  SetState(M_UP);
  SetButton(file, x, y, w, h, v, e, click, hover);
}


IButton::IButton()
{
  SetState(M_UP);

  SetXY(0,0);
  SetSize(0,0);
  SetVisible(false);
  SetEnable(false);

  click_func=NULL;
  hover_func=NULL;
}


IButton::~IButton()
{
  FinishMe();
}


void IButton::LoadSurface(char *file)
{
  surface.Load(file);
  renderer.SetSurface(&surface);
}


void IButton::SetButton(char *file, int x, int y, int w, int h, bool v, bool e, void (*click)(), void (*hover)())
{
  LoadSurface(file);
  SetXY(x,y);
  SetSize(w,h);
  SetVisible(v);
  SetEnable(e);

  click_func=click;
  hover_func=hover;
}


void IButton::Render()
{
  renderer.Blit(x, y, 0, state*h, w, h);
}


void IButton::FinishMe()
{
  click_func=NULL;
  hover_func=NULL;
}


IButtonList::IButtonList()
{
  enableKeys=false;
  keyCount=-1;
}

IButtonList::~IButtonList()
{

}

void IButtonList::AddButton(std::string buttonid, IButton* button)
{
  List.insert(std::pair<std::string,IButton*>(buttonid,button));
}


void IButtonList::RemoveButton(std::string buttonid)
{
  List.erase(buttonid);
}


void IButtonList::Render()
{
  std::map<std::string, IButton*>::iterator thebutton;
  for(thebutton=List.begin(); thebutton!=List.end(); ++thebutton)
  {
      if (thebutton->second->GetVisible()==false)
	continue;
      thebutton->second->Render();
  }

}


void IButtonList::Update(SDL_Event event)
{
  int mousex, mousey;
  int bx,by,bw,bh;
  std::map<std::string, IButton*>::iterator thebutton;

  if (event.type==SDL_MOUSEMOTION)
  {
    mousex=event.motion.x;
    mousey=event.motion.y;
    for(thebutton=List.begin(); thebutton!=List.end(); ++thebutton)
    {
      //mouse buttonun üzerinde mi?
      if (thebutton->second->GetEnable()==false)
	continue;

      bx=thebutton->second->GetX();
      by=thebutton->second->GetY();
      bw=thebutton->second->GetWidth();
      bh=thebutton->second->GetHeight();

      if ((mousex>bx&&mousex<bx+bw)&&(mousey>by&&mousey<by+bh))
      {
	thebutton->second->SetState(M_OVER);
	if (thebutton->second->hover_func!=NULL)
	  thebutton->second->hover_func();
      }
      else
	thebutton->second->SetState(M_UP);
    }
  }
  else if (event.type==SDL_MOUSEBUTTONDOWN)
  {
    mousex=event.button.x;
    mousey=event.button.y;
    for(thebutton=List.begin(); thebutton!=List.end(); ++thebutton)
    {
      if (thebutton->second->GetEnable()==false || thebutton->second->GetVisible()==false)
	continue;

      bx=thebutton->second->GetX();
      by=thebutton->second->GetY();
      bw=thebutton->second->GetWidth();
      bh=thebutton->second->GetHeight();

      if ((mousex>bx&&mousex<bx+bw)&&(mousey>by&&mousey<by+bh))
	thebutton->second->SetState(M_DOWN);
      else
	thebutton->second->SetState(M_UP);
    }
  }
  else if (event.type==SDL_MOUSEBUTTONUP)
  {
    mousex=event.button.x;
    mousey=event.button.y;
    for(thebutton=List.begin(); thebutton!=List.end(); ++thebutton)
    {
      if (thebutton->second->GetEnable()==false || thebutton->second->GetVisible()==false)
	continue;

      bx=thebutton->second->GetX();
      by=thebutton->second->GetY();
      bw=thebutton->second->GetWidth();
      bh=thebutton->second->GetHeight();

      if ((mousex>bx&&mousex<bx+bw)&&(mousey>by&&mousey<by+bh)&&(thebutton->second->GetState()==M_DOWN)&&(thebutton->second->click_func!=NULL))
	thebutton->second->click_func();
      
      thebutton->second->SetState(M_UP);
    }
  }
  else if (event.type==SDL_KEYDOWN)
  {
    if (enableKeys==true)
    {
      if (event.key.keysym.sym==SDLK_DOWN)
      {
	keyCount++;
	if (List.size()>=keyCount)
	  keyCount=0;
      }
      else if (event.key.keysym.sym==SDLK_UP)
      {
	keyCount--;
	if (keyCount<=-1)
	  keyCount=List.size()-1;
      }
      else if (event.key.keysym.sym==selectKey)
      {
	thebutton=List.begin();
	for (int i=0;i<keyCount;i++)
	  ++thebutton;
	thebutton->second->click_func();
      }
      else 
      {
	for(thebutton=List.begin(); thebutton!=List.end(); ++thebutton)
	{
	  if (thebutton->second->GetKey()==event.key.keysym.sym)
	    thebutton->second->click_func();
	}
      }
    }
  }
}


void IButtonList::EnableKeys(bool e) 
{
  if (e==false)
  {
    enableKeys=e;
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
  }
  else if (e==true)
  {
    enableKeys=e;
    SDL_EnableKeyRepeat(0,0);
  }
}

