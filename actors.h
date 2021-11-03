#ifndef ACTORS_H
#define ACTORS_H

//Includes
#include <ultra64.h>
#include <nusys.h>
#include "level.h"

//Variables
u8 joy1Pattern;
NUContData joy1Data;
u16 joy1ButtonPrev,joy1ButtonDown,joy1ButtonUp;

//Functions
void clear_actors();
void add_actor(u16 id,u8 param,int x,int y,u16 link);
void update_actors();

#endif
