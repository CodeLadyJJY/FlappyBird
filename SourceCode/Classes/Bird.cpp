#include"Bird.h"

USING_NS_CC;

bool Bird::init() 
{
	if (!Sprite::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	//�ӳᶯ��
	auto animate = Animate::create(AnimationCache::getInstance()->animationByName("birdAnimation"));
	this->runAction(RepeatForever::create(animate));

	//���»ζ�����
	auto up = MoveBy::create(0.4f, Point(0, 8));
	auto upBack = up->reverse();
	swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));
	this->runAction(swingAction);

	//���ø���
	this->setPhysicsBody(PhysicsBody::createCircle(BIRD_RADIUS));
	this->getPhysicsBody()->setContactTestBitmask(1);
	this->getPhysicsBody()->setGravityEnable(false);
	this->setPosition(size / 2);

	return true;
}