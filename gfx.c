#include "gfx.h"

////////////
//GRAPHICS//
////////////
//SEGMENT DATA
extern char _gfx_commonSegmentRomStart[],	_gfx_commonSegmentRomEnd[],	_gfx_commonSegmentStart[];
extern char _gfx_titleSegmentRomStart[],	_gfx_titleSegmentRomEnd[],	_gfx_titleSegmentStart[];
extern char _gfx_overSegmentRomStart[],		_gfx_overSegmentRomEnd[],	_gfx_overSegmentStart[];
extern char _gfx_endingSegmentRomStart[],	_gfx_endingSegmentRomEnd[],	_gfx_endingSegmentStart[];
extern char _gfx_level1SegmentRomStart[],	_gfx_level1SegmentRomEnd[],	_gfx_level1SegmentStart[];
extern char _gfx_level2SegmentRomStart[],	_gfx_level2SegmentRomEnd[],	_gfx_level2SegmentStart[];
extern char _gfx_level3SegmentRomStart[],	_gfx_level3SegmentRomEnd[],	_gfx_level3SegmentStart[];
extern char _gfx_level4SegmentRomStart[],	_gfx_level4SegmentRomEnd[],	_gfx_level4SegmentStart[];
typedef struct {
	char * dest;
	char * start;
	char * end;
	u8 slot;
} T_Segment;
const T_Segment segmentData[] = {
	//	DEST						START						END							SLOT
	{	_gfx_commonSegmentStart,	_gfx_commonSegmentRomStart,	_gfx_commonSegmentRomEnd,	0},
	{	_gfx_titleSegmentStart,		_gfx_titleSegmentRomStart,	_gfx_titleSegmentRomEnd,	1},
	{	_gfx_overSegmentStart,		_gfx_overSegmentRomStart,	_gfx_overSegmentRomEnd,		1},
	{	_gfx_endingSegmentStart,	_gfx_endingSegmentRomStart,	_gfx_endingSegmentRomEnd,	1},
	{	_gfx_level1SegmentStart,	_gfx_level1SegmentRomStart,	_gfx_level1SegmentRomEnd,	2},
	{	_gfx_level2SegmentStart,	_gfx_level2SegmentRomStart,	_gfx_level2SegmentRomEnd,	2},
	{	_gfx_level3SegmentStart,	_gfx_level3SegmentRomStart,	_gfx_level3SegmentRomEnd,	2},
	{	_gfx_level4SegmentStart,	_gfx_level4SegmentRomStart,	_gfx_level4SegmentRomEnd,	2},
};
u8 loadedSegments[4] = {0xFF,0xFF,0xFF,0xFF};
OSIoMesg mqDmaBuf[4];
OSMesgQueue mqDma;
u8 piInited = 0;

//Graphics variables
const Gfx gfxInit1[] = {
	//Init RDP for clearing
	gsDPSetCycleType(G_CYC_FILL),
	gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
	gsSPObjRenderMode(G_OBJRM_NOTXCLAMP),
	gsDPSetCombineMode(G_CC_SHADE,G_CC_SHADE),
	gsDPSetCombineKey(G_CK_NONE),
	gsDPSetScissor(G_SC_NON_INTERLACE,0,0,320,240),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsDPSetColorDither(G_CD_DISABLE),
	gsSPEndDisplayList(),
};
const Gfx gfxInit2[] = {
	//Init RDP for normal use
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPSetCombineMode(G_CC_DECALRGBA,G_CC_DECALRGBA),
	gsDPSetTexturePersp(G_TP_NONE),
	gsDPSetTextureLOD(G_TL_TILE),
	gsDPSetTextureFilter(G_TF_POINT),
	gsDPSetTextureConvert(G_TC_FILT),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetAlphaCompare(G_AC_THRESHOLD),
	gsDPSetBlendColor(0,0,0,1),
	gsSPEndDisplayList(),
};
Gfx dlBuf[2][0x1000];
Gfx * dlPtr;
u8 bufferId = 0;

