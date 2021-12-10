#ifndef LEVEL_H
#define LEVEL_H

//Includes
#include <ultra64.h>
#include <nusys.h>
#include "gfx.h"
#include "afx.h"

//Variables
u8 levelNum,areaNum;
u16 * levelBgImage;
u16 ** levelTileset;
u8 * levelTsProps;
u8 * levelTilemap;
u32 levelWidth,levelHeight;
T_LevelActor * levelActors;
u8 levelActorStatus[0x100];
u8 levelSwitchStatus[0x40];
typedef struct {
	//Actor type
	u16 id;
	u8 param;
	u8 inited;
	//Actor position info
	s32 x,y;
	s32 vx,vy;
	//Actor collision info
	int cx1,cy1,cx2,cy2;
	//Actor animation info
	u8 sprMode,sprLayer;
	u16 sprId;
	u16 animFrame,animTimer;
	//Actor-use temporaries
	int temps[4];
	//Link to level data index
	u16 link;
	u8 status;
} T_Actor;
T_Actor actorList[0x100];
T_Actor * actPlayer;
u8 playerLives;
u8 playerHP;
u16 playerMode;
u32 playerScore;
u8 playerPlatFlag;
T_Actor * playerPlat;
s32 playerPlatVX,playerPlatVY;

//Functions
void clear_level();
void load_level();
void update_level();

#endif
