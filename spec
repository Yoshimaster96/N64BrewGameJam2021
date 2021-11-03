#include <nusys.h>

////////////
//SEGMENTS//
////////////
//Common data
beginseg
	name "code"
	flags BOOT OBJECT
	entry nuBoot
	address NU_SPEC_BOOT_ADDR
	stack NU_SPEC_BOOT_STACK
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/n_aspMain.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspL3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.NoN.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DLX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspS2DEX2.fifo.o"
endseg
/*beginseg
	name "seq"
	flags RAW
	include "data/sound/midi.sbk"
endseg
beginseg
	name "midibank"
	flags RAW
	include "data/sound/wave.ctl" 
endseg
beginseg
	name "miditable"
	flags RAW
	include "data/sound/wave.tbl" 
endseg
beginseg
	name "sfxbank"
	flags RAW
	include "data/sound/se.ctl" 
endseg
beginseg
	name "sfxtable"
	flags RAW
	include "data/sound/se.tbl" 
endseg*/

//Common and mode graphics
beginseg
	name "gfx_common"
	flags OBJECT
	address 0x80200000
	include "data/graphics/gfx_common.o"
endseg
beginseg
	name "gfx_title"
	flags OBJECT
	address 0x80240000
	include "data/graphics/gfx_title.o"
endseg
beginseg
	name "gfx_over"
	flags OBJECT
	address 0x80240000
	include "data/graphics/gfx_over.o"
endseg
beginseg
	name "gfx_ending"
	flags OBJECT
	address 0x80240000
	include "data/graphics/gfx_ending.o"
endseg

//Level graphics
beginseg
	name "gfx_level1"
	flags OBJECT
	address 0x80280000
	include "data/graphics/gfx_level1.o"
endseg
beginseg
	name "gfx_level2"
	flags OBJECT
	address 0x80280000
	include "data/graphics/gfx_level1.o"
endseg
beginseg
	name "gfx_level3"
	flags OBJECT
	address 0x80280000
	include "data/graphics/gfx_level1.o"
endseg
beginseg
	name "gfx_level4"
	flags OBJECT
	address 0x80280000
	include "data/graphics/gfx_level1.o"
endseg

////////
//WAVE//
////////
beginwave
	name "main"
	include "code"
	//include "seq"
	//include "midibank"
	//include "miditable"
	//include "sfxbank"
	//include "sfxtable"
	include "gfx_common"
	include "gfx_title"
	include "gfx_over"
	include "gfx_ending"
	include "gfx_level1"
	include "gfx_level2"
	include "gfx_level3"
	include "gfx_level4"
endwave
