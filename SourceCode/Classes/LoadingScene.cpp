#include "LoadingScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	//±³¾°
	auto bg = Sprite::create("splash.png");
	bg->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(bg);
	
	return true;
}

void LoadingScene::onEnter()
{
	//Òì²½¼ÓÔØÍ¼Æ¬
	Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(LoadingScene::jumpToGame, this));
}

void LoadingScene::jumpToGame(Texture2D *texture)
{
	//Ô¤¼ÓÔØÖ¡»º´æÎÆÀí
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", texture);

	//Ô¤¼ÓÔØÖ¡¶¯»­
	auto birdAnimation = Animation::create();
	birdAnimation->setDelayPerUnit(0.2f);
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
	AnimationCache::getInstance()->addAnimation(birdAnimation, "birdAnimation");

	//Ô¤¼ÓÔØÒôÐ§
	SimpleAudioEngine::getInstance()->preloadEffect("die.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("swooshing.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("wing.mp3");

	//³¡¾°Ìø×ª
	auto scene = GameScene::createScene();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}