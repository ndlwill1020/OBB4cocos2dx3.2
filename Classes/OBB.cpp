//
//  OBB.cpp
//  OBBDemo
//
//  Created by macuser on 16/6/6.
//
//

#include "OBB.hpp"

OBB::OBB(){

}

OBB::~OBB(){

}

OBB* OBB::createWithNode(Node *node){
    OBB *obb = new (std::nothrow) OBB();
    if (obb && obb->initWithNode(node)) {
        obb->autorelease();
    } else {
        CC_SAFE_DELETE(obb);
    }
    return obb;
}

//得到node的坐标在世界坐标
bool OBB::initWithNode(Node *node){
    nodeSize = node->getContentSize();
    nodeCenterPosition = node->getPosition();//锚点在中心点
    auto rotateAngle= node->getRotation();
//    log("width:%f height:%f",nodeSize.width, nodeSize.height);
//    log("x:%f y:%f",nodeCenterPosition.x, nodeCenterPosition.y);
//    log("angle:%f",rotateAngle);
    
    this->setCheckAxesByRotation(rotateAngle);//得到的是单位向量的坐标（归一化的坐标）
    
    
    //得到实际坐标  归一化的坐标->实际坐标
//    Vec2 x = axes[0] * (nodeSize.width / 2);//水平轴向量
//    Vec2 y = axes[1] * (nodeSize.height / 2);
    
    
    originCorners[0] = Vec2(nodeCenterPosition.x - nodeSize.width / 2, nodeCenterPosition.y - nodeSize.height / 2);
    originCorners[1] = Vec2(nodeCenterPosition.x + nodeSize.width / 2, nodeCenterPosition.y - nodeSize.height / 2);
    originCorners[2] = Vec2(nodeCenterPosition.x + nodeSize.width / 2, nodeCenterPosition.y + nodeSize.height / 2);
    originCorners[3] = Vec2(nodeCenterPosition.x - nodeSize.width / 2, nodeCenterPosition.y + nodeSize.height / 2);
    
    corners[0] = originCorners[0].rotateByAngle(nodeCenterPosition, CC_DEGREES_TO_RADIANS(-rotateAngle));
    corners[1] = originCorners[1].rotateByAngle(nodeCenterPosition, CC_DEGREES_TO_RADIANS(-rotateAngle));
    corners[2] = originCorners[2].rotateByAngle(nodeCenterPosition, CC_DEGREES_TO_RADIANS(-rotateAngle));
    corners[3] = originCorners[3].rotateByAngle(nodeCenterPosition, CC_DEGREES_TO_RADIANS(-rotateAngle));
    
    
//    log("***********obb init corners************");
//    log("x:%f y:%f",corners[0].x, corners[0].y);
//    log("x:%f y:%f",corners[1].x, corners[1].y);
//    log("x:%f y:%f",corners[2].x, corners[2].y);
//    log("x:%f y:%f",corners[3].x, corners[3].y);
//    log("***************init end*****************");
    
    return true;
}

float OBB::vectorDotProduct(const Vec2& vec, const Vec2& identityVec){
    return std::abs((vec.x * identityVec.x + vec.y * identityVec.y));
}

//以nodeCenterPosition为（0，0）点 作为参考###
void OBB::setCheckAxesByRotation(float rotateAngle){
    axes[0] = Vec2(cosf(rotateAngle), sinf(rotateAngle));//水平
    //水平与垂直的夹角90度
    axes[1] = Vec2(-sinf(rotateAngle), cosf(rotateAngle));//垂直
}

bool OBB::isContainPoint(const Vec2 &point){
    bool isContain = false;
    auto localPoint = point - nodeCenterPosition;//转换到以nodeCenterPosition为原点的坐标
    if ((this->vectorDotProduct(localPoint, axes[0]) <= nodeSize.width / 2) && (this->vectorDotProduct(localPoint, axes[1]) <= nodeSize.height / 2)) {
        isContain = true;
    }
    
    return isContain;
}

//得到两条检测轴在以另一个矩形的检测轴为坐标系上面的投影长度
float OBB::getProjectionLength(const Vec2 &identityAxis){
    float projectAxisX = this->vectorDotProduct(axes[0], identityAxis);
    float projectAxisY = this->vectorDotProduct(axes[1], identityAxis);
    return projectAxisX * nodeSize.width / 2 + projectAxisY * nodeSize.height / 2;
}

//判断2矩形最终是否碰撞，需要依次检测4个分离轴，如果在一个轴上没有碰撞，则2个矩形就没有碰撞
bool OBB::isCollision(OBB *otherOBB){
    bool isCollision = true;
    //得到两个矩形中心点的距离向量(差值向量 在同一坐标系的差值)
    Vec2 centerDistanceVector = Vec2(this->nodeCenterPosition.x - otherOBB->nodeCenterPosition.x, this->nodeCenterPosition.y - otherOBB->nodeCenterPosition.y);
    
    //4条检测轴 都是单位向量
    Vec2 allAxes[4] = {axes[0], axes[1], *(otherOBB->getAxes()), *(otherOBB->getAxes() + 1)};
    
    for (int i = 0; i < (sizeof(allAxes) / sizeof(allAxes[0])); i++) {
        //中心点连线的投影长度与2矩形的半径投影长度之和，如果连线投影大，那么在这条轴上没有碰撞，否则碰撞  (这边的等于号看情况而定)
        if (this->getProjectionLength(allAxes[i]) + otherOBB->getProjectionLength(allAxes[i]) <= this->vectorDotProduct(centerDistanceVector, allAxes[i])) {
            isCollision = false;
            log("###########################no collision");
            return isCollision;
        }
    }
    log("###########################collision");
    return isCollision;
}