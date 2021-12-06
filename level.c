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
	int width,height;
	T_LevelActor * actors;
	int startX,startY;
} T_LevelHeader;
const T_LevelHeader headerData[] = {
	//	BGIMG			TILESET			TSPROPS			TILEMAP			WIDTH	HEIGHT	ACTORS			STARTX	STARTY
	//1
	{	level1BgImg,	level1Tileset,	level1TsProps,	level1Tilemap,	120,	32,		level1Actors,	0x0030,	0x01E0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	//2
	/*{	level2BgImg,	level2Tileset,	level2TsProps,	level2Tilemap,	20,		15,		level2Actors,	0x0010,	0x00C0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},*/
	//3
	/*{	level3BgImg,	level3Tileset,	level3TsProps,	level3Tilemap,	20,		15,		level3Actors,	0x0010,	0x00C0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},*/
	//4
	/*{	level4BgImg,	level4Tileset,	level4TsProps,	level4Tilemap,	20,		15,		level4Actors,	0x0010,	0x00C0},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},
	{	NULL,			NULL,			NULL,			NULL,			0,		0,		NULL,			0x0000,	0x0000},*/
};

//Clear level
void clear_level() {
	//Clear graphics data
	gfxUseBgL1 = 0;
	gfxUseBgL2 = 0;
	actPlayer = NULL;
	//Clear screen scroll
	camx = 0;
	camy = 0;
	camxL1 = camx;
	camyL1 = camy;
	camxL2 = camx>>1;
	camyL2 = camy>>1;
}
//Focus camera
void focus_camera() {
	int fx,fy;
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
	//Load level segment
	load_segment(levelNum+4);
	//Setup level
	idx = (levelNum<<4)|areaNum;
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
	load_bgm(8+levelNum);
	//Init player
	actorList[0].id		= 0x0001;
	actorList[0].param	= 0x00;
	actorList[0].x		= headerData[levelNum].startX<<4;
	actorList[0].y		= headerData[levelNum].startY<<4;
	actorList[0].link	= 0xFFFF;
	actPlayer = &actorList[0];
	//Init screen scroll
	focus_camera();
	//Init BG layers 1 and 2
	for(j=0; j<=15; j++) {
		for(i=0; i<=20; i++) {
			idx  =  i+(camx>>4);
			idx += (j+(camy>>4))*(levelWidth>>4);
			gfxDataBgL1[gfxUseBgL1] = levelTileset[levelTilemap[idx]];
			gfxBgLayer1[gfxUseBgL1].s.objX			= (i+(camx>>4))<<6;
			gfxBgLayer1[gfxUseBgL1].s.scaleW		= 1<<10;
			gfxBgLayer1[gfxUseBgL1].s.imageW		= 16<<5;
			gfxBgLayer1[gfxUseBgL1].s.paddingX		= 0;
			gfxBgLayer1[gfxUseBgL1].s.objY			= (j+(camy>>4))<<6;
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
	u32 camxPrev = camx;
	u32 camyPrev = camy;
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
	if((camxPrev&(~0xF))!=(camx&(~0xF))) {
		if(camx>camxPrev) {
			//Draw column right
			fx = (camx>>4)+20;
		} else {
			//Draw column left
			fx = (camx>>4);
		}
		fy = (camy>>4);
		for(i=0; i<=15; i++) {
			idx = (fx%21)+(((fy+i)%16)*21);
			gfxDataBgL1[idx] = levelTileset[levelTilemap[fx+((fy+i)*(levelWidth>>4))]];
			gfxBgLayer1[idx].s.objX = fx<<6;
			gfxBgLayer1[idx].s.objY = (fy+i)<<6;
		}
	}
	if((camyPrev&(~0xF))!=(camy&(~0xF))) {
		if(camy>camyPrev) {
			//Draw row down
			fy = (camy>>4)+15;
		} else {
			//Draw row up
			fy = (camy>>4);
		}
		fx = (camx>>4);
		for(i=0; i<=20; i++) {
			idx = ((fx+i)%21)+((fy%16)*21);
			gfxDataBgL1[idx] = levelTileset[levelTilemap[(fx+i)+(fy*(levelWidth>>4))]];
			gfxBgLayer1[idx].s.objX = (fx+i)<<6;
			gfxBgLayer1[idx].s.objY = fy<<6;
		}
	}
}
