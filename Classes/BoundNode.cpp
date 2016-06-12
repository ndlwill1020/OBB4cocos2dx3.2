#include "BoundNode.h"

BoundNode::BoundNode(){

}

BoundNode::~BoundNode(){

}

BoundNode* BoundNode::createWithSize(Size spriteSize){
	BoundNode *ret = new BoundNode();
	if (ret && ret->initWithSize(spriteSize))
	{
		ret->autorelease();
	}else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool BoundNode::initWithSize(Size spriteSize){
	if (!Node::init())
	{
		return false;
	}

	

	auto width = spriteSize.width;
	auto height = spriteSize.height;

	DrawNode *node = DrawNode::create();
	//l->t->r->b
	node->drawSegment(Vec2(-width / 2,-height / 2),Vec2(width / 2,-height /2),2.0f,Color4F::RED);
	node->drawSegment(Vec2(width / 2,-height /2),Vec2(width / 2,height /2),2.0f,Color4F::RED);
	node->drawSegment(Vec2(width / 2,height /2),Vec2(-width / 2,height /2),2.0f,Color4F::RED);
	node->drawSegment(Vec2(-width / 2,height /2),Vec2(-width / 2,-height /2),2.0f,Color4F::RED);

	//node->runAction(RepeatForever::create(Blink::create(1.5f,1.f)));

	this->addChild(node);
	

	return true;
}

/**********************************************************************************/

BoundNode* BoundNode::createWithRect(Rect spriteRect, Color4F color){
	BoundNode *ret = new BoundNode();
	if (ret && ret->initWithRect(spriteRect, color))
	{
		ret->autorelease();
	}else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool BoundNode::initWithRect(Rect spriteRect, Color4F color){
	if (!Node::init())
	{
		return false;
	}

	auto origin = spriteRect.origin;
	auto size = spriteRect.size;

	auto lbPoint = origin;
	auto ltPoint = Vec2(origin.x, origin.y + size.height);
	auto rtPoint = Vec2(origin.x + size.width, origin.y + size.height);
	auto rbPoint = Vec2(origin.x + size.width, origin.y);

	DrawNode *node = DrawNode::create();
	node->drawSegment(lbPoint, ltPoint, 2.0f, color);
	node->drawSegment(ltPoint, rtPoint, 2.0f, color);
	node->drawSegment(rtPoint, rbPoint, 2.0f, color);
	node->drawSegment(rbPoint, lbPoint, 2.0f, color);
	this->addChild(node);

	return true;
}


/**********************************************************************************/

BoundNode* BoundNode::createWithVectors(const Vec2* vectors, Color4F color){
    BoundNode *ret = new BoundNode();
    if (ret && ret->initWithVectors(vectors, color))
    {
        ret->autorelease();
    }else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool BoundNode::initWithVectors(const Vec2* vectors, Color4F color){
    if (!Node::init())
    {
        return false;
    }
    
    const Vec2 *cornerFI = vectors;
    Vec2 corners[4];
    corners[0] = *cornerFI;
    corners[1] = *(cornerFI + 1);
    corners[2] = *(cornerFI + 2);
    corners[3] = *(cornerFI + 3);
    
    DrawNode* node = DrawNode::create();
    node->drawSegment(corners[0], corners[1], 1.0f, color);
    node->drawSegment(corners[1], corners[2], 1.0f, color);
    node->drawSegment(corners[2], corners[3], 1.0f, color);
    node->drawSegment(corners[3], corners[0], 1.0f, color);
    this->addChild(node);

    
    return true;
}