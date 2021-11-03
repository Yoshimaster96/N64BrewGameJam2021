#include "main.h"

//////////////
//GAME MODES//
//////////////
//Game mode variables
u16 gameMode = 0x00;
u16 gameModeTimer = 0;

//Game mode funcs
//Title
void gm_title_init() {
	//Init title
	load_segment(0);
	load_segment(1);
	clear_level();
	clear_actors();
	add_actor(0x0004,0x00,0,0,0xFFFF);
	load_bgm(0);
	//Go to next task
	gameMode = 0x01;
}
void gm_title_main() {
	//Animate title screen
	update_actors();
	//Wait for start press
	if(joy1ButtonDown&START_BUTTON) {
		//Play sound effect
		//TODO
		//Go to next task
		gameMode = 0x02;
		gameModeTimer = 0;
	}
}
void gm_title_wait() {
	//Animate title screen
	update_actors();
	//Wait for sound effect to finish
	gameModeTimer++;
	if(gameModeTimer>90) {
		//Init level variables
		levelNum = 0;
		areaNum = 0;
		playerLives = 3;
		playerScore = 0;
		//Go to next task
		gameMode = 0x04;
	}
}
//Main game
void gm_ready_init() {
	//Init ready screen
	clear_level();
	clear_actors();
	add_actor(0x0007,0x00,0,0,0xFFFF);
	load_bgm(3);
	//Go to next task
	gameMode = 0x05;
	gameModeTimer = 0;
}
void gm_ready_main() {
	//Animate ready screen
	update_actors();
	//Wait for animation to finish
	gameModeTimer++;
	if(gameModeTimer>150) {
		//Go to next task
		gameMode = 0x06;
	}
}
void gm_play_init() {
	//Init level
	load_level();
	//Go to next task
	gameMode = 0x07;
}
void gm_play_main() {
	//Do gameplay
	update_level();
	update_actors();
	//Check player status and update mode
	if(playerMode!=0xFF) {
		gameMode = playerMode;
	}
}
//Level ending
void gm_death_init() {
	//Init death
	actPlayer->vy = -0x40;
	//TODO
	//Go to next task
	gameMode = 0x09;
	gameModeTimer = 0;
}
void gm_death_main() {
	//Animate death scene
	update_actors();
	//Wait for animation to finish
	gameModeTimer++;
	if(gameModeTimer>180) {
		//Go to next task
		playerLives--;
		if(playerLives==0) gameMode = 0x0C;
		else               gameMode = 0x04;
	}
}
void gm_goal_init() {
	//Init goal
	//TODO
	//Go to next task
	gameMode = 0x0B;
	gameModeTimer = 0;
}
void gm_goal_main() {
	//Animate goal scene
	update_actors();
	//Wait for animation to finish
	gameModeTimer++;
	if(gameModeTimer>180) {
		//Go to next task
		levelNum++;
		if(levelNum>4) gameMode = 0x0E;
		else           gameMode = 0x04;
	}
}
//Game ending
void gm_over_init() {
	//Init game over
	load_segment(2);
	clear_level();
	clear_actors();
	add_actor(0x0005,0x00,0,0,0xFFFF);
	load_bgm(1);
	//Go to next task
	gameMode = 0x0D;
	gameModeTimer = 0;
}
void gm_over_main() {
	//Animate game over screen
	update_actors();
	//Wait for animation to finish
	gameModeTimer++;
	if(gameModeTimer>300) {
		//Go to next task
		gameMode = 0x00;
	}
}
void gm_ending_init() {
	//Init ending
	load_segment(3);
	clear_level();
	clear_actors();
	add_actor(0x0006,0x00,0,0,0xFFFF);
	load_bgm(2);
	//Go to next task
	gameMode = 0x0F;
	gameModeTimer = 0;
}
void gm_ending_main() {
	//Animate ending screen
	update_actors();
	//Wait for animation to finish
	gameModeTimer++;
	if(gameModeTimer>600) {
		//Go to next task
		gameMode = 0x00;
	}
}

//GAME MODE FUNCS
void (*gmFuncs[0x10])() = {
	//Title
	gm_title_init,		//00 (init)
	gm_title_main,		//01 (main)
	gm_title_wait,		//02 (wait)
	NULL,				//03 (DUMMY FOR ALIGNMENT)
	//Main game
	gm_ready_init,		//04 (ready screen init)
	gm_ready_main,		//05 (ready screen main)
	gm_play_init,		//06 (gameplay init)
	gm_play_main,		//07 (gameplay main)
	//Level ending
	gm_death_init,		//08 (death ending init)
	gm_death_main,		//09 (death ending main)
	gm_goal_init,		//0A (win ending init)
	gm_goal_main,		//0B (win ending main)
	//Game ending
	gm_over_init,		//0C (death ending init)
	gm_over_main,		//0D (death ending main)
	gm_ending_init,		//0E (win ending init)
	gm_ending_main};	//0F (win ending main)
//Run game mode
void run_mode_func() {
	if(gameMode>=0x10) {
		//Oops, something happened! Time to reset the game
		gameMode = 0x00;
	} else {
		//Run game mode
		(*gmFuncs[gameMode])();
	}
}

////////////////
//MAIN PROGRAM//
////////////////
//Main game loop
void main_loop(int nPendingGfxTasks) {
	if(nPendingGfxTasks<3) {
		//Update graphics
		update_gfx();
	}
	//Update input
	if(joy1Pattern&1) {
		//Save previous buttons
		joy1ButtonPrev = joy1Data.button;
		//Get new buttons
		nuContDataGetEx(&joy1Data,0);
		//Get button up/down status
		joy1ButtonDown	= joy1Data.button&(~joy1ButtonPrev) ;
		joy1ButtonUp	= joy1ButtonPrev &(~joy1Data.button);
	}
	//Run game mode
	run_mode_func();
}
//Entry point
void mainproc() {
	//Init GFX
	nuGfxInit();
	nuGfxFuncSet((NUGfxFunc)main_loop);
	nuGfxDisplayOn();
	//Init controller
	joy1Pattern = nuContInit();
	//Init audio
	/*nuAuInit();
	nuAuSeqPlayerBankSet(_midibankSegmentRomStart,
		_midibankSegmentRomEnd-_midibankSegmentRomStart,
		_miditableSegmentRomStart);
	nuAuSndPlayerBankSet(_sfxbankSegmentRomStart,
		_sfxbankSegmentRomEnd-_sfxbankSegmentRomStart,
		_sfxtableSegmentRomStart);
	nuAuSeqPlayerSeqSet(_seqSegmentRomStart);*/
	//Main game loop
	while(1);
}
