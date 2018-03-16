#ifndef SFASSET_H
#define SFASSET_H

#include <string>
#include <memory>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFWindow.h"

using namespace std;

/**
 * We could create SFPlayer, SFProjectile and SFAsset which are subclasses
 * of SFAsset.  However, I've made an implementation decision to use this
 * enum to mark the type of the SFAsset.  If we add more asset types then
 * the subclassing strategy becomes a better option.
 */
enum SFASSETTYPE { SFASSET_DEAD, SFASSET_PLAYER, SFASSET_PROJECTILE, SFASSET_ALIEN, SFASSET_COIN };

class SFAsset {
public:
    SFAsset(const SFASSETTYPE, SDL_Renderer*);
    ~SFAsset();

    int GetWidth();
    int GetHeight();

    void      SetPosition(Point2 &);
    Point2    GetPosition();
    Point2    GetCenter();
    void      OnRender();
    void      GoEast();
    void      GoWest();
    void      GoNorth();
    void      SetNotAlive();
    bool      IsAlive();
    void      HandleCollision();

    bool CollidesWith(shared_ptr<SFAsset>);
    
private:

    SFASSETTYPE type;
    SDL_Rect bbox;

    SDL_Texture * sprite;
    SDL_Renderer * renderer;

    void Translate(Vector2&);
};

#endif
