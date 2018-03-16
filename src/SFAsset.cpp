#include "SFAsset.h"

SFAsset::SFAsset(const SFAssetType type, SDL_Renderer * renderer) : is_alive(true), type(type), renderer(renderer) {

    string image_name = GetImageName(type);

    sprite = IMG_LoadTexture(renderer, image_name.c_str());

    if (!sprite) {
        throw SFException("Couldn't load asset: " + image_name);
    }

    // Get texture width & height
    int w, h;
    SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

    // Initialise bounding box
    bbox = { 0, 0, w, h };
}

string SFAsset::GetImageName(const SFAssetType& type) {
    switch (type) {
        case SFAssetType::PLAYER:
            return "assets/player.png";

        case SFAssetType::PROJECTILE:
            return "assets/projectile.png";

        case SFAssetType::ALIEN:
            return "assets/alien.png";

        case SFAssetType::COIN:
            return "assets/coin.png";
    }
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
    is_alive = false;
}

bool SFAsset::IsAlive() {
    return is_alive;
}

void SFAsset::HandleCollision() {
    if (SFAssetType::PROJECTILE == type || SFAssetType::ALIEN == type) {
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
