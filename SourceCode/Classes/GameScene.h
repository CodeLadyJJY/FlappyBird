#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "Bird.h"

enum GAME_STATUS  //��Ϸ״̬,׼������ʼ������
{
	GAME_READY,
	GAME_START,
	GAME_OVER
};

class GameScene : public cocos2d::Layer
{
public :
	static cocos2d::Scene * createScene();
	bool virtual init();
	CREATE_FUNC(GameScene);

	Bird *bird;								//С��
	cocos2d::Vector<Node*> pipes;			//�ܵ�
	GAME_STATUS gameStatus;					//��Ϸ״̬
	void gameStart();						//��Ϸ��ʼ
	void gameOver();						//��Ϸ����
	void gameRetart(cocos2d::Ref *sender);	//��ť�ص�����
	virtual void update(float t);			//���º���

private:
	cocos2d::Size size;				//���ڴ�С
	cocos2d::Sprite *land1;			//½��1
	cocos2d::Sprite *land2;			//½��2
	cocos2d::Label *scoreLabel;		//������
	int score;						//��ǰ����
	int bestScore;					//��߷���
	void scrollLand(float dt);		//����½��
	void createPipes();				//��������
	void scorePanel();				//����������
};

#endif