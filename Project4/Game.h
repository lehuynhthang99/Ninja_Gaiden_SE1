#pragma once
#include <d3dx9math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sprite.h"  
#include "dxgraphics.h"
#include "dxinput.h"
#include "dxsound.h"
#include "Collision.h"
#include "Map.h"
#include "Ryu.h"
#include "Wall.h"
#include "Grid.h"
#include <string>
#include "Soldier_stage1.h"
#include "Bird_stage1.h"
#include "Wizard_stage1.h"
#include "WizardBullet_stage1.h"
#include "Gunner_stage1.h"
#include "GunnerBullet_stage1.h"
#include "Sniper_stage1.h"
#include "SniperBullet_stage1.h"
#include "BossBullet_stage1.h"
#include "Boss_stage1.h"
#include "Cat_stage1.h"
#include "Trooper_stage1.h"
#include "Stage.h"
#include "Container.h"
#include "ScoreBoard.h"


using namespace std;

#define APPTITLE "Camera"

#define SPEED_BALL 3


#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1:0)
#define	  KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1:0)

int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);
void Change_Stage(int, int);
void Update();