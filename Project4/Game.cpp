#include "Game.h"

Camera camera;
Map map;
Ryu ryu;
Stage stage;
ScoreBoard scoreBoard;

Wall *walls;
int wallsNum;

vector<LPEnemy> enemies;
vector<LPContainer> containers;
vector<LPItem> items;

bool GameOver;
Sprite SpriteGameOver;

Grid grid;

float _timeStop;


int Game_Init(HWND hWnd)
{
	addSound("Resource/Sounds/attack.wav");
	addSound("Resource/Sounds/attacked.wav");
	addSound("Resource/Sounds/boss-die.wav");
	addSound("Resource/Sounds/boss-jump.wav");
	addSound("Resource/Sounds/enemy-die.wav");
	addSound("Resource/Sounds/jump.wav");
	addSound("Resource/Sounds/pick-item.wav");
	addSound("Resource/Sounds/stage3_1_bgm.wav");
	addSound("Resource/Sounds/stage3_2_bgm.wav");
	addSound("Resource/Sounds/stageboss_bgm.wav");
	addSound("Resource/Sounds/pause.wav");
	addSound("Resource/Sounds/score_count.wav");
	addSound("Resource/Sounds/skill.wav");
	_timeStop = 0;
	stage = Stage("Resource/Stage/StageInfo.txt");
	scoreBoard = ScoreBoard("Resource/ScoreBoard/ascii_8x8.bmp");
	SpriteGameOver = Sprite("Resource/GameOver.bmp", 0, 0, 148, 60, 1, 0);
	GameOver = true;
	Change_Stage(0, 0);
	GameOver = false;
	return 1;
}

void Game_Run(HWND hWnd)
{
	//reacquire input
	dikeyboard->Acquire();
	dimouse->Acquire();
	Poll_Keyboard();
	Poll_Mouse();
	
	//Update
	if (!GameOver)
		Update();
	else
	{
		if (Key_Down(DIK_RETURN))
		{
			Change_Stage(stage._stage - 1, 0);
			GameOver = false;
			return;
		}
		switch (stage._stage-1)
		{
		case 0:
			stopSound(stage3_1_bgm);
			break;
		case 1:
			stopSound(stage3_2_bgm);
			break;
		case 2:
			stopSound(stageboss_bgm);
			break;
		default:
			break;
		}
		SpriteGameOver._X = camera._X + 125;
		SpriteGameOver._Y = camera._Y - 135;
	}

	//start render
	if (d3ddev == NULL)
		return;

	if (d3ddev->BeginScene())
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		
		//spritehandler render
		spritehandler->Begin(D3DXSPRITE_ALPHABLEND);

		map.Render(camera);
		ryu.Render(camera);

		for (int i = 0; i < enemies.size(); i++)
			enemies[i]->Render(camera);

		for (int i = 0; i < containers.size(); i++)
			containers[i]->Render(camera);

		for (int i = 0; i < items.size(); i++)
			items[i]->Render(camera);

		scoreBoard.Render(camera, ryu._HP, ryu._skillType);

		if (GameOver)
			SpriteGameOver.Render(camera, SpriteGameOver.rect);

		spritehandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}
	

void Game_End(HWND hWnd)
{
	if (d3d != NULL) d3d->Release();
	if (d3ddev != NULL) d3ddev->Release();
	if (backbuffer != NULL) backbuffer->Release();
	if (spritehandler != NULL) spritehandler->Release();
	if (dinput != NULL) dinput->Release();
	if (font != NULL) font->Release();
	Kill_Keyboard();
	Kill_Mouse();
	map.KillSprite();
	ryu.Remove();
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->EnemyDelete();
		delete enemies[i];
	}
	enemies.clear();

	for (int i = 0; i < containers.size(); i++)
	{
		containers[i]->ContainerDelete();
		delete containers[i];
	}
	containers.clear();

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->ItemDelete();
		delete items[i];
	}
	items.clear();

	if (walls) delete[] walls;
	grid.GridClear();
	scoreBoard.ScoreBoardDelete();
}

