#ifndef SFEVENT_H
#define SFEVENT_H

#include <SDL.h>

enum class SFEventType { NONE, QUIT, PLAYER_LEFT, PLAYER_RIGHT, FIRE };

/**
 * Abstracts away from SDL_Event so that our game event management needs no SDL-specific code.
 */
class SFEvent {
public:
    SFEvent(const SDL_Event &);
    SFEventType GetCode();
private:
    SFEventType code;
};

#endif
