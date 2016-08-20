/*
 * Teleport.cpp
 *
 *  Created on: 19-07-2013
 *      Author: michal
 */

#include "Sprites/Objects/Teleport.h"
#include "Common/Resources.h"
#include "GameLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Common\RESPATH.h"


Teleport::Teleport() :
		GameSprite()
{
	this->type = GAME_TYPE_TELEPORT;
	this->currentState = TeleportStateIdle;
	this->direction = GameDirectionUnknown;
	element = 1;
	sequence = 0;
	properities|=PENTERABLE;
	CCPoint p = getTileMapPosition();
	p = GAMEUTILS->ccpTiledAdd(p, ccp(1, 1));
	setTeleportPoints(p, p, p, p);
}

Teleport::~Teleport()
{

}





void Teleport::hit(GameDirection hitDirection, GameSprite* object)
{
	
	CCObject* obj;
	Teleport* nextTeleport = NULL;
	Teleport* firstTeleport = NULL;
	CCARRAY_FOREACH(&GAMEUTILS->objects, obj){
		if (((GameSprite*) obj)->getType() == GAME_TYPE_TELEPORT){
			Teleport* tmpTeleport = (Teleport*) obj;\
			if (tmpTeleport->sequence == this->sequence && tmpTeleport->element == 1){
				firstTeleport = tmpTeleport;
			}
			if (tmpTeleport->sequence == this->sequence && tmpTeleport->element == this->element + 1 ){
				nextTeleport = tmpTeleport;
			}

		}
	}
	if (nextTeleport == NULL){
		nextTeleport = firstTeleport;
	}
	CCPoint p = nextTeleport->getTileMapPosition();
	CCPoint Down = GAMEUTILS->ccpTiledAdd(p, ccp(0, -1));
	CCPoint Up = GAMEUTILS->ccpTiledAdd(p, ccp(0, 1));
	CCPoint Left = GAMEUTILS->ccpTiledAdd(p, ccp(-1, 0));
	CCPoint Right = GAMEUTILS->ccpTiledAdd(p, ccp(1, 0));
	setTeleportPoints(Left, Up, Right, Down);

	
	hitDirection = GAMEUTILS->getOpositeDirection(hitDirection);
	if (object->getType() == GAME_TYPE_ROBBO)
	{
		CCPoint points[4] =
		{ _pointHitUp, _pointHitRight, _pointHitDown , _pointHitLeft };
		CCPoint p;
		bool canteleport = false;
		GameDirection dir = GameDirectionUnknown;
		for(int t = 0; t<=3; t++ )
		{

			p = points[(((int)hitDirection)+t)%4];
			GameSprite* obj = GAMEUTILS->objectAt(p,this );
			if ((! GAMEUTILS->isWallPresent(p)) && obj == NULL)
			{
				canteleport = true;
				dir = (GameDirection) t;
				break;
			}
		}

		//będziem starać sie

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(respatchFix("Sounds/teleport" SOUND_EXT).c_str());
		if(canteleport)
		{
			((Robbo*) object)->setDirection(dir);
			
			

			//GameDirection d = GAMEUTILS->getOpositeDirection(hitDirection);
	
			object->setPosition(nextTeleport->getPosition());

		}
		currentState = TeleportStateIdle;

	}

}

void Teleport::setTeleportPoints(CCPoint pointHitLeft, CCPoint pointHitRight,
		CCPoint pointHitUp, CCPoint pointHitDown)
{
	this->_pointHitDown = pointHitDown;
	this->_pointHitLeft = pointHitLeft;
	this->_pointHitUp = pointHitUp;
	this->_pointHitRight = pointHitRight;
}

void Teleport::applyProperties(CCDictionary* dictionary){
	GameSprite::applyProperties(dictionary);
	element = dictionary->valueForKey("element")->intValue();
	sequence = dictionary->valueForKey("sequence")->intValue();
}