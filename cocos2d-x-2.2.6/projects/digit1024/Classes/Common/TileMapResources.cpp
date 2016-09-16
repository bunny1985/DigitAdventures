#include "TileMapResources.h"

#include "Sprites/Objects/Box.h"
#include "Sprites/Objects/IceBlock.h"
#include "Sprites/Objects/Teleport.h"
#include "Sprites/Objects/Bomb.h"
#include "Sprites/Objects/Ground.h"
#include "Sprites/Objects/EnterableGround.h"
#include "Sprites/Objects/Doors.h"
#include "Sprites/Objects/Rock.h"
#include "Sprites/Objects/FallingBomb.h"
#include "Sprites/Objects/Collectable.h"
#include "Sprites/Objects/Starship.h"
#include "Sprites/Objects/QuestionMark.h"
#include "Sprites/Objects/FrozenItem.h"
#include "Sprites/Objects/FallingStar.h"
#include "Sprites/Enemies/FourDirectionsEnemy.h"
#include "Sprites/Enemies/Lava.h"
#include "Sprites/Enemies/TwoDirectionsEnemy.h"
#include "Sprites/Enemies/StaticSimpleCannon.h"
#include "Sprites/Enemies/StaticLaserCannon.h"
#include "Sprites/Enemies/RANDOMDIRECTIONeNEMT.h"
#include "Sprites/Enemies/FollowingEnemy.h"
#include "Sprites/Enemies/Magnet.h"
#include "Sprites/Robbo.h"
#include "Sprites/Objects/Dialog.h"
#include <cstdlib>
TileMapResources::TileMapResources()
{
	directortiesDictionary["left"] = GameDirectionLeft;
	directortiesDictionary["right"] = GameDirectionRigh;
	directortiesDictionary["up"] = GameDirectionUp;
	directortiesDictionary["down"] = GameDirectiondDown;


	factoriesDictionary[0] = new GameSpriteFactory<Ground>();
	factoriesDictionary[1] = new GameSpriteFactory<EnterableGround>();
	factoriesDictionary[2] = new GameSpriteFactory<Box>();
	factoriesDictionary[3] = new GameSpriteFactory<Bomb>();
	factoriesDictionary[4] = new GameSpriteFactory<Teleport>();


	factoriesDictionary[10] = new GameSpriteFactory<Doors>();
	factoriesDictionary[11] = new GameSpriteFactory<Rock>();
	factoriesDictionary[12] = new GameSpriteFactory<Starship>();
	factoriesDictionary[13] = new GameSpriteFactory<IceBlock>();
	factoriesDictionary[14] = new GameSpriteFactory<Lava>();
	factoriesDictionary[22] = new GameSpriteFactory<FallingBomb>();
	factoriesDictionary[21] = new GameSpriteFactory<FallingStar>();


	factoriesDictionary[30] = new GameSpriteFactory<CollectableStar>();
	factoriesDictionary[31] = new GameSpriteFactory<CollectableKey>();
	factoriesDictionary[32] = new GameSpriteFactory<CollectableAmmo>();



	factoriesDictionary[40] = new GameSpriteFactory<Robbo>();


	factoriesDictionary[7] = new GameSpriteFactory<TwoDirectionsEnemy_UP>();
	factoriesDictionary[17] = new GameSpriteFactory<TwoDirectionsEnemy_RIGHT>();
	factoriesDictionary[27] = new GameSpriteFactory<TwoDirectionsEnemy_DOWN>();
	factoriesDictionary[37] = new GameSpriteFactory<TwoDirectionsEnemy_LEFT>();


	factoriesDictionary[8] = new GameSpriteFactory<FourDirectionsEnemy_UP>();
	factoriesDictionary[18] = new GameSpriteFactory<FourDirectionsEnemy_RIGHT>();
	factoriesDictionary[28] = new GameSpriteFactory<FourDirectionsEnemy_DOWN>();
	factoriesDictionary[38] = new GameSpriteFactory<FourDirectionsEnemy_LEFT>();


	factoriesDictionary[6] = new GameSpriteFactory<StaticSimpleCannon_UP>();
	factoriesDictionary[16] = new GameSpriteFactory<StaticSimpleCannon_RIGHT>();
	factoriesDictionary[26] = new GameSpriteFactory<StaticSimpleCannon_DOWN>();
	factoriesDictionary[36] = new GameSpriteFactory<StaticSimpleCannon_LEFT>();
	factoriesDictionary[46] = new GameSpriteFactory<StaticSimpleCannonRotating>();

	factoriesDictionary[5] = new GameSpriteFactory<StaticLaserCannon_UP>();
	factoriesDictionary[15] = new GameSpriteFactory<StaticLaserCannon_RIGHT>();
	factoriesDictionary[25] = new GameSpriteFactory<StaticLaserCannon_DOWN>();
	factoriesDictionary[35] = new GameSpriteFactory<StaticLaserCannon_LEFT>();
	factoriesDictionary[45] = new GameSpriteFactory<StaticLaserCannonRotating>();




	factoriesDictionary[47] = new GameSpriteFactory<MagnetEnemy_Up>();
	factoriesDictionary[57] = new GameSpriteFactory<MagnetEnemy_Right>();
	factoriesDictionary[67] = new GameSpriteFactory<MagnetEnemy_Down>();
	factoriesDictionary[77] = new GameSpriteFactory<MagnetEnemy_Left>();



	factoriesDictionary[9] = new GameSpriteFactory<FollowingEnemy>();
	factoriesDictionary[19] = new GameSpriteFactory<RandomDirectionEnemy>();



	factoriesDictionary[29] = new GameSpriteFactory<frozenBomb>();
	factoriesDictionary[39] = new GameSpriteFactory<frozenAmmo>();
	factoriesDictionary[49] = new GameSpriteFactory<frozenScrew>();
	factoriesDictionary[59] = new GameSpriteFactory<frozenBox>();
	factoriesDictionary[69] = new GameSpriteFactory<frozenKey>();
	factoriesDictionary[79] = new GameSpriteFactory<frozenRock>();
	factoriesDictionary[89] = new GameSpriteFactory<frozenStarship>();


	factoriesDictionary[99] = new GameSpriteFactory<Dialog>();

}


TileMapResources::~TileMapResources()
{
	std::map<int, IGameSpriteFactory*>::iterator iterator;
	for (iterator = factoriesDictionary.end(); iterator != factoriesDictionary.begin(); iterator--) {

	//	CC_SAFE_DELETE(iterator->second);
	}
}
