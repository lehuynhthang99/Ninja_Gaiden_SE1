#include "Game.h"

Camera camera;
Map map;
Ryu ryu;
Stage stage;

Wall *walls;
int wallsNum;

vector<LPEnemy> enemies;
vector<LPContainer> containers;
vector<LPItem> items;

Grid grid;


int Game_Init(HWND hWnd)
{
	stage = Stage("Resource/Stage/StageInfo.txt");
	//stage._stage+=2;
	Change_Stage();
	return 1;
}

void Game_Run(HWND hWnd)
{
	//reacquire input
	dikeyboard->Acquire();
	dimouse->Acquire();
	Poll_Keyboard();
	Poll_Mouse();

	//Ryu
	if (!ryu._died) 
	{
		ryu.UpdateState();

		Box ryuBox_tmp = ryu.ToBox();
		RECT ryuRect = { ryuBox_tmp.x, ryuBox_tmp.y, ryuBox_tmp.x + ryuBox_tmp.width, ryuBox_tmp.y - ryuBox_tmp.height };

		vector<Wall*> wallCollision_tmp = grid.WallOut(ryuRect);

		int tmp;
		tmp = 0;
		for (int i = 0; i<wallCollision_tmp.size(); i++)
		{
			ryu.UpdateCollision(wallCollision_tmp[i]);
		}
		ryu.Update();
		if (stage._stage != 3 && ryu.GetPosX() > stage._gameWidth[stage._stage - 1] - 50)
		{
			Change_Stage();
			return;
		}
	}
	else 
	{
		stage._stage--;
		Change_Stage();
		return;
	}

	// Enemy

	for (int i=0; i<enemies.size(); i++)
	{
		if (enemies[i]->GetPosX() >= camera._X - 100 && enemies[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALEX * 1.0f + 100)
		{
			if (ryu.GetStateType() == ATTACK_state && !enemies[i]->_isAttacked && enemies[i]->_died == -1)
			{
				float normalX, normalY;
				Box tmpSwordBox = ryu.ToBoxSword();
				Box enemyBox = enemies[i]->ToBox();
				float tmpcollision = SweptAABB(tmpSwordBox, enemyBox, normalX, normalY);
				/*DebugOut((wchar_t*)L"tmpColli: %f %f %f\n", tmpcollision, normalX, normalY);
				DebugOut((wchar_t*)L"tmpSwordBox: %f %f %f %f %f %f\n", 
					tmpSwordBox.x, tmpSwordBox.y, tmpSwordBox.vx, tmpSwordBox.vy, tmpSwordBox.width, tmpSwordBox.height);
				DebugOut((wchar_t*)L"enemyBox: %d %f %f %f %f %f %f\n",
					enemies[i]->_type, enemyBox.x, enemyBox.y, enemyBox.vx, enemyBox.vy, enemyBox.width, enemyBox.height);*/
				if (enemies[i]->_type == SNIPERBULLET_stage1)
				{
					DebugOut((wchar_t*)L"tmpColli: %f %f %f\n", tmpcollision, normalX, normalY);
					DebugOut((wchar_t*)L"tmpSwordBox: %f %f %f %f %f %f\n",
						tmpSwordBox.x, tmpSwordBox.y, tmpSwordBox.vx, tmpSwordBox.vy, tmpSwordBox.width, tmpSwordBox.height);
					DebugOut((wchar_t*)L"enemyBox: %d %f %f %f %f %f %f\n\n",
						enemies[i]->_type, enemyBox.x, enemyBox.y, enemyBox.vx, enemyBox.vy, enemyBox.width, enemyBox.height);
				}
				if (normalX != 0.0f || normalY != 0.0f || tmpcollision < 1.0f)
				{
					enemies[i]->_isAttacked = true;
					enemies[i]->_HP--;
					continue;
				}
			}
			LPEnemy enemy;
			enemy = enemies[i]->Update(&ryu);
			if (enemy)
				enemies.push_back(enemy);
		}
		else if (enemies[i]->_type < 0)
			enemies[i]->_died = 0;
	}

	int i = 0;
	while (i < enemies.size())
	{
		if (enemies[i]->_died == 0)
		{
			enemies[i]->EnemyDelete();
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		else i++;
	}


	if (ryu.GetStateType() != STUN_state && ryu._invisible == 0)
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->_died == -1 && enemies[i]->GetPosX() >= camera._X && enemies[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALEX * 1.0f)
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
		if (containers[i]->GetPosX() >= camera._X - 100 && containers[i]->GetPosX() <= camera._X + SCREEN_WIDTH / SCALEX * 1.0f + 100)
		{
			if (ryu.GetStateType() == ATTACK_state && !containers[i]->_died)
			{
				float normalX, normalY;
				Box tmpSwordBox = ryu.ToBoxSword();
				Box containersBox = containers[i]->ToBox();
				float tmpcollision = SweptAABB(tmpSwordBox, containersBox, normalX, normalY);
				/*DebugOut((wchar_t*)L"tmpColli: %f %f %f\n", tmpcollision, normalX, normalY);
				DebugOut((wchar_t*)L"tmpSwordBox: %f %f %f %f %f %f\n",
					tmpSwordBox.x, tmpSwordBox.y, tmpSwordBox.vx, tmpSwordBox.vy, tmpSwordBox.width, tmpSwordBox.height);
				DebugOut((wchar_t*)L"enemyBox: %d %f %f %f %f %f %f\n",
					enemies[i]->_type, enemyBox.x, enemyBox.y, enemyBox.vx, enemyBox.vy, enemyBox.width, enemyBox.height);*/
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

	//camera
	camera.Update(ryu.GetPosX());

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

		spritehandler->End();

		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);

	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hWnd, WM_DESTROY, 0, 0);
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
}

void Change_Stage()
{
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
	if (ryu._died)
	{
		ryu.Remove(); 
		ryu = Ryu("Resource/Ryu/Ryu.bmp", stage._ryuPos[stage._stage].x, stage._ryuPos[stage._stage].y, NULL, NULL, 24, 10, "Resource/Ryu/Ryu.xml");
	}
	else ryu.SetStartPos(stage._ryuPos[stage._stage].x, stage._ryuPos[stage._stage].y);

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

	//
	grid.Output();
	stage._stage++;
}

