#include "level.h"

/////////////////
//LEVEL LOADING//
/////////////////
//LEVEL DATA POINTERS
typedef struct {
	u16 * bgImg;
	u16 ** tileset;
	u8 * tsProps;
	u8 * tilemap;
	u16 width,height;
	T_LevelActor * actors;
	s32 startX,startY;
	u8 bank;
	u8 musicId;
} T_LevelHeader;
const T_LevelHeader headerData[] = {
	//	BGIMG			TILESET			TSPROPS			TILEMAP			WIDTH	HEIGHT	ACTORS			STARTX	STARTY	BANK	MUSIC
	//1
	{	level1BgImg,	level1Tileset,	level1TsProps,	level1Tilemap,	120,	32,		level1Actors,	0x0030,	0x01E0,	4,		8},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	//2
	/*{	level1BgImg,	level1Tileset,	level1TsProps,	level2Tilemap,	20,		15,		level2Actors,	0x0010,	0x00C0,	4,		8},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
	//3
	/*{	level3BgImg,	level3Tileset,	level3TsProps,	level3Tilemap,	20,		15,		level3Actors,	0x0010,	0x00C0,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
	//4
	/*{	level4BgImg,	level4Tileset,	level4TsProps,	level4Tilemap,	20,		15,		level4Actors,	0x0010,	0x00C0,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
	//5
	/*{	level1BgImg,	level1Tileset,	level1TsProps,	level5Tilemap,	20,		15,		level5Actors,	0x0010,	0x00C0,	4,		8},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
	//6
	/*{	level6BgImg,	level6Tileset,	level6TsProps,	level6Tilemap,	20,		15,		level6Actors,	0x0010,	0x00C0,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
	//7
	/*{	level7BgImg,	level7Tileset,	level7TsProps,	level7Tilemap,	20,		15,		level7Actors,	0x0010,	0x00C0,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
	//8
	/*{	level8BgImg,	level8Tileset,	level8TsProps,	level8Tilemap,	20,		15,		level8Actors,	0x0010,	0x00C0,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000,	0,		0},*/
};

