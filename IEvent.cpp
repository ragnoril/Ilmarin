
#include "IEvent.h"

IEvent::IEvent() 
{

}


IEvent::~IEvent()
{

}


void IEvent::AddListener(Uint8 type, void (*func)())
{
  ListenerList.insert(std::pair<Uint8, void(*)()>(type, func));
}


void IEvent::RemoveListener(Uint8 type, void (*func)())
{
  ListenerList.erase(type);
}


void IEvent::Listen()
{
  std::map<Uint8,void(*)()>::iterator eventSearch;
    while (SDL_PollEvent(&Event))
    {
      eventSearch=ListenerList.find(Event.type);

      if (eventSearch!=ListenerList.end())
      {
	eventSearch->second();
      }

      // off çok amele oldu bu sanki
      //      Gui->UpdateGUI(Event);
    }
}
