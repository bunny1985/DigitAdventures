/*
 * Dialog.h
 *
 *  Created on: 22 wrz 2014
 *      Author: Michal
 */

#ifndef DIALOG_H_
#define DIALOG_H_

#include "Collectable.h"

class Dialog :public Collectable
{
public:
	SPRITECREATION("dialog.png", Dialog);

	//REDEFINED:
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	virtual void applyProperties(CCDictionary* dictionary);

    Dialog();
    virtual ~Dialog();
private:
	const char* message;
	const char* image;

};

#endif /* DIALOG_H_ */
