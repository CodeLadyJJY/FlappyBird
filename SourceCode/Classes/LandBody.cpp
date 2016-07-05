#include "LandBody.h"

USING_NS_CC;

bool LandBody::init()
{
	if (!Node::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	//½�ظ���
	auto groundBody = PhysicsBody::createBox(Size(size.width, 108));
	groundBody->setDynamic(false);
	groundBody->setContactTestBitmask(1);

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE); //���������еĸ���ֻ������ê������Ϊ����
	this->setPhysicsBody(groundBody);
	this->setPosition(size.width / 2, 108 / 2);

	return true;
}