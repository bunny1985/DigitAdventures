/*
 * ObjectsFactory.cpp
 *
 *  Created on: 21-07-2013
 *      Author: michal
 */

#include "ObjectsFactory.h"
#include "Common/Resources.h"
#include "Sprites/Objects/Box.h"
#include "Sprites/Objects/Teleport.h"

#include "Sprites/Objects/Bomb.h"
#include "Sprites/Objects/Ground.h"
#include "Sprites/Objects/EnterableGround.h"
#include "Sprites/Objects/Doors.h"
#include "Sprites/Objects/Rock.h"
#include "Sprites/Objects/Collectable.h"
#include "Sprites/Objects/Starship.h"
#include "Sprites/Objects/QuestionMark.h"
#include "Sprites/Enemies/FourDirectionsEnemy.h"
#include "Sprites/Enemies/TwoDirectionsEnemy.h"
#include "Sprites/Enemies/StaticSimpleCannon.h"
#include "Sprites/Enemies/StaticLaserCannon.h"
#include "Sprites/Robbo.h"
#include "GameLevelScene.h"

#include <cstdlib>

ObjectsFactory::ObjectsFactory() {
	srand(time(0));
	// TODO Auto-generated constructor stub

}

ObjectsFactory::~ObjectsFactory() {
	// TODO Auto-generated destructor stub
}

GameSprite* ObjectsFactory::createObject(CCDictionary* properties) {
	CCString *type = getValue(properties, "type");
	int x = getValue(properties, "x")->intValue();
	int y = getValue(properties, "y")->intValue();
	GameSprite *obj;

	int typeGid = validateIntRange(1, DefinedTypes, type);
	CCLog("TYPEgid %i ", typeGid);

	switch (typeGid) {
	case GAME_TYPE_BOX:
		CCLOG("Adding BOX");
		obj = Box::create();
		setPosition(obj, x, y);
		break;
	case GAME_TYPE_TELEPORT:
		CCLOG("Adding TELEPORT");
		obj = Teleport::create();
		((Teleport*) obj)->setTeleportPoints(
				ccp(getValue(properties , "leftx")->intValue() ,getValue(properties , "lefty")->intValue() ),
		ccp(getValue(properties , "rightx")->intValue() ,getValue(properties , "righty")->intValue() ) ,
		ccp(getValue(properties , "upx")->intValue() ,getValue(properties , "upy")->intValue() ),
		ccp(getValue(properties , "downx")->intValue() ,getValue(properties , "downy")->intValue() )
		);
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_ROCK:
			CCLOG("Adding Rock");
			obj = Rock::create();
			setPosition(obj, x, y);
			break;
		case GAME_TYPE_STRARSHIP:
		CCLOG("Adding Starship");
		obj = Starship::create();
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_BOMB:
		CCLOG("Adding Bomb");
		obj = Bomb::create();
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_GROUND:
		CCLOG("Adding Ground");
		obj = Ground::create();
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_ENTERABLEGROUND:
		CCLOG("Adding  EnterableGround");
		obj = EnterableGround::create();
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_Door:
		CCLOG("Adding Door");
		obj = Doors::create();
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_Collectable:
		CCLOG("Adding Colectable");
		obj = Collectable::create(validateIntRange(0 , 3 , getValue(properties, "c_type")) ,validateIntRange(0 , 9 , getValue(properties, "c_quantity")) );
		setPosition(obj, x, y);
		break;
		case GAME_TYPE_ENEMY:
		CCLOG("Adding Enemy");
		obj = createEnemy(properties);

		break;
		case GAME_TYPE_QUESTIONMARK:
		CCLOG("Adding QuestionMark");
		obj = QuestionMark::create();
		setPosition(obj, x, y);

		CCLOG("Adding QUESTONMARK");
		break;
		case GAME_TYPE_ROBBO:
		obj = GAMEUTILS->robboSprite;
		setPosition(obj, x, y);
		CCLOG("Adding ROBBO");
		break;
		default:
		return NULL;
		break;
	}

	return obj;
}

GameSprite* ObjectsFactory::createEnemy(CCDictionary* properties) {
//
	int x = getValue(properties, "x")->intValue();
	int y = getValue(properties, "y")->intValue();

	int enemytype = validateIntRange(0, 3, getValue(properties, "enemy_type"));

	int direction = validateIntRange(0, 3, getValue(properties, "direction"));
	if (enemytype == GAME_TYPE_ENEMY_Two_ways) {
		CCLOG("Adding Enemy two directions");
		TwoDirectionsEnemy * enemy = TwoDirectionsEnemy::create();
		enemy->setDirection((GameDirection) direction);
		setPosition(enemy, x, y);

		return enemy;
	}
	else if (enemytype == GAME_TYPE_ENEMY_four_ways)
	{
		CCLOG("Adding Enemy four directions");
		int turn = validateIntRange(-1, 1, getValue(properties, "turn"));
		FourDirectionsEnemy * enemy = FourDirectionsEnemy::create();
		enemy->setTurn(turn);
		enemy->setDirection((GameDirection) direction);
		setPosition(enemy, x, y);

		return enemy;
	}
	else if (enemytype == GAME_TYPE_ENEMY_Cannon_normal_fire)
	{
		CCLOG("Adding Enemy cannon Simple static");
		StaticSimpleCannon * enemy = StaticSimpleCannon::create();
		enemy->setShotingDirection((GameDirection) direction);
		enemy->setDirection((GameDirection) direction);

		int frequency = validateIntRange(0, 10, getValue(properties, "shoot_frequency"));
		enemy->setShootFrequency(frequency);
		setPosition(enemy, x, y);
		return enemy;
}
	else if (enemytype == GAME_TYPE_ENEMY_Cannon_laser_fire)
	{
		CCLOG("Adding Enemy cannon LASER");
		StaticSimpleCannon * enemy = StaticLaserCannon::create();
		enemy->setShotingDirection((GameDirection) direction);
		enemy->setDirection((GameDirection) direction);

		int frequency = validateIntRange(0, 10, getValue(properties, "shoot_frequency"));
		enemy->setShootFrequency(frequency);
		setPosition(enemy, x, y);
		return enemy;

	}
		return NULL;

	}

int ObjectsFactory::validateIntRange(int minValue, int maxValue,
		CCString* value)
{

	if (value != NULL && value->length() != 0)
	{

		return value->intValue();
	}
	else
	{

		int d = maxValue - minValue;

		return std::rand() % d + minValue;

	}
}

void ObjectsFactory::setPosition(GameSprite* obj, int x, int y)
{
	if (obj)
	{
		//TODO do zmiany  an tile width i height
		obj->setPosition(
				ccp (x+ 40 , y +40 ));
		CCLog("Set at pos %i, %i " ,x, y);
	}
}

CCString* ObjectsFactory::getValue(CCDictionary* properties, const char* key)
{

	CCString *value = (CCString*) properties->valueForKey(key);
	return value;

}

