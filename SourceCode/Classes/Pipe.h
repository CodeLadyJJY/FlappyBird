#ifndef _PIPE_H_
#define _PIPE_H_

#include"cocos2d.h"

const int PIPE_HEIGHT = 320;	//管道高度
const int PIPE_WIDTH = 52;		//管道宽度
const int PIPE_SPACE = 100;		//上下管之间的缝隙
const int PIPE_INTERVAL = 170;	//横向两根管子之间的间距
const int WAIT_DISTANCE = 380;	//等待距离

class Pipe : public cocos2d::Sprite
{
public:
	static Pipe* createPipe(int type);
	bool virtual init(int type);
};

#endif

