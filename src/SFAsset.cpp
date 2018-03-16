#include "SFAsset.h"

SFAsset::SFAsset(const SFASSETTYPE type, SDL_Renderer * renderer) : type(type), renderer(renderer) {

    switch (type) {
    case SFASSET_PLAYER:
        sprite = IMG_LoadTexture(renderer, "assets/player.png");
        break;
    case SFASSET_PROJECTILE:
        sprite = IMG_LoadTexture(renderer, "assets/projectile.png");
        break;
    case SFASSET_ALIEN:
        sprite = IMG_LoadTexture(renderer, "assets/alien.png");
        break;
    case SFASSET_COIN:
        sprite = IMG_LoadTexture(renderer, "assets/coin.png");
        break;
    }

    if (!sprite) {
        throw SFException("Couldn't load asset");
    }

    // Get texture width & height
    int w, h;
    SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

    // Initialise bounding box
    bbox = { 0, 0, w, h };
}

SFAsset::~SFAsset() {
    if (sprite) {
        SDL_DestroyTexture(sprite);
        sprite = nullptr;
    }
}

int SFAsset::GetWidth() {
    return bbox.w;
}

int SFAsset::GetHeight() {
    return bbox.h;
}

void SFAsset::SetPosition(Point2 & point) {
    bbox.x = point.getX();
    bbox.y = point.getY();
}

Point2 SFAsset::GetPosition() {
    return Point2(bbox.x, bbox.y);
}

Point2 SFAsset::GetCenter() {
    return Point2(bbox.x + bbox.w / 2, bbox.y + bbox.h / 2);
}

void SFAsset::OnRender() {
    // render the full sprite using bbox as position and dimension
    SDL_RenderCopy(renderer, sprite, NULL, &bbox);
}

void SFAsset::GoWest() {
    Vector2 v = Vector2(-5.0f, 0);
    Translate(v);
}

void SFAsset::GoEast() {
    Vector2 v = Vector2(5.0f, 0);
    Translate(v);
}

void SFAsset::GoNorth() {
    Vector2 v = Vector2(0.0f, -5.0f);
    Translate(v);
}

void SFAsset::SetNotAlive() {
    type = SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
    return (SFASSET_DEAD != type);
}

void SFAsset::HandleCollision() {
    if (SFASSET_PROJECTILE == type || SFASSET_ALIEN == type) {
        SetNotAlive();
    }
}

bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
    return SDL_HasIntersection(&bbox, &other->bbox) == SDL_TRUE;
}

void SFAsset::Translate(Vector2& v) {
    bbox.x += v.getX();
    bbox.y += v.getY();
}
