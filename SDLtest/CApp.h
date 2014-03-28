#ifndef _CAPP_H_
    #define _CAPP_H_

#include "SDL/SDL.h"

#include "CEvent.h"
#include "CSurface.h"

#include "hfiles/Park.h"

class CApp : public CEvent {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

        SDL_Surface*    Surf_Test;

    public:
        CApp();

        int OnExecute();

    public:
        Park Pmap;

        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

#endif
