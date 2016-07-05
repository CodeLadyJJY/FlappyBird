#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "LandBody.h"
#include "Pipe.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene * GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);	//����ģʽ
	scene->getPhysicsWorld()->setGravity(Vect(0, -1000));						//��������

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	size = Director::getInstance()->getWinSize();
	gameStatus = GAME_READY;
	srand(time(NULL));

	//����
	auto bg = Sprite::createWithSpriteFrameName("bg.png");
	bg->setPosition(size / 2);
	this->addChild(bg);

	//logo
	auto gameLogo = Sprite::createWithSpriteFrameName("bird_logo.png");
	gameLogo->setPosition(size.width / 2, size.height *3 / 4);
	gameLogo->setName("logo");
	this->addChild(gameLogo);

	//������
	scoreLabel = Label::createWithSystemFont("0", "Consolas", 30);
	scoreLabel->setPosition(size.width / 2, size.height * 7 / 8);
	scoreLabel->setVisible(false);
	this->addChild(scoreLabel, 10);

	//С��
	bird = Bird::create();
	this->addChild(bird);
	
	//�ܵ�
	createPipes();

	//½��
	land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setAnchorPoint(Point::ZERO);
	land1->setPosition(Point::ZERO);
	this->addChild(land1, 10);  //�������

	land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setAnchorPoint(Point::ZERO);
	land2->setPosition(Point::ZERO);
	this->addChild(land2, 10);

	//½�ظ���
	auto landBody = LandBody::create();
	this->addChild(landBody);

	//��������
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [&](Touch *t, Event *e)
	{
		switch (gameStatus)
		{
		case GAME_READY:
			this->gameStart();
			bird->getPhysicsBody()->setGravityEnable(true);
			SimpleAudioEngine::getInstance()->playEffect("wing.mp3");
			break;
		case GAME_START:
			bird->getPhysicsBody()->setVelocity(Vec2(0,250));
			SimpleAudioEngine::getInstance()->playEffect("wing.mp3");
			break;
		default:
			break;
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//��ײ����
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [&](PhysicsContact &contact)
	{
		if (gameStatus == GAME_OVER)
			return false;

		gameOver();

		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

//��Ϸ��ʼ
void GameScene::gameStart()
{
	gameStatus = GAME_START;
	score = 0;
	this->getChildByName("logo")->setVisible(false);
	scoreLabel->setVisible(true);
	bird->stopAction(bird->swingAction);
	this->schedule(schedule_selector(GameScene::scrollLand), 0.01f);
	this->scheduleUpdate();
}

//��Ϸ����
void GameScene::gameOver()
{
	gameStatus = GAME_OVER;
	bestScore = UserDefault::getInstance()->getIntegerForKey("BEST");
	if (score > bestScore)
	{
		bestScore = score;
		UserDefault::getInstance()->setIntegerForKey("BEST", bestScore);
	}
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	this->unschedule(schedule_selector(GameScene::scrollLand));
}

//��Ϸ���¿�ʼ
void GameScene::gameRetart(Ref *sender)
{
	auto scene = GameScene::createScene();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void GameScene::scrollLand(float dt) {
	//����½��ѭ���ƶ�
	land1->setPositionX(land1->getPositionX() - 1.0f);
	land2->setPositionX(land1->getPositionX() + land1->getContentSize().width - 2.0f);
	if (land2->getPositionX() <= 0)
		land1->setPosition(Point::ZERO);

	//���ӹ���
	for (auto &singlePipe : pipes)
	{
		singlePipe->setPositionX(singlePipe->getPositionX() - 1.0f);
		if (singlePipe->getPositionX() < - PIPE_WIDTH / 2)
		{
			singlePipe->setPositionX(size.width + PIPE_WIDTH / 2);
			singlePipe->setPositionY(rand() % 200 + 40);
			singlePipe->setName("newPipe");  //ÿ������һ�����ӣ���Ϊnew
		}
	}

	//����÷�
	if (gameStatus == GAME_START)
	{
		for (auto *pipe : pipes)
		{
			if (pipe->getName() == "newPipe" && pipe->getPositionX() < bird->getPositionX())
			{
				score++;
				scoreLabel->setString(StringUtils::format("%d", score));
				SimpleAudioEngine::getInstance()->playEffect("point.mp3");
				pipe->setName("passed");
			}
		}
	}

	//С����ת
	auto curVelocity = bird->getPhysicsBody()->getVelocity();
	bird->setRotation(-curVelocity.y * 0.1 - 15);
}

void GameScene::update(float t)
{
	//С��������������
	if (bird->getPositionY() <= land1->getContentSize().height + BIRD_RADIUS)
	{
		bird->stopAllActions();
		bird->setRotation(90);
		bird->getPhysicsBody()->setDynamic(false);
		SimpleAudioEngine::getInstance()->playEffect("die.mp3");
		this->unscheduleUpdate();
		scoreLabel->setVisible(false);
		scorePanel();
	}
}

//����ˮ��
void GameScene::createPipes()
{
	for (int i = 0; i < 2; ++i)
	{
		auto pipeup = Pipe::createPipe(1);
		auto pipedown = Pipe::createPipe(2);

		pipeup->setPosition(0, PIPE_HEIGHT + PIPE_SPACE);
		
		auto singlePipe = Node::create();
		singlePipe->addChild(pipeup);
		singlePipe->addChild(pipedown);
		singlePipe->setPosition(i * PIPE_INTERVAL + WAIT_DISTANCE, rand() % 200 + 40);
		singlePipe->setName("newPipe");
		this->addChild(singlePipe);

		pipes.pushBack(singlePipe);
	}
}

void GameScene::scorePanel()
{
	//��Ϸ����logo
	auto gameOver = Sprite::createWithSpriteFrameName("gameover.png");
	gameOver->setPosition(size.width / 2, size.height * 6 / 8);
	this->addChild(gameOver);

	//������
	auto panel = Sprite::createWithSpriteFrameName("board.PNG");
	panel->setPosition(size.width / 2, size.height / 2);
	this->addChild(panel);

	//��ǰ����
	auto curScoreLabel = Label::createWithSystemFont(StringUtils::format("%d", score), "Consolas", 25);
	curScoreLabel->setPosition(size.width *3 / 4, size.height * 16 / 30);
	this->addChild(curScoreLabel);

	//��߷���
	auto bestScoreLabel = Label::createWithSystemFont(StringUtils::format("%d", bestScore), "Consolas", 25);
	bestScoreLabel->setPosition(size.width * 3 / 4, size.height * 13 / 30);
	this->addChild(bestScoreLabel);

	//���¿�ʼ��ť
	auto restartBtn = Sprite::createWithSpriteFrameName("start_btn.png");
	auto restartBtnActive = Sprite::createWithSpriteFrameName("start_btn_pressed.png");

	auto restartItem = MenuItemSprite::create(restartBtn, restartBtnActive, NULL, CC_CALLBACK_1(GameScene::gameRetart, this));
	auto menu = Menu::create(restartItem, NULL);
	menu->setPosition(size.width / 2, size.height * 5 / 16);
	this->addChild(menu);
}