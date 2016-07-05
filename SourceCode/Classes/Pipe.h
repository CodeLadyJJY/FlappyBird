#ifndef _PIPE_H_
#define _PIPE_H_

#include"cocos2d.h"

const int PIPE_HEIGHT = 320;	//�ܵ��߶�
const int PIPE_WIDTH = 52;		//�ܵ����
const int PIPE_SPACE = 100;		//���¹�֮��ķ�϶
const int PIPE_INTERVAL = 170;	//������������֮��ļ��
const int WAIT_DISTANCE = 380;	//�ȴ�����

class Pipe : public cocos2d::Sprite
{
public:
	static Pipe* createPipe(int type);
	bool virtual init(int type);
};

#endif

