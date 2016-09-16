#include "Sprites/Enemies/TwoDirectionsEnemy.h"

#ifndef RandomDirectionEnemy_H_
#define RandomDirectionEnemy_H_


class RandomDirectionEnemy : public TwoDirectionsEnemy
{
public:
	RandomDirectionEnemy();
	virtual ~RandomDirectionEnemy();
	SPRITECREATION("enemy4.png", RandomDirectionEnemy);
	virtual GameDirection pickDirection();
	virtual bool canBeMoved(GameDirection direction);
	void fixPosition();
};
#endif

