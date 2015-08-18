#pragma once
#include "SDL.h"
#include "Player_Object.h"
#include "Game_Renderer.h"
#include "Game_Room.h"
#include "RoomLoader.h"
#include "Camera.h"
#include "LevelSize.h"

class Game_World{
	
public:

	bool InitWorld();
	bool LoadNewLevel();
	void Update();
	void Render();
	void GameOver();
	void GameWon();
	void HandleKeyBoard(const Uint8* keyState);
	void CheckForPlayerCollisions();
	void CheckForPlayerCollisionsALTER();
	



private:

	Camera mCamera;
	Game_Room currentLoadedRoom;
	Game_Renderer mRenderer;
	Player_Object* mPlayer;
	//vector<Enemy_Object*> m Enemies;
	//vector<Collectible_Object*> mItems;
	//vector<Ballistic_Object*> mBallistic;


};