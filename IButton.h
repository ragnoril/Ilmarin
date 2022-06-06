
#ifndef IBUTTON_H
#define IBUTTON_H


#include <SDL/SDL.h>
#include <string>
#include <map>
#include "ISurface.h"
#include "IBlitter.h"


#define M_UP   0
#define M_OVER 1
#define M_DOWN 2



class IButton 
{
  int x,y;
  int w,h;
  int state;
  bool enabled;
  bool visible;
  SDLKey key;
  IBlitter renderer;
  ISurface surface;

 public:
  IButton(char *file, int x, int y, int w, int h, bool v, bool e, void (*click)(), void (*hover)());
  IButton();
  ~IButton();

  void LoadSurface(char *file);
  void SetXY(int _x, int _y) { x=_x; y=_y; };
  void SetSize(int _w, int _h) { w=_w; h=_h; };
  void SetVisible(bool v) { visible=v; };
  void SetEnable(bool e) { enabled=e; };
  void SetState(int s) { state=s; };
  void SetKey(SDLKey k) { key=k; };

  SDLKey GetKey() { return key; }
  bool GetVisible() { return visible; };
  bool GetEnable() { return enabled; };
  int GetX() { return x; };
  int GetY() { return y; };
  int GetWidth() { return w; };
  int GetHeight() { return h; };
  int GetState() { return state; };

  void SetButton(char *file, int x, int y, int w, int h, bool v, bool e, void (*click)(), void (*hover)());
  void Render();
  void FinishMe();

  void (*click_func)();
  void (*hover_func)();


};


class IButtonList 
{
  std::map<std::string, IButton*> List;
  bool enableKeys;
  int keyCount;
  SDLKey selectKey;

 public:
  IButtonList();
  ~IButtonList();

  void AddButton(std::string buttonid, IButton* button);
  void RemoveButton(std::string buttonid);
  void Render();
  void EnableKeys(bool e);
  void SetKey(SDLKey k) { selectKey=k; };
  SDLKey GetKey() { return selectKey; };
  void Update(SDL_Event event);
};


#endif
