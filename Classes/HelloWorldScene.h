#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "OBB.hpp"
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void update(float ft);
private:
    HelloWorld();
    ~HelloWorld();
private:
    DrawNode *drawNode;
    Sprite *right;
    OBB* leftOBB;
    OBB* rightOBB;
    
    Vec2 corners[4];
};

#endif // __HELLOWORLD_SCENE_H__