//Clear level
void clear_level() {
	//Clear graphics data
	gfxUseBgL1 = 0;
	gfxUseBgL2 = 0;
	actPlayer = NULL;
	//Clear screen scroll
	camxL1 = 0;
	camyL1 = 0;
	camxL2 = 0;
	camyL2 = 0;
}
//Focus camera
void focus_camera() {
	int fx,fy;
	u32 camx,camy;
	//Focus camera
	fx = (actPlayer->x>>4)+8;
	fy = (actPlayer->y>>4)+8;
	if(levelWidth<=320) {
		camx = (320-levelWidth)>>1;
	} else {
		if(fx<160) {
			camx = 0;
		} else if(fx>(levelWidth-160)) {
			camx = levelWidth-320;
		} else {
			camx = fx-160;
		}
	}
	if(levelHeight<=240) {
		camy = 240-levelHeight;
	} else {
		if(fy<120) {
			camy = 0;
		} else if(fy>(levelHeight-120)) {
			camy = levelHeight-240;
		} else {
			camy = fy-120;
		}
	}
	//Update screen scroll
	camxL1 = camx;
	camyL1 = camy;
	camxL2 = camx>>1;
	camyL2 = camy>>1;
}
//Load level
void load_level() {
	int idx;
	int i,j;
	//Clear graphics data
	gfxUseBgL1 = 0;
	gfxUseBgL2 = 0;
	gfxUseSp = 0;
	//Setup level
	idx = (levelNum<<2)|areaNum;
	load_segment(headerData[idx].bank);
	levelBgImage	= headerData[idx].bgImg;
	levelTileset	= headerData[idx].tileset;
	levelTsProps	= headerData[idx].tsProps;
	levelTilemap	= headerData[idx].tilemap;
	levelWidth		= headerData[idx].width<<4;
	levelHeight		= headerData[idx].height<<4;
	levelActors		= headerData[idx].actors;
	memset(levelActorStatus,0,0x100);
	memset(levelSwitchStatus,0,0x40);
	memset(actorList,0,0x100*sizeof(T_Actor));
	load_bgm(headerData[idx].musicId);
	//Init player
	actorList[0].id		= 0x0001;
	actorList[0].param	= 0x00;
	actorList[0].x		= headerData[idx].startX<<4;
	actorList[0].y		= headerData[idx].startY<<4;
	actorList[0].link	= 0xFFFF;
	actPlayer = &actorList[0];
	//Init screen scroll
	focus_camera();
	//Init BG layers 1 and 2
	for(j=0; j<=15; j++) {
		for(i=0; i<=20; i++) {
			idx  =  i+(camxL1>>4);
			idx += (j+(camyL1>>4))*(levelWidth>>4);
			gfxDataBgL1[gfxUseBgL1] = levelTileset[levelTilemap[idx]];
			gfxBgLayer1[gfxUseBgL1].s.objX			= (i+(camxL1>>4))<<6;
			gfxBgLayer1[gfxUseBgL1].s.scaleW		= 1<<10;
			gfxBgLayer1[gfxUseBgL1].s.imageW		= 16<<5;
			gfxBgLayer1[gfxUseBgL1].s.paddingX		= 0;
			gfxBgLayer1[gfxUseBgL1].s.objY			= (j+(camyL1>>4))<<6;
			gfxBgLayer1[gfxUseBgL1].s.scaleH		= 1<<10;
			gfxBgLayer1[gfxUseBgL1].s.imageH		= 16<<5;
			gfxBgLayer1[gfxUseBgL1].s.paddingY		= 0;
			gfxBgLayer1[gfxUseBgL1].s.imageStride	= 16>>2;
			gfxBgLayer1[gfxUseBgL1].s.imageAdrs		= 0;
			gfxBgLayer1[gfxUseBgL1].s.imageFmt		= G_IM_FMT_RGBA;
			gfxBgLayer1[gfxUseBgL1].s.imageSiz		= G_IM_SIZ_16b;
			gfxBgLayer1[gfxUseBgL1].s.imagePal		= 0;
			gfxBgLayer1[gfxUseBgL1].s.imageFlags	= 0;
			gfxUseBgL1++;
		}
	}
	gfxDataBgL2 = levelBgImage;
	//TODO
	gfxUseBgL2++;
}
//Update level
void update_level() {
	int fx,fy;
	int i,idx;
	u32 camxPrev = camxL1;
	u32 camyPrev = camyL1;
	//Check to spawn actors
	for(i=0; i<0x1000; i++) {
		if(levelActors[i].id==0xFFFF) break;
		if(ah_check(levelActors[i].x,levelActors[i].y)) {
			if(levelActorStatus[i]==0) {
				add_actor(levelActors[i].id,levelActors[i].param,levelActors[i].x,levelActors[i].y,i);
				levelActorStatus[i] = 1;
			}
		} else if(levelActorStatus[i]==2) {
			levelActorStatus[i] = 0;
		}
	}
	//Update screen scroll
	focus_camera();
	//Update BG layers 1 and 2
	if((camxPrev&(~0xF))!=(camxL1&(~0xF))) {
		if(camxL1>camxPrev) {
			//Draw column right
			fx = (camxL1>>4)+20;
		} else {
			//Draw column left
			fx = (camxL1>>4);
		}
		fy = (camyL1>>4);
		for(i=0; i<=15; i++) {
			idx = (fx%21)+(((fy+i)%16)*21);
			gfxDataBgL1[idx] = levelTileset[levelTilemap[fx+((fy+i)*(levelWidth>>4))]];
			gfxBgLayer1[idx].s.objX = fx<<6;
			gfxBgLayer1[idx].s.objY = (fy+i)<<6;
		}
	}
	if((camyPrev&(~0xF))!=(camyL1&(~0xF))) {
		if(camyL1>camyPrev) {
			//Draw row down
			fy = (camyL1>>4)+15;
		} else {
			//Draw row up
			fy = (camyL1>>4);
		}
		fx = (camxL1>>4);
		for(i=0; i<=20; i++) {
			idx = ((fx+i)%21)+((fy%16)*21);
			gfxDataBgL1[idx] = levelTileset[levelTilemap[(fx+i)+(fy*(levelWidth>>4))]];
			gfxBgLayer1[idx].s.objX = (fx+i)<<6;
			gfxBgLayer1[idx].s.objY = fy<<6;
		}
	}
}
