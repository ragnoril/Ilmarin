
#ifndef IEVENT_H
#define IEVENT_H

#include <SDL/SDL.h>
#include <map>
//#include "IGui.h"



class IEvent
{
  SDL_Event Event;
  std::map<Uint8,void (*)()> ListenerList;
  // IGui *Gui;

 public:
  IEvent();
  ~IEvent();

  void AddListener(Uint8 type, void (*func)());
  void RemoveListener(Uint8 type, void (*func)());
  SDL_Event GetEvent() { return Event; };
  void Listen();
  //void AttachGUI(IGui *gui) { Gui=gui; }
};


#endif

