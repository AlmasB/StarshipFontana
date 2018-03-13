#include "SFApp.h"

#define SECOND_MILLIS 1000
#define FRAME_RATE 60
#define DELAY SECOND_MILLIS / FRAME_RATE

SFApp::SFApp(std::shared_ptr<SFWindow> window) : is_running(true), window(window) {
    int canvas_w = window->GetWidth();
    int canvas_h = window->GetHeight();

    player = make_shared<SFAsset>(SFASSET_PLAYER, window->GetRenderer());
    auto player_pos = Point2(canvas_w / 2 - player->GetBoundingBox()->GetWidth() / 2, canvas_h - player->GetBoundingBox()->GetHeight());
    player->SetPosition(player_pos);

    const int number_of_aliens = 10;
    for (int i = 0; i < number_of_aliens; i++) {
        // place an alien at width/number_of_aliens * i
        auto alien = make_shared<SFAsset>(SFASSET_ALIEN, window->GetRenderer());
        auto pos = Point2((canvas_w / number_of_aliens) * i + alien->GetBoundingBox()->GetWidth() / 2, 200.0f);
        alien->SetPosition(pos);
        aliens.push_back(alien);
    }

    auto coin = make_shared<SFAsset>(SFASSET_COIN, window->GetRenderer());
    auto pos = Point2((canvas_w / 4), 100);
    coin->SetPosition(pos);
    coins.push_back(coin);
}

void SFApp::StartMainLoop() {
    while (is_running) {
        
        OnInput();
        OnUpdate();
        OnRender();

        // note this doesn't take into account time spent in the loop
        SDL_Delay(DELAY);
    }
}

void SFApp::OnInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // wrap an SDL_Event with our SFEvent and handle it
        HandleEvent(SFEvent(event));
    }
}

/**
 * Handle all events (mainly keyboard).
 */
void SFApp::HandleEvent(SFEvent& event) {
    switch (event.GetCode()) {
        case SFEVENT_QUIT:
            is_running = false;
            break;
        case SFEVENT_PLAYER_LEFT:
            player->GoWest();
            break;
        case SFEVENT_PLAYER_RIGHT:
            player->GoEast();
            break;
        case SFEVENT_FIRE:
            FireProjectile();
            break;
    }
}

void SFApp::OnUpdate() {
    
    // 1. Move / update game objects
    for (auto p : projectiles) {
        p->GoNorth();
    }

    // coins
    for (auto c : coins) {
        c->GoNorth();
    }

    // enemies
    for (auto a : aliens) {
        // do something here
    }

    // 2. Detect collisions
    for (auto p : projectiles) {
        for (auto a : aliens) {
            if (p->CollidesWith(a)) {
                p->HandleCollision();
                a->HandleCollision();
            }
        }
    }

    // 3. Remove aliens if they are not alive (dead)
    aliens.remove_if([](shared_ptr<SFAsset> a) { return !a->IsAlive(); } );

    // Note: we should also remove dead coins and projectiles
    // and we should remove projectiles that are off-screen
}

void SFApp::OnRender() {
    // 1. Clear visible content
    window->ClearScreen();

    // 2. Draw game objects off-screen
    player->OnRender();

    for (auto p : projectiles) {
        if (p->IsAlive()) { 
            p->OnRender(); 
        }
    }

    for (auto a : aliens) {
        if (a->IsAlive()) { 
            a->OnRender(); 
        }
    }

    for (auto c : coins) {
        c->OnRender();
    }

    // 3. Switch the off-screen buffer to be on-screen
    window->ShowScreen();
}

void SFApp::FireProjectile() {
    auto bullet = make_shared<SFAsset>(SFASSET_PROJECTILE, window->GetRenderer());
    auto v = player->GetCenter();
    auto pos = Point2(v.getX() - bullet->GetBoundingBox()->GetWidth() / 2, v.getY());
    bullet->SetPosition(pos);
    projectiles.push_back(bullet);
}