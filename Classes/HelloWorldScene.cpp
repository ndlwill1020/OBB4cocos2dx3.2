#include "HelloWorldScene.h"
#include "BoundNode.h"

USING_NS_CC;

//#define Vec2Test
#define ROTATE_ANGLE -45.0f
#define SEGMENT_RADIUS 1.0f

HelloWorld::HelloWorld(){

}

HelloWorld::~HelloWorld(){
    leftOBB->release();
    rightOBB->release();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
#ifdef Vec2Test
    //Vec2 Test
    Vec2 one = Vec2(10.0f,0);
    Vec2 other = Vec2(10.0f,10.0f);
    
    Vec2 one1 = Vec2(20.0f, 0.0f);
    Vec2 other1 = Vec2(20.0f, 10.f);
    
    Vec2 one2 = Vec2(15.0f,0.0f);
    Vec2 one3 = Vec2(30.0f,0.0f);
    
    Vec2 test = Vec2(10.0f,0.0f);
    //得到两个角的夹角 弧度值得到
    log("angle:%f",Vec2::angle(one, other));//0.785398
    log("angle:%f",Vec2::angle(other, one));//0.785398
    //10 两个点连线的距离
    log("distance:%f",one.distance(other));
    //100 点乘10*10+0*10=100  向量点乘a.b=a.x*b.x + a.y*b.y
    log("dot:%f",one.dot(other));
    //1个向量的长度10
    log("length:%f",one.length());
    //归一化 将向量的大小变为1
    test.normalize();
    log("normalize:%f %f",test.x, test.y);
    //得到弧度
    log("getAngle:%f",one.getAngle(other));//0.785398
    log("getAngle:%f",other.getAngle(one));//－0.785398
    
    //other绕着one这个点旋转多少弧度
    log("other:%f %f one:%f %f",other.x, other.y, one.x, one.y);
    Vec2 result1 = other.rotateByAngle(one, M_PI_4);
    Vec2 result2 = other.rotateByAngle(one, -M_PI_4);//-的弧度是顺时针
    log("result1:%f %f  result2:%f %f",result1.x, result1.y, result2.x, result2.y);
    

    //线段是否平行
    log("isLineParallel:%d",Vec2::isLineParallel(one, other, one1, other1));
    log("isLineParallel:%d",Vec2::isLineParallel(one, one1, other, other1));
    //线或线段是否相交
    log("isLineIntersect:%d",Vec2::isLineIntersect(one, one1, other, other1));
    log("isLineIntersect:%d",Vec2::isLineIntersect(one, other1, one1, other));
    log("isSegmentIntersect:%d",Vec2::isSegmentIntersect(one, other1, one1, other));
    
    //得到相交点
    Vec2 intersectPoint = Vec2::getIntersectPoint(one, other1, one1, other);
    log("intersectPoint:%f %f",intersectPoint.x, intersectPoint.y);
    
    //线段是否有重叠
    log("isLineOverlap:%d",Vec2::isLineOverlap(one, one1, other, other1));
    log("isLineOverlap:%d",Vec2::isLineOverlap(one, other1, one1, other));
    log("isLineOverlap:%d",Vec2::isLineOverlap(one, one1, one1, one2));//1
    log("isLineOverlap:%d",Vec2::isLineOverlap(one, one1, one2, one3));//1
#endif
    
    //********************************************
    
    auto left = Sprite::create("frog.png");
    left->setPosition(visibleSize.width * 0.25f, visibleSize.height / 2);
    this->addChild(left,0);
    
    
    
    right = Sprite::create("frog.png");
    right->setPosition(visibleSize.width * 0.75f, visibleSize.height / 2);
    log("right Position:%f %f",right->getPositionX(), right->getPositionY());
    //auto originRect = right->getBoundingBox();
    right->setRotation(ROTATE_ANGLE);//负 逆时针旋转
    this->addChild(right,1);
    
    //size create
//    auto leftBound = BoundNode::createWithSize(left->getContentSize());
//    leftBound->setPosition(left->getPosition());
//    this->addChild(leftBound);
//    
//    auto rightBound = BoundNode::createWithSize(right->getContentSize());
//    rightBound->setPosition(right->getPosition());
//    this->addChild(rightBound);

    //rect create -AABB
    auto leftBound = BoundNode::createWithRect(left->getBoundingBox());
    this->addChild(leftBound,0);
    
//    auto rotatedRect = right->getBoundingBox();
//    log("%f %f %f %f",originRect.origin.x, originRect.origin.y, originRect.size.width, originRect.size.height);
//    log("%f %f %f %f",rotatedRect.origin.x, rotatedRect.origin.y, rotatedRect.size.width, rotatedRect.size.height);
    
    //auto rightOriginBound = BoundNode::createWithRect(originRect, Color4F::GREEN);
    //this->addChild(rightOriginBound);

    //auto rightBound = BoundNode::createWithRect(rotatedRect);
    //this->addChild(rightBound);
    
    
    
    //obb
    leftOBB = OBB::createWithNode(left);
    leftOBB->retain();
    rightOBB = OBB::createWithNode(right);
    rightOBB->retain();
    
    
//    Vec2 *originCornerFI = rightOBB->getOriginCorners();
//    Vec2 originCorners[4];
//    originCorners[0] = *originCornerFI;
//    originCorners[1] = *(originCornerFI + 1);
//    originCorners[2] = *(originCornerFI + 2);
//    originCorners[3] = *(originCornerFI + 3);
//    auto rightOriginBound = BoundNode::createWithVectors(originCorners);
//    this->addChild(rightOriginBound);
    
    
    Vec2 *cornerFI = rightOBB->getCorners();
    corners[0] = *cornerFI;
    corners[1] = *(cornerFI + 1);
    corners[2] = *(cornerFI + 2);
    corners[3] = *(cornerFI + 3);
    
    log("length = %ld %ld",(sizeof(corners) / sizeof(Vec2)), (sizeof(corners) / sizeof(corners[0])));
    
//    auto rightObbBound = BoundNode::createWithVectors(corners, Color4F::BLUE);
//    this->addChild(rightObbBound);
    drawNode = DrawNode::create();
    drawNode->drawSegment(corners[0], corners[1], SEGMENT_RADIUS, Color4F::BLUE);
    drawNode->drawSegment(corners[1], corners[2], SEGMENT_RADIUS, Color4F::BLUE);
    drawNode->drawSegment(corners[2], corners[3], SEGMENT_RADIUS, Color4F::BLUE);
    drawNode->drawSegment(corners[3], corners[0], SEGMENT_RADIUS, Color4F::BLUE);
    this->addChild(drawNode,1);
    
    
//    log("***************Hello**********************");
//    log("x:%f y:%f",corners[0].x, corners[0].y);
//    log("x:%f y:%f",corners[1].x, corners[1].y);
//    log("x:%f y:%f",corners[2].x, corners[2].y);
//    log("x:%f y:%f",corners[3].x, corners[3].y);
//    log("***************Hello end******************");
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float ft){
    //log("%d",rightOBB->getReferenceCount());
    //rightOBB->getDescription();
    
    
    rightOBB->isCollision(leftOBB);
}

static int count = 0;
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){
    auto worldPoint = touch->getLocation();
    if (rightOBB->isContainPoint(worldPoint)) {
        count++;
        //log("#################################%d",count);
        return true;
    }
    return false;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event){
    auto moveVec2 = touch->getLocation() - touch->getPreviousLocation();
    right->setPosition(right->getPosition() + moveVec2);
    rightOBB->setNodeCenterPosition(right->getPosition());
    
    //redraw  
    corners[0] += moveVec2;
    corners[1] += moveVec2;
    corners[2] += moveVec2;
    corners[3] += moveVec2;
    rightOBB->setCorners(corners);
    drawNode->clear();
    drawNode->drawSegment(corners[0] , corners[1], SEGMENT_RADIUS, Color4F::BLUE);
    drawNode->drawSegment(corners[1], corners[2], SEGMENT_RADIUS, Color4F::BLUE);
    drawNode->drawSegment(corners[2], corners[3], SEGMENT_RADIUS, Color4F::BLUE);
    drawNode->drawSegment(corners[3], corners[0], SEGMENT_RADIUS, Color4F::BLUE);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event){

}



