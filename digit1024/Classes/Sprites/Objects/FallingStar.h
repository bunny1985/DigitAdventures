

#ifndef FALLINGSTAR_H_
#define FALLINGSTAR_H_

#include "Rock.h"
#include "Common\Enums.h"

class FallingStar: public Rock{
public:
	SPRITECREATION("FallingScrew.png", FallingStar)
	FallingStar();
	void hit(GameDirection hitDirection, GameSprite* object);
	virtual void getKill();
	virtual void onGetKill();
	bool pushed(GameDirection direction){ return true; }
	bool canBeMoved(GameDirection direction);

};

#endif
