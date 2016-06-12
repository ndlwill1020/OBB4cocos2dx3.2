#ifndef __BOUND_NODE_H__
#define __BOUND_NODE_H__
#include "cocos2d.h"

USING_NS_CC;

class BoundNode : public Node{
public:
	BoundNode();
	~BoundNode();
	
	static BoundNode* createWithSize(Size spriteSize);
	bool initWithSize(Size spriteSize);
	
	//Rect {Vec2 origin;Size  size;}  F:(0.f-1.f)
	static BoundNode* createWithRect(Rect spriteRect, Color4F color = Color4F::RED);
	bool initWithRect(Rect spriteRect, Color4F color);
    
    //lower left -> lower right.....
    static BoundNode* createWithVectors(const Vec2* vectors, Color4F color = Color4F::RED);
    bool initWithVectors(const Vec2* vectors, Color4F color = Color4F::RED);
    
};

#endif