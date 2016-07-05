#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "Bird.h"

enum GAME_STATUS  //游戏状态,准备，开始，结束
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

	Bird *bird;								//小鸟
	cocos2d::Vector<Node*> pipes;			//管道
	GAME_STATUS gameStatus;					//游戏状态
	void gameStart();						//游戏开始
	void gameOver();						//游戏结束
	void gameRetart(cocos2d::Ref *sender);	//按钮回调函数
	virtual void update(float t);			//更新函数

private:
	cocos2d::Size size;				//窗口大小
	cocos2d::Sprite *land1;			//陆地1
	cocos2d::Sprite *land2;			//陆地2
	cocos2d::Label *scoreLabel;		//分数板
	int score;						//当前分数
	int bestScore;					//最高分数
	void scrollLand(float dt);		//滚动陆地
	void createPipes();				//创建管子
	void scorePanel();				//创建分数板
};

#endif