void Change_Stage(int prev, int now)
{
	stage._stage = now;
	//clear
	map.KillSprite();

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->EnemyDelete();
		delete enemies[i];
	}
	enemies.clear();

	for (int i = 0; i < containers.size(); i++)
	{
		containers[i]->ContainerDelete();
		delete containers[i];
	}
	containers.clear();

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->ItemDelete();
		delete items[i];
	}
	items.clear();

	if (walls) delete[] walls;

	grid.GridClear();

	////init
	//playBGM
	switch (prev)
	{
	case 0:
		stopSound(stage3_1_bgm);
		break;
	case 1:
		stopSound(stage3_2_bgm);
		break;
	case 2:
		stopSound(stageboss_bgm);
		break;
	default:
		break;
	}
	switch (now)
	{
	case 0:
		playSound(stage3_1_bgm, true, 1);
		break;
	case 1:
		playSound(stage3_2_bgm, true, 1);
		break;
	case 2:
		playSound(stageboss_bgm, true, 1);
		break;
	default:
		break;
	}

	//Grid
	grid = Grid();

	//Map
	D3DXIMAGE_INFO info;
	string tmpMapImgStr, tmpMapTxtStr;
	tmpMapImgStr = tmpMapTxtStr = "Resource/Map/";
	tmpMapImgStr += stage._mapImg[stage._stage];
	tmpMapTxtStr += stage._mapTxt[stage._stage];
	HRESULT result = D3DXGetImageInfoFromFile(tmpMapImgStr.c_str(), &info);
	if (result != D3D_OK)
		return;
	map = Map(tmpMapTxtStr.c_str(), tmpMapImgStr.c_str(), 0, GAME_HEIGHT, 16, 16, info.Width / 16, 1);

	//Camera
	camera = Camera(stage._gameWidth[stage._stage]);

	//Ryu
	//if (ryu._lives == 0 && ryu._died)
	if (GameOver)
	{
		ryu.Remove();
		ryu = Ryu("Resource/Ryu/Ryu.bmp", stage._ryuPos[stage._stage].x, stage._ryuPos[stage._stage].y, NULL, NULL, 24, 10, "Resource/Ryu/Ryu.xml");
		scoreBoard.ScoreBoardDelete();
		scoreBoard = ScoreBoard("Resource/ScoreBoard/ascii_8x8.bmp");
	} 
	else ryu.ChangeStage(stage._ryuPos[stage._stage].x, stage._ryuPos[stage._stage].y);

	//Walls
	string tmpWallTxtStr = "Resource/Walls/";
	tmpWallTxtStr += stage._wallsTxt[stage._stage];
	ifstream walltxt;
	walltxt.open(tmpWallTxtStr.c_str());
	walltxt >> wallsNum;
	walls = new Wall[wallsNum];
	RECT wallrect;
	bool tmpleft, tmpright;
	for (int i = 0; i < wallsNum; i++)
	{
		walltxt >> wallrect.left >> wallrect.top >> wallrect.right >> wallrect.bottom >> tmpleft >> tmpright;
		walls[i] = Wall(wallrect, tmpleft, tmpright);
		grid.Add(&walls[i]);
	}
	walltxt.close();

	//Containers
	string tmpContainersTxtStr = "Resource/Container/";
	tmpContainersTxtStr += stage._containerTxt[stage._stage];
	LPContainer container;
	ifstream containertxt;
	containertxt.open(tmpContainersTxtStr);
	int containerNum;
	containertxt >> containerNum;
	for (int i = 0; i < containerNum; i++)
	{
		float a, b;
		int c, d;
		containertxt >> a >> b >> c >> d;
		switch (stage._stage+1)
		{
		case 1:
			container = new Container("Resource/Container/ContainerTypeA.bmp", a, b, NULL, NULL, 2, 10, "Resource/Container/ContainerTypeA.xml", (ItemDefine)c, d);
			containers.push_back(container);
			break;
		case 2:
			container = new Container("Resource/Container/ContainerTypeB.bmp", a, b, NULL, NULL, 2, 10, "Resource/Container/ContainerTypeB.xml", (ItemDefine)c, d);
			containers.push_back(container);
			break;
		case 3:
			break;
		default:
			break;
		}
	}
	containertxt.close();

	//Enemies
	string tmpEnemiesTxtStr = "Resource/Enemies/";
	tmpEnemiesTxtStr += stage._enemyTxt[stage._stage];
	LPEnemy enemy;
	ifstream enemiestxt;
	enemiestxt.open(tmpEnemiesTxtStr);
	int enemyNum;
	enemiestxt >> enemyNum;
	for (int i = 0; i < enemyNum; i++)
	{
		int type;
		float a, b, c, d;
		enemiestxt >> type;
		switch (type)
		{
		case SOLDIER_stage1:
			enemiestxt >> a >> b >> c >> d;
			enemy = new Soldier_stage1("Resource/Enemies/Soldier_stage1/Soldier_stage1.bmp", a, b, NULL, NULL,
				3, 10, "Resource/Enemies/Soldier_stage1/Soldier_stage1.xml", c, d);
			enemies.push_back(enemy);
			break;
		case BIRD_stage1:
			enemiestxt >> a >> b;
			enemy = new Bird_stage1("Resource/Enemies/Bird_stage1/Bird_stage1.bmp", a, b, NULL, NULL,
				2, 10, "Resource/Enemies/Bird_stage1/Bird_stage1.xml");
			enemies.push_back(enemy);
			break;
		case CAT_stage1:
			enemiestxt >> a >> b >> c >> d;
			enemy = new Cat_stage1("Resource/Enemies/Cat_stage1/Cat_stage1.bmp", a, b, NULL, NULL,
				2, 10, "Resource/Enemies/Cat_stage1/Cat_stage1.xml", c, d);
			enemies.push_back(enemy);
			break;
		case WIZARD_stage1:
			enemiestxt >> a >> b >> c >> d;
			enemy = new Wizard_stage1("Resource/Enemies/Wizard_stage1/Wizard_stage1.bmp", a, b, NULL, NULL,
				4, 10, "Resource/Enemies/Wizard_stage1/Wizard_stage1.xml", c, d);
			enemies.push_back(enemy);
			break;
		case GUNNER_stage1:
			enemiestxt >> a >> b >> c >> d;
			enemy = new Gunner_stage1("Resource/Enemies/Gunner_stage1/Gunner_stage1.bmp", a, b, NULL, NULL,
				5, 10, "Resource/Enemies/Gunner_stage1/Gunner_stage1.xml", c, d);
			enemies.push_back(enemy);
			break;
		default:
			break;
		case SNIPER_stage1:
			enemiestxt >> a >> b;
			enemy = new Sniper_stage1("Resource/Enemies/Sniper_stage1/Sniper_stage1.bmp", a, b, NULL, NULL,
				3, 10, "Resource/Enemies/Sniper_stage1/Sniper_stage1.xml");
			enemies.push_back(enemy);
			break;
		case TROOPER_stage1:
			enemiestxt >> a >> b >> c >> d;
			enemy = new Trooper_stage1("Resource/Enemies/Trooper_stage1/Trooper_stage1.bmp", a, b, NULL, NULL,
				2, 10, "Resource/Enemies/Trooper_stage1/Trooper_stage1.xml", c, d);
			enemies.push_back(enemy);
			break;
		case BOSS_stage1:
			enemiestxt >> a >> b;
			enemy = new Boss_stage1("Resource/Enemies/Boss_stage1/Boss_stage1.bmp", a, b, NULL, NULL,
				3, 10, "Resource/Enemies/Boss_stage1/Boss_stage1.xml");
			enemies.push_back(enemy);
			break;
		}
	}
	enemiestxt.close();

	scoreBoard._timer = 150;

	//
	grid.Output();
	stage._stage++;
}

