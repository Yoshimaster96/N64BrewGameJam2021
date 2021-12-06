#ifndef GFX_H
#define GFX_H

//Includes
#include <ultra64.h>
#include <nusys.h>
#include "data/graphics/gfx_common.h"
#include "data/graphics/gfx_title.h"
#include "data/graphics/gfx_over.h"
#include "data/graphics/gfx_ending.h"
#include "data/graphics/gfx_level1.h"
#include "data/graphics/gfx_level2.h"
#include "data/graphics/gfx_level3.h"
#include "data/graphics/gfx_level4.h"

//Variables
u16 gfxUseBgL1,gfxUseBgL2,gfxUseSp;
u16 * gfxDataBgL1[0x180],* gfxDataSp[0x400];
u16 * gfxDataBgL2;
uObjSprite gfxBgLayer1[0x180];
uObjBg gfxBgLayer2;
uObjSprite gfxSprites[0x400];
u32 camxL1,camyL1,camxL2,camyL2;

//Functions
void load_segment(int segId);
void update_gfx();

#endif
