#include "Pipe.h"

USING_NS_CC;

Pipe* Pipe::createPipe(int type)
{
	Pipe* pRet = new Pipe();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Pipe::init(int type)
{
	if (!Sprite::init())
		return false;

	//if(type == 1)
	//	this->createWithSpriteFrameName("pipe_up.png");
	//else if(type == 2)
	//	this->createWithSpriteFrameName("pipe_down.png");

	auto pipeBody = PhysicsBody::createBox(Size(52, 320));
	pipeBody->setDynamic(false);
	pipeBody->setContactTestBitmask(1);

	this->setTextureRect(Rect(0, 0, 52, 320));
	this->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->setColor(Color3B::GREEN);
	this->setPhysicsBody(pipeBody);

	return true;
}