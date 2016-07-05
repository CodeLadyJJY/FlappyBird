#ifndef _LAND_BODY_H_
#define _LAND_BODY_H_

#include "cocos2d.h"

class LandBody : public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(LandBody);
};

#endif