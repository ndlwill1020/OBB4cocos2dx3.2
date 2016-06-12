//
//  OBB.hpp
//  OBBDemo
//
//  Created by macuser on 16/6/6.
//  参考博客：http://blog.csdn.net/tom_221x/article/details/38457757
//

#ifndef OBB_hpp
#define OBB_hpp
#include "cocos2d.h"
USING_NS_CC;

//弧度 radian
//半径 radius


/*
 把2个矩形的半径距离投影到检测轴上
 把2个矩形的中心点连线投影到检测轴上
 判断2个矩形的中心连线投影和2个矩形的半径投影之和的大小
 */

//向量概念：
//单位向量是指模等于1的向量


/// 没有涉及到node的缩放 （涉及的话 改变一些相应的属性即可）
class OBB : public Ref{

public:
    static OBB* createWithNode(Node *node);
    bool initWithNode(Node *node);
    
    bool isContainPoint(const Vec2 &point);
    bool isCollision(OBB *otherOBB);
    
    /***************set && get****************/
    
    //get set
    inline Vec2* getOriginCorners(){
        return originCorners;
    };
    
    
    
    //nodeCenterPosition    set && get
    inline void setNodeCenterPosition(const Vec2 &point){
        this->nodeCenterPosition = point;
//        log("*****************obb set center point****************");
//        log("x:%f y:%f",this->nodeCenterPosition.x, this->nodeCenterPosition.y);
    };
    
    inline Vec2 getNodeCenterPosition(){
        return this->nodeCenterPosition;
    };
    
    //corners[4]      set && get
    inline void setCorners(const Vec2 *corners){
        this->corners[0] = *corners;
        this->corners[1] = *(corners + 1);
        this->corners[2] = *(corners + 2);
        this->corners[3] = *(corners + 3);
        
//        log("*****************obb set corners****************");
//        log("x:%f y:%f",this->corners[0].x, this->corners[0].y);
//        log("x:%f y:%f",this->corners[1].x, this->corners[1].y);
//        log("x:%f y:%f",this->corners[2].x, this->corners[2].y);
//        log("x:%f y:%f",this->corners[3].x, this->corners[3].y);
    };
    
    inline Vec2* getCorners(){
        return corners;
    };
    //nodeSize  set && get
    inline void setNodeSize(const Size &size){
        this->nodeSize = size;
    };
    
    inline Size getNodeSize(){
        return this->nodeSize;
    };
    
    //axes[2]   set && get
    inline Vec2* getAxes(){
        return axes;
    };
    
    /**************************************/
    
    //for test
    inline void getDescription(){
        log("*************OBB*************");
    };
    
    
private:
    OBB();
    ~OBB();
    //一个向量点乘一个单位向量，我们得到的是这个向量在这个单位向量上的投影长度#####
    //向量点乘 a点乘b=|a|×|b|×coc(a,b)几何定义  a点乘b ＝ a.x * b.x + a.y * b.y代数定义
    //b=identityVec为单位向量
    float vectorDotProduct(const Vec2& vec, const Vec2& identityVec);
    
    //当一个向量a为单位向量(大小为1)
    //它的坐标 旋转angle   a=（cos(angle),sin(angle)）//a为mid right
    //因为垂直cos(90度)＝0   所以a点乘b＝0 所以与a垂直的单位向量b为（-sin(angle),cos(angle)）
    void setCheckAxesByRotation(float rotateAngle);
    
    //矩形两条半径投影
    //矩形2条检测轴的向量和就是矩形中心点到矩形一个顶点(拐点)的向量，所以投影半径也是矩形中心点到矩形顶点的向量投影长度
    //核心：2个矩形检测过程中，每次以一个矩形的检测轴为坐标系，投影另一个矩形的检测轴#####
    float getProjectionLength(const Vec2 &identityAxis);
private:
    //矩形的4个拐角点 0:lower left 1:lower right 2:upper right 3:upper left
    Vec2 originCorners[4];//for test
    Vec2 corners[4];//旋转后
    //矩形的2条检测轴的向量坐标（与矩形中心点(0,0)的连线） 0:水平轴
    Vec2 axes[2];//它为单位向量
    
    Vec2 nodeCenterPosition;
    Size nodeSize;
};

#endif /* OBB_hpp */
