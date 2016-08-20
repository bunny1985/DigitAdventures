/*
 * QuestionMark.h
 *
 *  Created on: 24-07-2013
 *      Author: michal
 */

#ifndef QUESTIONMARK_H_
#define QUESTIONMARK_H_
#include "Sprites/Objects/Box.h"

class QuestionMark: public Box
{
public:
	QuestionMark();
	virtual ~QuestionMark();
	virtual void getKill();
	virtual void hit(GameDirection hitDirection, GameSprite *object);
	static QuestionMark* create();
};

#endif /* QUESTIONMARK_H_ */
