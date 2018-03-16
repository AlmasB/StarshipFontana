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

enum class SFAssetType { PLAYER, PROJECTILE, ALIEN, COIN };

class SFAsset {
public:
    SFAsset(const SFAssetType, SDL_Renderer*);
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

    bool is_alive;
    SFAssetType type;
    SDL_Rect bbox;

    SDL_Texture * sprite;
    SDL_Renderer * renderer;

    string GetImageName(const SFAssetType&);
    void Translate(Vector2&);
};

#endif
