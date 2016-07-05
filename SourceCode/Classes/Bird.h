#ifndef _BIRD_H_
#define _BIRD_H_

#include"cocos2d.h"

const int BIRD_RADIUS = 15;

class Bird : public cocos2d::Sprite
{
public:
	bool virtual init();
	CREATE_FUNC(Bird);

	cocos2d::RepeatForever *swingAction;	//上下晃动动作
};

#endif

