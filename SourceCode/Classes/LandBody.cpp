#include "LandBody.h"

USING_NS_CC;

bool LandBody::init()
{
	if (!Node::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	//陆地刚体
	auto groundBody = PhysicsBody::createBox(Size(size.width, 108));
	groundBody->setDynamic(false);
	groundBody->setContactTestBitmask(1);

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE); //物理引擎中的刚体只允许结点锚点设置为中心
	this->setPhysicsBody(groundBody);
	this->setPosition(size.width / 2, 108 / 2);

	return true;
}