#include "actors.h"

////////////////
//HELPER FUNCS//
////////////////
//ACTOR GRAPHICS DATA
typedef struct {
	int offsX,offsY;
	s32 scaleX,scaleY;
	u16 width,height;
	u16 * graphic;
} T_StaticSprite;
typedef struct {
	int offsX,offsY;
	u16 id;
} T_CompoundSprite;
typedef struct {
	u16 frames;
	u16 id;
} T_AnimatedSprite;
const T_StaticSprite staticSpriteData[] = {
	//	OFFSX	OFFSY	SCALEX		SCALEY		WIDTH	HEIGHT		GRAPHIC
	//00
	{	0,		0,		0x10000,	0x10000,	16,		16,			test16Gfx},				//TEST 16
	{	0,		0,		0x10000,	0x10000,	8,		8,			test8Gfx},				//TEST 8
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x0000]},	//Player head
	{	0,		0,		0x10000,	0x10000,	8,		12,			&playerGfx[0x0080]},	//Player body
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x0100]},	//Player foot normal
	{	0,		0,		0x10000,	0x10000,	8,		8,			NULL},					//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x0180]},	//Player foot left
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x01C0]},	//Player foot right
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x0200]},	//Player hand normal left
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x0240]},	//Player hand normal right
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x0280]},	//Player hand grab left
	{	0,		0,		0x10000,	0x10000,	8,		8,			&playerGfx[0x02C0]},	//Player hand grab right
	{	0,		0,		0x10000,	0x10000,	16,		16,			&leverGfx[0x0000]},		//Lever up
	{	0,		0,		0x10000,	0x10000,	16,		16,			&leverGfx[0x0100]},		//Lever mid
	{	0,		0,		0x10000,	0x10000,	16,		16,			&leverGfx[0x0200]},		//Lever down
	{	0,		0,		0x10000,	0x10000,	16,		16,			NULL},					//(DUMMY FOR ALIGNMENT)
	//10
	{	0,		0,		0xFFFF0000,	0x10000,	16,		16,			NULL},					//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			NULL},					//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x0000]},	//Player head
	{	0,		0,		0xFFFF0000,	0x10000,	8,		12,			&playerGfx[0x0080]},	//Player body
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x0100]},	//Player foot normal
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			NULL},					//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x0180]},	//Player foot left
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x01C0]},	//Player foot right
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x0200]},	//Player hand normal left
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x0240]},	//Player hand normal right
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x0280]},	//Player hand grab left
	{	0,		0,		0xFFFF0000,	0x10000,	8,		8,			&playerGfx[0x02C0]},	//Player hand grab right
	{	0,		0,		0x10000,	0x10000,	16,		32,			&doorGfx[0x0000]},		//Door closed
	{	0,		0,		0x10000,	0x10000,	16,		32,			&doorGfx[0x0200]},		//Door mid
	{	0,		0,		0x10000,	0x10000,	16,		32,			&doorGfx[0x0400]},		//Door open
	{	0,		0,		0x10000,	0x10000,	16,		32,			NULL},					//(DUMMY FOR ALIGNMENT)
	//20
	{	0,		0,		0x10000,	0x10000,	16,		16,			&springGfx[0x0000]},	//Trampoline frame 1
	{	0,		0,		0x10000,	0x10000,	16,		16,			&springGfx[0x0100]},	//Trampoline frame 2
	{	0,		0,		0x10000,	0x10000,	16,		16,			&springGfx[0x0200]},	//Trampoline frame 3
	{	0,		0,		0x10000,	0x10000,	16,		16,			&springGfx[0x0300]},	//Trampoline frame 4
	//TODO
};
const T_CompoundSprite compoundSpriteData[] = {
	//	OFFSX	OFFSY	ID
	//000
	{	6,		9,		0x0004},	//Player idle frame 1
	{	7,		3,		0x0009},
	{	4,		-10,	0x0002},
	{	4,		-2,		0x0003},
	{	3,		9,		0x0004},
	{	2,		3,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	6,		9,		0x0004},	//Player idle frame 2
	{	7,		3,		0x0009},
	{	4,		-9,		0x0002},
	{	4,		-1,		0x0003},
	{	3,		9,		0x0004},
	{	2,		3,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//010
	{	6,		9,		0x0004},	//Player idle frame 3
	{	7,		4,		0x0009},
	{	4,		-9,		0x0002},
	{	4,		-1,		0x0003},
	{	3,		9,		0x0004},
	{	2,		4,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	6,		9,		0x0004},	//Player idle frame 4
	{	7,		4,		0x0009},
	{	4,		-10,	0x0002},
	{	4,		-2,		0x0003},
	{	3,		9,		0x0004},
	{	2,		4,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//020
	{	6,		9,		0x0004},	//Player run frame 1
	{	7,		3,		0x0009},
	{	4,		-10,	0x0002},
	{	4,		-2,		0x0003},
	{	3,		9,		0x0004},
	{	2,		3,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	9,		9,		0x0007},	//Player run frame 2
	{	5,		3,		0x0009},
	{	4,		-9,		0x0002},
	{	4,		-1,		0x0003},
	{	1,		9,		0x0006},
	{	4,		3,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//030
	{	6,		9,		0x0004},	//Player run frame 3
	{	7,		3,		0x0009},
	{	4,		-10,	0x0002},
	{	4,		-2,		0x0003},
	{	3,		9,		0x0004},
	{	2,		3,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	4,		9,		0x0006},	//Player run frame 4
	{	9,		2,		0x0009},
	{	4,		-9,		0x0002},
	{	4,		-1,		0x0003},
	{	6,		9,		0x0007},
	{	0,		2,		0x0008},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//040
	{	2,		9,		0x0014},	//Player idle frame 1
	{	1,		3,		0x0019},
	{	4,		-10,	0x0012},
	{	4,		-2,		0x0013},
	{	5,		9,		0x0014},
	{	6,		3,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	2,		9,		0x0014},	//Player idle frame 2
	{	1,		3,		0x0019},
	{	4,		-9,		0x0012},
	{	4,		-1,		0x0013},
	{	5,		9,		0x0014},
	{	6,		3,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//050
	{	2,		9,		0x0014},	//Player idle frame 3
	{	1,		4,		0x0019},
	{	4,		-9,		0x0012},
	{	4,		-1,		0x0013},
	{	5,		9,		0x0014},
	{	6,		4,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	2,		9,		0x0014},	//Player idle frame 4
	{	1,		4,		0x0019},
	{	4,		-10,	0x0012},
	{	4,		-2,		0x0013},
	{	5,		9,		0x0014},
	{	6,		4,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//060
	{	2,		9,		0x0014},	//Player run frame 1
	{	1,		3,		0x0019},
	{	4,		-10,	0x0012},
	{	4,		-2,		0x0013},
	{	5,		9,		0x0014},
	{	6,		3,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	-1,		9,		0x0017},	//Player run frame 2
	{	3,		3,		0x0019},
	{	4,		-9,		0x0012},
	{	4,		-1,		0x0013},
	{	7,		9,		0x0016},
	{	4,		3,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//070
	{	2,		9,		0x0014},	//Player run frame 3
	{	1,		3,		0x0019},
	{	4,		-10,	0x0012},
	{	4,		-2,		0x0013},
	{	5,		9,		0x0014},
	{	6,		3,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	4,		9,		0x0016},	//Player run frame 4
	{	-1,		2,		0x0019},
	{	4,		-9,		0x0012},
	{	4,		-1,		0x0013},
	{	2,		9,		0x0017},
	{	8,		2,		0x0018},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//080
	{	0,		0,		0x0000},	//Player ledge grab frame 1 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player ledge grab frame 2 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//090
	{	0,		0,		0x0000},	//Player ledge grab frame 3 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player ledge grab frame 4 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//0A0
	{	0,		0,		0x0000},	//Player ledge grab frame 1 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player ledge grab frame 2 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//0B0
	{	0,		0,		0x0000},	//Player ledge grab frame 3 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player ledge grab frame 4 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//0C0
	{	0,		0,		0x0000},	//Player ledge grab frame 5 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player ledge grab frame 5 (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//0D0
	{	0,		0,		0x0000},	//Player skid (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player skid (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//0E0
	{	0,		0,		0x0000},	//Player jump (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player jump (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//0F0
	{	0,		0,		0x0000},	//Player fall (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player fall (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//100
	{	0,		0,		0x0000},	//Player wall slide (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0,		0x0000},	//Player wall slide (PLACEHOLDER)
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},
	{	0,		0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//110
	//TODO
};
const T_AnimatedSprite animatedSpriteData[] = {
	//	FRAMES	ID
	//00
	{	12,		0x0000},	//Player idle
	{	12,		0x0008},
	{	12,		0x0010},
	{	12,		0x0018},
	{	0,		0xFFFF},
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	6,		0x0020},	//Player run
	{	6,		0x0028},
	{	6,		0x0030},
	{	6,		0x0038},
	{	0,		0xFFFF},
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	6,		0x000C},	//Lever up->down
	{	6,		0x000D},
	{	6,		0x000E},
	{	0,		0xFFFF},
	//10
	{	12,		0x0040},	//Player idle
	{	12,		0x0048},
	{	12,		0x0050},
	{	12,		0x0058},
	{	0,		0xFFFF},
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	6,		0x0060},	//Player run
	{	6,		0x0068},
	{	6,		0x0070},
	{	6,		0x0078},
	{	0,		0xFFFF},
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	6,		0x000E},	//Lever down->up
	{	6,		0x000D},
	{	6,		0x000C},
	{	0,		0xFFFF},
	//20
	{	6,		0x001C},	//Door closed->open
	{	6,		0x001D},
	{	6,		0x001E},
	{	0,		0xFFFF},
	{	6,		0x001E},	//Door open->closed
	{	6,		0x001D},
	{	6,		0x001C},
	{	0,		0xFFFF},
	{	6,		0x0020},	//Trampoline
	{	6,		0x0021},
	{	6,		0x0022},
	{	6,		0x0023},
	{	6,		0x0022},
	{	6,		0x0021},
	{	0,		0xFFFF},
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	//30
	{	6,		0x0080},	//Player ledge grab
	{	6,		0x0088},
	{	6,		0x0090},
	{	6,		0x0098},
	{	6,		0x00C0},
	{	0,		0xFFFF},
	{	6,		0x00A0},	//Player ledge grab
	{	6,		0x00A8},
	{	6,		0x00B0},
	{	6,		0x00B8},
	{	6,		0x00C8},
	{	0,		0xFFFF},
	{	120,	0x00D0},	//Player skid
	{	0,		0xFFFF},
	{	120,	0x00D8},	//Player skid
	{	0,		0xFFFF},
	//40
	{	120,	0x00E0},	//Player jump
	{	0,		0xFFFF},
	{	120,	0x00E8},	//Player jump
	{	0,		0xFFFF},
	{	120,	0x00F0},	//Player fall
	{	0,		0xFFFF},
	{	120,	0x00F8},	//Player fall
	{	0,		0xFFFF},
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	0,		0xFFFF},	//(DUMMY FOR ALIGNMENT)
	{	120,	0x0100},	//Player wall slide
	{	0,		0xFFFF},
	{	120,	0x0108},	//Player wall slide
	{	0,		0xFFFF},
	//50
	//TODO
};

//Move with velocity
void ah_move(T_Actor * a) {
	//Apply velocity
	a->x += a->vx;
	a->y += a->vy;
}
//Collide with other actor
#define ah_collidepl(a) ah_collide(a,actPlayer)
int ah_collide(T_Actor * a,T_Actor * b) {
	//Check all possible failure cases
	if((a->x+a->cx1)>(b->x+b->cx2)) return 0;
	if((b->x+b->cx1)>(a->x+a->cx2)) return 0;
	if((a->y+a->cy1)>(b->y+b->cy2)) return 0;
	if((b->y+b->cy1)>(a->y+a->cy2)) return 0;
	//Return success
	return 1;
}
//Get level tile
u8 ah_gettile(int x,int y) {
	return levelTilemap[(x>>8)+((y>>8)*(levelWidth>>4))];
}
//Collide with level
u8 ah_collidebg(T_Actor * a) {
	//Initialize some variables
	u8 t1,t2;
	u8 res = 0;
	int cx1 = a->x+a->cx1;
	int cy1 = a->y+a->cy1;
	int cx2 = a->x+a->cx2;
	int cy2 = a->y+a->cy2;
	//Check left
	if(a->vx<=0) {
		t1 = ah_gettile(cx1,cy1+0x40);
		t2 = ah_gettile(cx1,cy2-0x40);
		if(levelTsProps[t1]|levelTsProps[t2]) {
			a->x += 0x100-(cx1&0xFF);
			a->vx = 0;
			res |= 1;
		}
	}
	//Check right
	if(a->vx>=0) {
		t1 = ah_gettile(cx2,cy1+0x40);
		t2 = ah_gettile(cx2,cy2-0x40);
		if(levelTsProps[t1]|levelTsProps[t2]) {
			a->x -= cx2&0xFF;
			a->vx = 0;
			res |= 2;
		}
	}
	//Check top
	if(a->vy<=0) {
		t1 = ah_gettile(cx1+0x40,cy1);
		t2 = ah_gettile(cx2-0x40,cy1);
		if(levelTsProps[t1]|levelTsProps[t2]) {
			a->y += 0x100-(cy1&0xFF);
			a->vy = -a->vy;
			res |= 4;
		}
	}
	//Check bottom
	if(a->vy>=0) {
		t1 = ah_gettile(cx1+0x40,cy2);
		t2 = ah_gettile(cx2-0x40,cy2);
		if(levelTsProps[t1]|levelTsProps[t2]) {
			a->y -= cy2&0xFF;
			a->vy = 0;
			res |= 8;
		}
	}
	//Return result
	return res;
}
//Draw sprite tile
void ah_drawtile(int x,int y,int id) {
	gfxDataSp[gfxUseSp] = staticSpriteData[id].graphic;
	gfxSprites[gfxUseSp].s.objX			= (x+staticSpriteData[id].offsX)<<2;
	gfxSprites[gfxUseSp].s.scaleW		= staticSpriteData[id].scaleX>>6;
	gfxSprites[gfxUseSp].s.imageW		= staticSpriteData[id].width<<5;
	gfxSprites[gfxUseSp].s.paddingX		= 0;
	gfxSprites[gfxUseSp].s.objY			= (y+staticSpriteData[id].offsY)<<2;
	gfxSprites[gfxUseSp].s.scaleH		= staticSpriteData[id].scaleY>>6;
	gfxSprites[gfxUseSp].s.imageH		= staticSpriteData[id].height<<5;
	gfxSprites[gfxUseSp].s.paddingY		= 0;
	gfxSprites[gfxUseSp].s.imageStride	= staticSpriteData[id].width>>2;
	gfxSprites[gfxUseSp].s.imageAdrs	= 0;
	gfxSprites[gfxUseSp].s.imageFmt		= G_IM_FMT_RGBA;
	gfxSprites[gfxUseSp].s.imageSiz		= G_IM_SIZ_16b;
	gfxSprites[gfxUseSp].s.imagePal		= 0;
	gfxSprites[gfxUseSp].s.imageFlags	= 0;
	if(staticSpriteData[id].scaleX<0) {
		gfxSprites[gfxUseSp].s.scaleW		= (-staticSpriteData[id].scaleX)>>6;
		gfxSprites[gfxUseSp].s.imageFlags	|= G_OBJ_FLAG_FLIPS;
	}
	if(staticSpriteData[id].scaleY<0) {
		gfxSprites[gfxUseSp].s.scaleH		= (-staticSpriteData[id].scaleY)>>6;
		gfxSprites[gfxUseSp].s.imageFlags	|= G_OBJ_FLAG_FLIPT;
	}
	gfxUseSp++;
}
//Standard draw
void ah_draw(T_Actor * a) {
	int i,i2;
	int id = a->sprId;
	//Check for animated sprite
	if(a->sprMode&2) {
		a->animTimer++;
		if(a->animTimer==animatedSpriteData[a->sprId+a->animFrame].frames) {
			a->animTimer = 0;
			a->animFrame++;
			if(animatedSpriteData[a->sprId+a->animFrame].id==0xFFFF) {
				a->animFrame = 0;
			}
		}
		id = animatedSpriteData[a->sprId+a->animFrame].id;
	}
	//Check for compound sprite
	if(a->sprMode&1) {
		//Compound sprite
		i = id;
		while(1) {
			i2 = compoundSpriteData[i].id;
			if(i2==0xFFFF) break;
			ah_drawtile(
				(a->x>>4)+compoundSpriteData[i].offsX+staticSpriteData[i2].offsX,
				(a->y>>4)+compoundSpriteData[i].offsY+staticSpriteData[i2].offsY,
				i2);
			i++;
		}
	} else {
		//Static sprite
		ah_drawtile(
			(a->x>>4)+staticSpriteData[id].offsX,
			(a->y>>4)+staticSpriteData[id].offsY,
			id);
	}
}
//Draw text character
void ah_drawchar(int x,int y,char c) {
	gfxDataSp[gfxUseSp] = fontAsciiTable[c];
	gfxSprites[gfxUseSp].s.objX			= x<<2;
	gfxSprites[gfxUseSp].s.scaleW		= 1<<10;
	gfxSprites[gfxUseSp].s.imageW		= 16<<5;
	gfxSprites[gfxUseSp].s.paddingX		= 0;
	gfxSprites[gfxUseSp].s.objY			= y<<2;
	gfxSprites[gfxUseSp].s.scaleH		= 1<<10;
	gfxSprites[gfxUseSp].s.imageH		= 16<<5;
	gfxSprites[gfxUseSp].s.paddingY		= 0;
	gfxSprites[gfxUseSp].s.imageStride	= 16>>2;
	gfxSprites[gfxUseSp].s.imageAdrs	= 0;
	gfxSprites[gfxUseSp].s.imageFmt		= G_IM_FMT_RGBA;
	gfxSprites[gfxUseSp].s.imageSiz		= G_IM_SIZ_16b;
	gfxSprites[gfxUseSp].s.imagePal		= 0;
	gfxSprites[gfxUseSp].s.imageFlags	= 0;
	gfxUseSp++;
}
//Draw text
void ah_drawtext(int x,int y,char * str) {
	int i = 0;
	while(1) {
		if(str[i]==0) break;
		ah_drawchar(x,y,str[i]);
		x += 16;
		i++;
	}
}
//Check position
u8 ah_check(int x,int y) {
	//Check all possible failure cases
	if(x<camx) return 0;
	if(y<camy) return 0;
	if(x>=(camx+320)) return 0;
	if(y>=(camy+240)) return 0;
	//Return success
	return 1;
}
//Kill
void ah_kill(T_Actor * a) {
	//Remove actor
	a->id = 0;
	//Mark as killed in level data
	if(a->link!=0xFFFF) {
		levelActorStatus[a->link] = 2;
		if(a->status==0) levelActorStatus[a->link]++;
	}
}

////////////////
//ACTORS FUNCS//
////////////////
//Player!
//[TEMPS USE]
//0: Grounded/on platform state
//1: Special ledge/wall state
//2: Player facing direction
//3: Timer for impatience
void actor_player_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
	//Init collision info
	self->cx1 =  2<<4;
	self->cy1 = -8<<4;
	self->cx2 = 14<<4;
	self->cy2 = 16<<4;
	//Init animation
	self->sprId = 0x00;
	self->sprMode = 3;
	//Init misc.
	playerHP = 12;
	playerMode = 0xFF;
}
void actor_player_main(T_Actor * self) {
	int ax,ax2;
	u8 t1,t2;
	u16 curAnim,oldAnim;
	//Move horizontally
	oldAnim = self->sprId;
	ax = joy1Data.stick_x>>5;
	     if(ax<-2) ax = -2;
	else if(ax> 2) ax =  2;
	if(ax) self->temps[2] = ax;
	if(playerMode!=0xFF) ax = 0;
	if(ax==0) {
		     if(self->vx<0) {
			self->vx += 2;
			if(self->vx>0) self->vx = 0;
			 }
		else if(self->vx>0) {
			self->vx -= 2;
			if(self->vx<0) self->vx = 0;
		}
	} else {
		self->vx += ax;
		     if(self->vx<-0x20) self->vx = -0x20;
		else if(self->vx> 0x20) self->vx =  0x20;
	}
	if(self->temps[0]&8) {
		if(self->vx) {
			     if(ax<0 && self->vx>0 && self->vx< 0x10) curAnim = 0x3C;
			else if(ax>0 && self->vx<0 && self->vx>-0x10) curAnim = 0x3C;
			else curAnim = 0x06;
		}
		else curAnim = 0x00;
	} else {
		     if(self->temps[0]&1 && ax<0) curAnim = 0x4C;
		else if(self->temps[0]&2 && ax>0) curAnim = 0x4C;
		else if(self->vy>0) curAnim = 0x44;
		else                curAnim = 0x40;
	}
	//Handle jumping
	if(joy1ButtonDown&A_BUTTON && playerMode==0xFF) {
		//Check normal jump
		if(self->temps[0]&8) {
			self->vy = -0x40;
		} else {
			//Check wall jump
			     if(self->temps[0]&1 && ax<0) {
				self->vx =  0x20;
				self->vy = -0x40;
			}
			else if(self->temps[0]&2 && ax>0) {
				self->vx = -0x20;
				self->vy = -0x40;
			}
		}
	}
	if(joy1ButtonUp&A_BUTTON && playerMode==0xFF && self->vy<-0x20) self->vy = -0x20;
	//Handle ledge grab
	if((self->temps[1]&0xFF)<1 && (self->temps[0]&8)==0 && self->y>0x100) {
			 if(self->temps[0]&1 && ax<0) {
			if(levelTsProps[ah_gettile(self->x-0xE0,self->y-0x100)]==0 &&
			   levelTsProps[ah_gettile(self->x-0xE0,self->y)]) {
				//Init ledge grab state
				self->temps[1] = 0x801;
				self->x &= ~0xFF;
				self->x += 0xE0;
				self->y &= ~0xFF;
			}
		}
		else if(self->temps[0]&2 && ax>0) {
			if(levelTsProps[ah_gettile(self->x+0xE0,self->y-0x100)]==0 &&
			   levelTsProps[ah_gettile(self->x+0xE0,self->y)]) {
				//Init ledge grab state
				self->temps[1] = 0x001;
				self->x &= ~0xFF;
				self->x += 0x20;
				self->y &= ~0xFF;
			}
		}
	}
	if(self->temps[1]) {
		curAnim = 0x30;
		//Update position on certain frames
		switch(self->temps[1]&0xFF) {
			case 5: {
				if(self->temps[1]&0x800) self->vx = -0x10;
				else                     self->vx =  0x10;
				self->vy = -0x60;
				break;
			}
			case 11: {
				if(self->temps[1]&0x800) self->vx = -0x30;
				else                     self->vx =  0x30;
				self->vy = -0x60;
				break;
			}
			case 17: {
				if(self->temps[1]&0x800) self->vx = -0x60;
				else                     self->vx =  0x60;
				self->vy = -0x30;
				break;
			}
			case 22: {
				if(self->temps[1]&0x800) self->vx = -0x60;
				else                     self->vx =  0x60;
				self->vy = -0x10;
				break;
			}
			default: {
				self->vx = 0;
				self->vy = 0;
				break;
			}
		}
		//Update ledge grab timer
		self->temps[1]++;
		if((self->temps[1]&0xFF)==24) {
			self->temps[1] = 0;
		}
	}
	//Handle gravity
	if((self->temps[0]&8)==0 && self->temps[1]==0) {
		self->vy += 2;
		if(self->vy>0x30) self->vy = 0x30;
	}
	//Do movement
	ah_move(self);
	//Check horizontal bounds collision
	if(self->vx<0 && self->x<0) {
		self->x = 0;
		self->vx = 0;
	} else if(self->vx>0 && ((self->x>>4)+0x10)>levelWidth) {
		self->x = (levelWidth-0x10)<<4;
		self->vx = 0;
	}
	//Check vertical bounds collision
	if(self->y<0) {
		self->y = 0;
		self->vy = -self->vy;
		if(self->vy<0) self->vy = 0;
	} else if((self->y>>4)>levelHeight) {
		playerMode = 0x08;
	}
	//Check BG collision and set grounded state
	if(self->temps[1]==0 && playerMode==0xFF) {
		self->temps[0] = ah_collidebg(self);
	} else {
		self->temps[0] = 0;
	}
	//Animate player
	if(self->temps[2]<0) {
		switch(curAnim) {
			case 0x00: {
				curAnim = 0x10;
				break;
			}
			case 0x06: {
				curAnim = 0x16;
				break;
			}
			case 0x30: {
				curAnim = 0x36;
				break;
			}
			case 0x3C: {
				curAnim = 0x3E;
				break;
			}
			case 0x40: {
				curAnim = 0x42;
				break;
			}
			case 0x44: {
				curAnim = 0x46;
				break;
			}
			case 0x4C: {
				curAnim = 0x4E;
				break;
			}
		}
	}
	self->sprId = curAnim;
	if(curAnim!=oldAnim) {
		self->animFrame = 0;
		self->animTimer = 0;
	}
	ah_draw(self);
}
//Lever
//[TEMPS USE]
//0: State
//1: Animation timer
void actor_lever_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
}
void actor_lever_main(T_Actor * self) {
	//TODO
}
//Door
//[TEMPS USE]
//0: State
//1: Animation timer
void actor_door_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
}
void actor_door_main(T_Actor * self) {
	//TODO
}
//Title sprites
//[TEMPS USE]
//0: Group animation timer
void actor_title_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
	//Init animation
	//self->sprId = 0;
	//self->sprMode = 0;
}
void actor_title_main(T_Actor * self) {
	//Check for START press
	if(joy1ButtonDown&START_BUTTON && self->temps[0]==0) {
		self->temps[0]++;
	}
	//Draw title graphic
	//ah_draw(self);
	//Draw "PRESS START"
	if((self->temps[0]&4)==0) {
		ah_drawtext(0x48,0xA0,"PRESS START");
	}
	//Update animation timer
	if(self->temps[0]) self->temps[0]++;
}
//Game over sprites
//[TEMPS USE]
//0: Group animation timer
const char gameOverText[16] = {
	'G','\0',
	'A','\0',
	'M','\0',
	'E','\0',
	'O','\0',
	'V','\0',
	'E','\0',
	'R','\0',
};
const int gameOverXPos[8] = {0x58,0x68,0x78,0x88,0xA8,0xB8,0xC8,0xD8};
int calc_game_over_ypos(int t) {
	int dy;
	if(t<0) return -0x20;
	else if(t<0x20) {
		dy = t*t;
		return (0x60-0x80)+(dy>>3);
	} else if(t<0x40) {
		dy = (t-0x30)*(t-0x30);
		return (0x60-0x20)+(dy>>3);
	} else if(t<0x50) {
		dy = (t-0x48)*(t-0x48);
		return (0x60-0x08)+(dy>>3);
	} else if(t<0x58) {
		dy = (t-0x54)*(t-0x54);
		return (0x60-0x02)+(dy>>3);
	} else return 0x60;
}
void actor_over_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
}
void actor_over_main(T_Actor * self) {
	int i;
	//Draw letters
	for(i=0; i<8; i++) {
		ah_drawtext(gameOverXPos[i],
			calc_game_over_ypos(self->temps[0]-(i<<2)),
			&gameOverText[i<<1]);
	}
	//Update animation timer
	self->temps[0]++;
}
//Ending sprites
//[TEMPS USE]
//0: Group animation timer
void actor_ending_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
}
void actor_ending_main(T_Actor * self) {
	//TODO
	
	
	
}
//Ready sprites
//[TEMPS USE]
//0: Group animation timer
const char levelNameData[4][16] = {
	//234567890123456
	"   LEVEL1NAME",
	"   LEVEL2NAME",
	"   LEVEL3NAME",
	"   LEVEL4NAME",
};
void actor_ready_init(T_Actor * self) {
	//Mark inited
	self->inited = 1;
}
void actor_ready_main(T_Actor * self) {
	int ax;
	char strBuf[16];
	//Draw level num. string
	sprintf(strBuf,"LEVEL %d",levelNum+1);
	ax = -(0x140-0x68)+(self->temps[0]<<4);
	if(ax>0x68) ax = 0x68;
	ah_drawtext(ax,0x40,strBuf);
	//Draw level name string
	ax = (0x140+0x20)-((self->temps[0]-0x20)<<4);
	if(ax<0x20) ax = 0x20;
	ah_drawtext(ax,0x60,levelNameData[levelNum]);
	//Draw player lives
	sprintf(strBuf,"$*%02d",playerLives);
	ax = (0xE0+0xA0)-((self->temps[0]-0x30)<<3);
	if(ax<0xA0) ax = 0xA0;
	self->y = ax<<4;
	ah_drawtext(0x80,ax,strBuf);
	//Update animation timer
	self->temps[0]++;
}




