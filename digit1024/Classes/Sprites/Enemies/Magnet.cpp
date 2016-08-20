#include "Magnet.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "CCShake.h"

GameDirection MagnetEnemy::pickDirection(){
	return direction;
}

void MagnetEnemy::setDirection(GameDirection direction){
	AbstractEnemy::setDirection(direction);
	runAction(CCRotateTo::create(0.3, (int) direction * 90));
}
void MagnetEnemy::update(){
	CCPoint prevPos = getTileMapPosition();
	int i = 0;
	CCPoint nextPoint = GAMEUTILS->ccpTiledAdd(prevPos, GAMEUTILS->getTiledVectorFromDirection(direction));
	GameSprite* obj = NULL;
	while (!GAMEUTILS->isWallPresent(nextPoint) && !(obj = GAMEUTILS->objectAt(nextPoint, this)))
	{
		
		prevPos = nextPoint;
		nextPoint = GAMEUTILS->ccpTiledAdd(prevPos, GAMEUTILS->getTiledVectorFromDirection(direction));
		i++;
	}
	if (i != fieldCount){
		field->setTextureRect(CCRect(0, 0, 80, i * 80));
		fieldCount = i;
	}
	if (obj && obj->getType() == GAME_TYPE_ROBBO){
		obj->getKill();
	}
	


	
}
MagnetEnemy::MagnetEnemy() : AbstractEnemy()
{
	properities &= (~PSHOOTABLE);
	properities &= (~PENTERABLE);
	properities &= (~PPUSHABLE);
	
	

}
GameSprite* MagnetEnemy::postCreate(const char* framename){
	GameSprite::postCreate(framename);
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("magnet_fielsd.png");
	ccTexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	texture->setTexParameters(&tp);
	field = CCSprite::createWithTexture(texture, CCRectMake(0, 0, 80, 80));
	field->setAnchorPoint(ccp(0, 0));
	field->setPositionY(80);
	
	field->setAnchorPoint(ccp(0, 0));
	field->setPositionY(80);
	//field->setOpacity(0.3);
	//field->setZOrder(-1);
	this->addChild(field);
	return this;
}