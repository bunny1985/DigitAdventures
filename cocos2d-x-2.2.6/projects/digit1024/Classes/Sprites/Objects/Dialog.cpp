/*
 * Dialog.cpp
 *
 *  Created on: 22 wrz 2014
 *      Author: Michal
 */

#include <Sprites/Objects/Dialog.h>
#include "GameLevelScene.h"

Dialog::Dialog() : Collectable()
{
	;
	colectableType = GAME_TYPE_CollectableTYPE_INFO;


}

Dialog::~Dialog()
{
    // TODO Auto-generated destructor stub
}

void Dialog::applyProperties(CCDictionary* dictionary){
	GameSprite::applyProperties(dictionary);
	const char* a = dictionary->valueForKey("message")->getCString();
	char* iterator = (char*) a;
	while (*iterator  != '\0'){
		if (*iterator == '#' ){
			*iterator = '\n';
			//iterator++;
		}
		iterator++;
	}

	message = a;

	image = dictionary->valueForKey("image")->getCString();

}

void Dialog::hit(GameDirection hitDirection, GameSprite *object){
	if (object->getType() == GAME_TYPE_ROBBO){
		GAMEUTILS->showDialog(message, image);
	}
	getKill();
}