void Update()
{
	//TimeStop
	if (_timeStop > 0)
		_timeStop -= 0.01f;

	//TimeOut
	if (scoreBoard._timer <= 0 && scoreBoard._bossHP != 0)
		ryu._died = true;

	//Ryu
	if (!ryu._died)
	{
		ryu.UpdateState();

		Box ryuBox_tmp = ryu.ToBox();
		RECT ryuRect = { ryuBox_tmp.x, ryuBox_tmp.y, ryuBox_tmp.x + ryuBox_tmp.width, ryuBox_tmp.y - ryuBox_tmp.height };

		vector<Wall*> wallCollision_tmp = grid.WallOut(ryuRect);

		int tmp;
		tmp = 0;
		for (int i = 0; i < wallCollision_tmp.size(); i++)
		{
			ryu.UpdateCollision(wallCollision_tmp[i]);
		}
		ryu.Update();
		if (stage._stage != 3 && ryu.GetPosX() > stage._gameWidth[stage._stage - 1] - 20)
		{
			Change_Stage(stage._stage - 1, stage._stage);
			return;
		}
	}
	else
	{
		if (ryu._lives > 0)
		{
			Change_Stage(stage._stage - 2, stage._stage - 1);
			return;
		}
		else
		{
			GameOver = true;
			return;
		}
	}

	// Enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetPosX() >= camera._X - 100 && enemies[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALE * 1.0f + 100)
		{
			if (!enemies[i]->_isAttacked && enemies[i]->_died == -1)
			{
				if (ryu.GetStateType() == ATTACK_state)
				{
					float normalX, normalY;
					Box tmpSwordBox = ryu.ToBoxSword();
					Box enemyBox = enemies[i]->ToBox();
					float tmpcollision = SweptAABB(tmpSwordBox, enemyBox, normalX, normalY);
					if (normalX != 0.0f || normalY != 0.0f || tmpcollision < 1.0f)
					{
						enemies[i]->_isAttacked = true;
						enemies[i]->_HP--;
						if (enemies[i]->_type == BOSS_stage1)
							scoreBoard._bossHP--;
						continue;
					}
				}
				if (ryu.GetSkill())
				{
					float normalX, normalY;
					Box tmpSkillBox = ryu.ToSkillBox();
					Box enemyBox = enemies[i]->ToBox();
					float tmpcollision = SweptAABB(tmpSkillBox, enemyBox, normalX, normalY);
					if (normalX != 0.0f || normalY != 0.0f || tmpcollision < 1.0f || OverlappedBox(tmpSkillBox, enemyBox))
					{
						enemies[i]->_isAttacked = true;
						enemies[i]->_HP--;
						if (enemies[i]->_type == BOSS_stage1)
						{
							scoreBoard._bossHP--;
							ryu.KillSkill();
						}
						continue;
					}
				}
			}
			if ((int)(_timeStop * 10) % 10 == 0 || enemies[i]->_HP <= 0)
			{
				LPEnemy enemy;
				enemy = enemies[i]->Update(&ryu);
				if (enemy)
					enemies.push_back(enemy);
			}
		}
		else if (enemies[i]->_type < 0)
			enemies[i]->_died = 0;
	}

	int i = 0;
	while (i < enemies.size())
	{
		if (enemies[i]->_died == 0)
		{
			if (enemies[i]->_HP <= 0)
				scoreBoard._score += enemies[i]->_score;
			enemies[i]->EnemyDelete();
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		else i++;
	}

	if (ryu.GetStateType() != STUN_state && ryu._invisible == 0)
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->_died == -1 && enemies[i]->GetPosX() >= camera._X && enemies[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALE * 1.0f)
			{
				float normalX, normalY;
				Box tmpBox = ryu.ToBox();
				Box enemyBox = enemies[i]->ToBox();
				float tmpcollision = SweptAABB(tmpBox, enemyBox, normalX, normalY);
				if (normalX != 0.0f || normalY != 0.0f || tmpcollision < 1.0f || OverlappedBox(tmpBox, enemyBox))
				{
					ryu._specialChange = STUN_state;
					break;
				}
			}
		}

	//container
	/*for (int i = 0; i < containers.size(); i++)
		containers[i]->Update();*/
	for (int i = 0; i < containers.size(); i++)
	{
		if (containers[i]->GetPosX() >= camera._X - 100 && containers[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALE * 1.0f + 100)
		{
			if (ryu.GetStateType() == ATTACK_state && !containers[i]->_died)
			{
				float normalX, normalY;
				Box tmpSwordBox = ryu.ToBoxSword();
				Box containersBox = containers[i]->ToBox();
				float tmpcollision = SweptAABB(tmpSwordBox, containersBox, normalX, normalY);
				if (normalX != 0.0f || normalY != 0.0f || tmpcollision < 1.0f || OverlappedBox(tmpSwordBox, containersBox))
				{
					containers[i]->_died = true;
				}
			}
			if (!containers[i]->_died && ryu.GetSkill())
			{
				float normalX, normalY;
				Box tmpSkillBox = ryu.ToSkillBox();
				Box containersBox = containers[i]->ToBox();
				float tmpcollision = SweptAABB(tmpSkillBox, containersBox, normalX, normalY);
				if (normalX != 0.0f || normalY != 0.0f || tmpcollision < 1.0f)
				{
					containers[i]->_died = true;
				}
			}
			LPItem item;
			item = containers[i]->Update();
			if (item)
				items.push_back(item);
		}
	}

	i = 0;
	while (i < containers.size())
	{
		if (containers[i]->_died)
		{
			containers[i]->ContainerDelete();
			delete containers[i];
			containers.erase(containers.begin() + i);
		}
		else i++;
	}

	//Item
	for (int i = 0; i < items.size(); i++)
		items[i]->Update();
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->_activate == 0 && items[i]->GetPosX() >= camera._X - 100 && items[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALE * 1.0f + 100)
		{
			float normalX, normalY;
			Box tmpRyuBox = ryu.ToBox();
			Box itemsBox = items[i]->ToBox();
			if (OverlappedBox(tmpRyuBox, itemsBox))
			{
				playSound(pick_item_sound);
				switch (items[i]->_id)
				{
				case LiveUp:
					ryu._lives++;
					break;
				case PtsBonus_A:
					scoreBoard._score += 500;
					break;
				case PtsBonus_B:
					scoreBoard._score += 1000;
					break;
				case HPRecover:
					ryu._HP = 16;
					break;
				case MPRecover_A:
					ryu._MP += 5;
					break;
				case MPRecover_B:
					ryu._MP += 10;
					break;
				case Dart_A:
					ryu._skillType = DartA_skill;
					break;
				case Dart_B:
					ryu._skillType = DartB_skill;
					break;
				case TimeStop:
					_timeStop = 5;
					break;
				default:
					break;
				}
				items[i]->_died = true;
			}
		}
	}
	i = 0;
	while (i < items.size())
	{
		if (items[i]->_died)
		{
			items[i]->ItemDelete();
			delete items[i];
			items.erase(items.begin() + i);
		}
		else i++;
	}

	//camera
	camera.Update(ryu.GetPosX());

	//ScoreBoard
	scoreBoard.Update(stage._stage, ryu._lives, ryu._MP, false);

	if (scoreBoard._bossHP == 0 && scoreBoard._timer <= 0)
		GameOver = true;
}