////////////////////
//ACTOR PROCESSING//
////////////////////
//ACTOR INIT FUNCS
void (*actorInitFuncs[0x100])(T_Actor*) = {
	//00
	NULL,				//00 (nothing)
	actor_player_init,	//01 (player!)
	actor_lever_init,	//02 (lever)
	actor_door_init,	//03 (door)
	actor_title_init,	//04 (title sprites)
	actor_over_init,	//05 (game over sprites)
	actor_ending_init,	//06 (ending sprites)
	actor_ready_init,	//07 (ready sprites)
	//TODO
};
//ACTOR MAIN FUNCS
void (*actorMainFuncs[0x100])(T_Actor*) = {
	//00
	NULL,				//00 (nothing)
	actor_player_main,	//01 (player!)
	actor_lever_main,	//02 (lever)
	actor_door_main,	//03 (door)
	actor_title_main,	//04 (title sprites)
	actor_over_main,	//05 (game over sprites)
	actor_ending_main,	//06 (ending sprites)
	actor_ready_main,	//07 (ready sprites)
	//TODO
};

//Clear actor data
void clear_actors() {
	//Clear graphics data
	gfxUseSp = 0;
	//Clear actor list data
	memset(actorList,0,0x100*sizeof(T_Actor));
}
//Add actor
void add_actor(u16 id,u8 param,int x,int y,u16 link) {
	int i;
	T_Actor actor;
	//Check for empty slot
	for(i=0; i<0x100; i++) {
		if(actorList[i].id==0) {
			//Store actor
			memset(&actor,0,sizeof(T_Actor));
			actor.id	= id;
			actor.param	= param;
			actor.x		= x<<4;
			actor.y		= y<<4;
			actor.link	= link;
			memcpy(&actorList[i],&actor,sizeof(T_Actor));
			return;
		}
	}
	//Check for offscreen slot
	for(i=0; i<0x100; i++) {
		if(actorList[i].status==2) {
			//Store actor
			memset(&actor,0,sizeof(T_Actor));
			actor.id	= id;
			actor.param	= param;
			actor.x		= x<<4;
			actor.y		= y<<4;
			actor.link	= link;
			memcpy(&actorList[i],&actor,sizeof(T_Actor));
			return;
		}
	}
}
//Update actors
void update_actors() {
	int i;
	u16 thisId;
	char strBuf[16];
	//Clear graphics data
	gfxUseSp = 0;
	//Process loaded actors
	for(i=0; i<0x100; i++) {
		if(actorList[i].id!=0) {
			//Check actor onscreen status
			actorList[i].status = ah_check(actorList[i].x>>4,actorList[i].y>>4);
			//Run actor code
			thisId = actorList[i].id;
			if(thisId<=0x100) {
				if(actorList[i].inited) {
					//Run actor main func
					(*actorMainFuncs[thisId])(&actorList[i]);
				} else {
					//Run actor init func
					(*actorInitFuncs[thisId])(&actorList[i]);
				}
			}
		}
	}
	//Update HUD
	if(actPlayer!=NULL) {
		//Draw score
		sprintf(strBuf,"%08d",playerScore);
		ah_drawtext(camx,camy,strBuf);
		//Draw lives
		sprintf(strBuf,"$*%02d",playerLives);
		ah_drawtext(0x100+camx,camy,strBuf);
		//Draw HP
		memset(strBuf,0,16);
		for(i=0; i<6; i++) {
			thisId = playerHP-(i<<1);
			     if(thisId<=0) strBuf[i] = 0x3C;
			else if(thisId==1) strBuf[i] = 0x3D;
			else               strBuf[i] = 0x3E;
		}
		ah_drawtext(0xE0+camx,0x10+camy,strBuf);
	}
}
