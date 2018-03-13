#ifndef SFAPP_H
#define SFAPP_H

#include <memory>
#include <list>

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

using namespace std;

/**
 * Represents the StarshipFontana application.  It has responsibilities for:
 * 1. Process game events
 * 2. Update game world
 * 3. Render game world
 */
class SFApp {
public:
    SFApp(shared_ptr<SFWindow>);
    
    void StartMainLoop();

    void OnInput();
    void OnUpdate();
    void OnRender();

    void HandleEvent(SFEvent &);

    void FireProjectile();
private:
    bool is_running;

    shared_ptr<SFWindow> window;

    shared_ptr<SFAsset> player;
    
    list<shared_ptr<SFAsset> > projectiles;
    list<shared_ptr<SFAsset> > aliens;
    list<shared_ptr<SFAsset> > coins;
};

#endif
