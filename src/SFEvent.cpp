#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event & event) {
    switch (event.type) {
    case SDL_QUIT:
        code = SFEventType::QUIT;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            code = SFEventType::PLAYER_LEFT;
            break;
        case SDLK_RIGHT:
            code = SFEventType::PLAYER_RIGHT;
            break;
        case SDLK_SPACE:
            code = SFEventType::FIRE;
            break;
        case SDLK_q:
            code = SFEventType::QUIT;
            break;
        }
        break;
    default:
        code = SFEventType::NONE;
        break;
    }
}

SFEventType SFEvent::GetCode() {
    return code;
}
