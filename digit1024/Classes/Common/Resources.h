/*
 * Resources.h
 *
 *  Created on: 16-07-2013
 *      Author: michal
 */
#ifndef WINDOWS
 #define SOUND_EXT ".ogg"
#endif
#ifndef RESOURCES_H_
#define RESOURCES_H_

#define MUSIC_FILE_EXT ".ogg"
#define GRAPHICS_ROBBO_idle "ROBBO_stay.png"
#define GRAPHICS_ROBBO_go_left "robbo_left%i.png"
#define GRAPHICS_ROBBO_go_right "robbo_right%i.png"
#define GRAPHICS_ROBBO_go_up ("robbo_up%i.png")
#define GRAPHICS_ROBBO_go_down ("robbo_down%i.png")

#define GAME_CONSTS_ROBBO_moving_animation_length (1)
#define GAME_CONSTS_ROBBO_moving_animation_speed (10)
#define GAME_MENU_FONT_FILE ("fonts/konqa32.fnt")
#define GAME_MENU_FONTHD_FILE ("fonts/konqa32hd.fnt")

#define GAME_TYPE_ROBBO (0)
#define GAME_TYPE_BOX (1)
#define GAME_TYPE_WALL (2)
#define GAME_TYPE_GROUND (3)
#define GAME_TYPE_TELEPORT (4)
#define GAME_TYPE_ENEMY (5)
#define GAME_TYPE_ENEMY_Two_ways (0)
#define GAME_TYPE_ENEMY_four_ways (1)
#define GAME_TYPE_ENEMY_Cannon_laser_fire (2)
#define GAME_TYPE_ENEMY_Cannon_normal_fire (3)
#define GAME_TYPE_ENEMY_Follower (4)
#define GAME_TYPE_BULLET (6)
#define GAME_TYPE_QUESTIONMARK (7)
#define GAME_TYPE_BOMB (8)
#define GAME_TYPE_Door (9)
#define GAME_TYPE_Collectable (10)
#define GAME_TYPE_CollectableTYPE_SCREW (0)
#define GAME_TYPE_CollectableTYPE_KEY (1)
#define GAME_TYPE_CollectableTYPE_LIFE (2)
#define GAME_TYPE_CollectableTYPE_AMMO (3)
#define GAME_TYPE_CollectableTYPE_INFO (4)
#define GAME_TYPE_STRARSHIP (11)
#define GAME_TYPE_Magnet (12)
#define GAME_TYPE_FORCE_FIELD (13)
#define GAME_TYPE_ENTERABLEGROUND (14)
#define GAME_TYPE_ROCK (15)
#define GAME_TYPE_SWITCH (16)




//SETTINGS KEYS
#define SETTINGSLASTLEVEL ("lastlevel")
#define SETTINGSMAXLEVEL ("maxlevel")
#define SETTINGSLIVESLEFT ("livesleft")
#define SETTINGSMUSICVOLUME ("musicvolume")
#define SETTINGSOUNDSVOLUME ("soundvolume")
#define SETTINGSCONTROLMODE ("controlmode")





#define DefinedTypes (15)

class Resources
{
public:
	Resources();
	virtual ~Resources();
};

#endif /* RESOURCES_H_ */