//Load segment
void load_segment(int segId) {
	u32 dest,src,size;
	int slot;
	//Check if PI hasn't been inited
	if(!piInited) {
		osCreatePiManager(OS_MESG_PRI_NORMAL,&mqDma,(OSMesg*)mqDmaBuf,4);
		osCreateMesgQueue(&mqDma,(OSMesg*)mqDmaBuf,4);
		piInited = 1;
	}
	//Check if loaded already
	slot = segmentData[segId].slot;
	if(loadedSegments[slot]!=segId) {
		//Copy data
		dest = (u32)segmentData[segId].dest;
		src  = (u32)segmentData[segId].start;
		size = (u32)segmentData[segId].end-src;
		if(size!=0) {
			osInvalDCache((void*)dest,size);
			osPiStartDma(mqDmaBuf,OS_MESG_PRI_NORMAL,OS_READ,src,(void*)dest,size,&mqDma);
			osRecvMesg(&mqDma,NULL,OS_MESG_BLOCK);
		}
		//Mark as loaded
		loadedSegments[slot] = segId;
	}
}
//Update graphics
void update_gfx() {
	int i,j;
	//Handle camera (pre-process!)
	for(i=0; i<gfxUseBgL1; i++) {
		gfxBgLayer1[i].s.objX -= camxL1<<2;
		gfxBgLayer1[i].s.objY -= camyL1<<2;
	}
	for(i=0; i<gfxUseSp; i++) {
		gfxSprites[i].s.objX -= camxL1<<2;
		gfxSprites[i].s.objY -= camyL1<<2;
	}
	//Init RDP for clearing
	dlPtr = &dlBuf[bufferId][0];
	gSPSegment(dlPtr++,0x00,0);
	gSPDisplayList(dlPtr++,OS_K0_TO_PHYSICAL(gfxInit1));
	//Setup framebuffer
	gDPSetDepthImage(dlPtr++,OS_K0_TO_PHYSICAL(nuGfxZBuffer));
	gDPSetColorImage(dlPtr++,G_IM_FMT_RGBA,G_IM_SIZ_16b,320,OS_K0_TO_PHYSICAL(nuGfxZBuffer));
	gDPSetFillColor(dlPtr++,GPACK_ZDZ(G_MAXFBZ,0)<<16 | GPACK_ZDZ(G_MAXFBZ,0));
	gDPFillRectangle(dlPtr++,0,0,319,239);
	gDPPipeSync(dlPtr++);
	gDPSetColorImage(dlPtr++,G_IM_FMT_RGBA,G_IM_SIZ_16b,320,osVirtualToPhysical(nuGfxCfb_ptr));
	gDPSetFillColor(dlPtr++,GPACK_RGBA5551(0,0,128,1)<<16 | GPACK_RGBA5551(0,0,128,1));
	gDPFillRectangle(dlPtr++,0,0,319,239);
	gDPPipeSync(dlPtr++);
	//Init RDP for normal use
	gSPDisplayList(dlPtr++,OS_K0_TO_PHYSICAL(gfxInit2));
	//Generate display list for BG layer 2
	/*if(gfxUseBgL2) {
		gDPPipeSync(dlPtr++);
		gSPBgRect1Cyc(dlPtr++,OS_K0_TO_PHYSICAL(&gfxBgLayer2));
	}*/
	//Generate display list for sprites
	for(i=0; i<gfxUseSp; i++) {
		if(gfxDataSp[i] && gfxLayerSp[i]==0) {
			gDPPipeSync(dlPtr++);
			gDPLoadTextureBlock(dlPtr++,gfxDataSp[i],G_IM_FMT_RGBA,G_IM_SIZ_16b,
				gfxSprites[i].s.imageW>>5,
				gfxSprites[i].s.imageH>>5,
				0,G_TX_WRAP|G_TX_NOMIRROR,G_TX_WRAP|G_TX_NOMIRROR,
				G_TX_NOMASK,G_TX_NOMASK,G_TX_NOLOD,G_TX_NOLOD);
			gSPObjRectangle(dlPtr++,OS_K0_TO_PHYSICAL(&gfxSprites[i]));
		}
	}
	//Generate display list for BG layer 1
	for(i=0; i<gfxUseBgL1; i++) {
		if(gfxDataBgL1[i]) {
			gDPPipeSync(dlPtr++);
			gDPLoadTextureBlock(dlPtr++,gfxDataBgL1[i],G_IM_FMT_RGBA,G_IM_SIZ_16b,
				gfxBgLayer1[i].s.imageW>>5,
				gfxBgLayer1[i].s.imageH>>5,
				0,G_TX_WRAP|G_TX_NOMIRROR,G_TX_WRAP|G_TX_NOMIRROR,
				G_TX_NOMASK,G_TX_NOMASK,G_TX_NOLOD,G_TX_NOLOD);
			gSPObjRectangle(dlPtr++,OS_K0_TO_PHYSICAL(&gfxBgLayer1[i]));
		}
	}
	//Generate display list for sprites
	for(j=1; j<=3; j++) {
		for(i=0; i<gfxUseSp; i++) {
			if(gfxDataSp[i] && gfxLayerSp[i]==j) {
				gDPPipeSync(dlPtr++);
				gDPLoadTextureBlock(dlPtr++,gfxDataSp[i],G_IM_FMT_RGBA,G_IM_SIZ_16b,
					gfxSprites[i].s.imageW>>5,
					gfxSprites[i].s.imageH>>5,
					0,G_TX_WRAP|G_TX_NOMIRROR,G_TX_WRAP|G_TX_NOMIRROR,
					G_TX_NOMASK,G_TX_NOMASK,G_TX_NOLOD,G_TX_NOLOD);
				gSPObjRectangle(dlPtr++,OS_K0_TO_PHYSICAL(&gfxSprites[i]));
			}
		}
	}
	//End display list
	gDPFullSync(dlPtr++);
	gSPEndDisplayList(dlPtr++);
	//Send display list to RSP
	nuGfxTaskStart(&dlBuf[bufferId][0],(s32)(dlPtr-dlBuf[bufferId])*sizeof(Gfx),NU_GFX_UCODE_S2DEX2,NU_SC_SWAPBUFFER);
	nuGfxTaskAllEndWait();
	//Swap buffers
	bufferId ^= 1;
	//Handle camera (post-process!)
	for(i=0; i<gfxUseBgL1; i++) {
		gfxBgLayer1[i].s.objX += camxL1<<2;
		gfxBgLayer1[i].s.objY += camyL1<<2;
	}
	for(i=0; i<gfxUseSp; i++) {
		gfxSprites[i].s.objX += camxL1<<2;
		gfxSprites[i].s.objY += camyL1<<2;
	}
}
