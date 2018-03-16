#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event& event) {
    type = MapType(event);
}

SFEventType SFEvent::MapType(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            return SFEventType::QUIT;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    return SFEventType::PLAYER_LEFT;
                    
                case SDLK_RIGHT:
                    return SFEventType::PLAYER_RIGHT;
                    
                case SDLK_SPACE:
                    return SFEventType::FIRE;
                    
                case SDLK_q:
                    return SFEventType::QUIT;       
            }

        default:
            return SFEventType::NONE;
    }
}

SFEventType SFEvent::GetType() {
    return type;
}
