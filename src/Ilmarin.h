/*
Ilmarin: Yüce Göklerin Evi anlamýna geliyor. 
Sanýrým Quenya'da olmasý lazým. Silmarillion'dan.
Evet, özenle seçtik :).

Coded by: Fredi & Ragnor
Date: 16.02.2007

Bu kod LGPL ile lisanslanmýþ gibidir. Öyledir yani...
This code is licenced with LGPL, i guess...

LGPL için: http://www.belgeler.org/howto/lgpl.html
For LGPL: http://www.gnu.org/licenses/lgpl.html

TODO:
-> 27.07.2008 16:47 ragnor
* ITileset ve IBlitter sınıfları eklendi
* ISurface'teki MaskedLoad'ta SDL_LoadBMP kullanılmış, o satır IMG_Load ile değiştirildi.

-> 17.02.2007 18:41 fredi
* ne yazýk ki rotate olayý istediðim gibi çalýþmýyor bir etmek lazým. nasýl düzeltileceði hakkýnda pek bir fikrim yok

->  16.02.2007 19:29 fredi
* sdl_collision tamam ama her özelliði denenmeli bi de ISurface alacak þekilde deðiþtirilmeli
* sdl_gfx de tamamdýr, transformation gibi bi bölüm açacam library de oraya ilgili fonksiyonlarý koyacam

->  16.02.2007 01:30 ragnor
* isurface'e sdl_collide ve sdl_gfx desteði.
* imusic ve isample geliþtirilebilir. efekt ekleme vs.
* opengl desteði 2d ve 3d olarak.

*/

#ifndef ILMARIN_H
#define ILMARIN_H

#include "IApplication.h"
#include "ISurface.h"
#include "IPrimitive.h"
#include "IBlitter.h"
#include "IText.h"
#include "ISprite.h"
#include "ITimer.h"
#include "IMusic.h"
#include "IEvent.h"
#include "IButton.h"

#include "Math.h"
#include "Utilities.h"

#endif

