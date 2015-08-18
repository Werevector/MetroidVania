#include "Game_World.h"

//At the start the game will have a dummy version of the player for testing movement
bool Game_World::InitWorld(){
							  // X   Y  Tex  HP
	mPlayer = new Player_Object(50,100, 100);
	
	SDL_Rect collBox;
	collBox.x = mPlayer->ReturnPositon().x - 50;
	collBox.y = mPlayer->ReturnPositon().y - 50;
	collBox.h = 50;
	collBox.w = 20;

	SDL_Rect selectorBox;
	selectorBox.x = mPlayer->ReturnPositon().x - 50;
	selectorBox.y = mPlayer->ReturnPositon().y - 50;
	selectorBox.h = 100;
	selectorBox.w = 50;
	
	mPlayer->SetCollisionBox(collBox);
	mPlayer->SetSelectorBox(selectorBox);
	
	mRenderer.InitRenderer();
	LoadNewLevel();
	
	mCamera.CameraW = Settings::WINDOW_WIDTH;
	mCamera.CameraH = Settings::WINDOW_HEIGHT;

	mCamera.CameraX = mPlayer->ReturnPositon().x - mCamera.CameraW;
	mCamera.CameraY = mPlayer->ReturnPositon().y - mCamera.CameraH;
	
	return mRenderer.LoadSpriteSheet("platformer.png");
}

bool Game_World::LoadNewLevel(){

	//LoadDummyRoom(&dummyRoom);

	LoadRoomFromTmxFile("TestMap3.tmx", &currentLoadedRoom);
	//currentLoadedRoom = LoadRoomFromTmxFile("map1.tmx");


	return true;
}

void Game_World::Update(){
	mPlayer->Update();
	CheckForPlayerCollisions();
	
	mCamera.CameraX = mPlayer->ReturnPositon().x - mCamera.CameraW/2;
	mCamera.CameraY = mPlayer->ReturnPositon().y - mCamera.CameraH/2;

	//Keep the camera in bounds 
	if (mCamera.CameraX < 0) { mCamera.CameraX = 0; }
	if (mCamera.CameraY < 0) { mCamera.CameraY = 0; }

	if (mCamera.CameraX > LEVEL_WIDTH_M - mCamera.CameraW) { mCamera.CameraX = LEVEL_WIDTH_M - mCamera.CameraW; }
	if (mCamera.CameraY > LEVEL_HEIGHT_M - mCamera.CameraH) { mCamera.CameraY = LEVEL_HEIGHT_M - mCamera.CameraH; }

}

void Game_World::Render(){
	
	mRenderer.ReadyRendering(mCamera);
	mRenderer.RenderPlayerInstance(mPlayer->ReturnPositon().x, mPlayer->ReturnPositon().y, mPlayer->GetTextureKey());
	mRenderer.RenderRoom(&currentLoadedRoom);
	
	mRenderer.RenderBounding(mPlayer->GetCollisionBoxP()->GetBoundingBox(), COLOR::GREEN);
	mRenderer.RenderBounding(mPlayer->GetSelectorBoxP()->GetBoundingBox(), COLOR::BLUE);
	mRenderer.RenderCollPoints(mPlayer->ReturnPositon().x - 20, mPlayer->ReturnPositon().y - 30, mPlayer->GetCollisionBoxP());

	//CheckForPlayerCollisions();
	mRenderer.FlipBuffer();

}

void Game_World::CheckForPlayerCollisions(){


	//Flag, if a collision is in effect
	bool collision = false;
	bool resolved = false;

	//inits for values used in determining collison
	SDL_Point playerPos = mPlayer->ReturnPositon();
	std::vector<Game_Tile*> selected_Tiles;
	SDL_Rect* selectorBounding = mPlayer->GetSelectorBoxP()->GetBoundingBox();
	SDL_Rect* currentBounding = nullptr;

	//Selecting the tiles that the player bounding box is touching
	for (Game_Tile* tile : currentLoadedRoom.TileMap){
		currentBounding = tile->GetBoundingBox();

		if (SDL_HasIntersection(selectorBounding, currentBounding)){
			selected_Tiles.push_back(tile);
		}

	}
	
	//Fetch collison points
	int test = 0;
	bool grounded = false;
	std::vector<std::vector<int>>* pointArray = mPlayer->GetCollisionBoxP()->GetCollisionPointArrayP();
	
	do{
		collision = false;
		for (int dir = 0; dir < 4 && !collision; dir++){
			
			for (int i = 0; i < 2; i++){
				test = (dir * 2) + i;
				for (Game_Tile* tile : selected_Tiles){
					if ((*pointArray)[(dir * 2) + i][0] > tile->x && (*pointArray)[(dir * 2) + i][0] < (tile->x + tile->w) && (*pointArray)[(dir * 2) + i][1] > tile->y && (*pointArray)[(dir * 2) + i][1] < (tile->y + tile->h)){
						collision = true;

					}
				}
			}

			if (collision){
				DIRECTION direction = (DIRECTION)dir;
				mPlayer->PartialCollResolve(direction);
				std::cout << selected_Tiles.size();
				if (direction == DOWN) grounded = true;

			}

		}
		

	} while (collision);

	if (grounded) mPlayer->Ground();

	mPlayer->MoveToDesired();

}

void Game_World::CheckForPlayerCollisionsALTER(){
	//Flag, if a collision is in effect
	bool collision = false;
	bool resolved = false;

	//inits for values used in determining collison
	SDL_Point playerPos = mPlayer->ReturnPositon();
	std::vector<Game_Tile*> selected_Tiles;
	SDL_Rect* selectorBounding = mPlayer->GetSelectorBoxP()->GetBoundingBox();
	SDL_Rect* currentBounding = nullptr;

	//Selecting the tiles that the player bounding box is touching
	for (Game_Tile* tile : currentLoadedRoom.TileMap){
		currentBounding = tile->GetBoundingBox();

		if (SDL_HasIntersection(selectorBounding, currentBounding)){
			selected_Tiles.push_back(tile);
		}

	}
}

void Game_World::HandleKeyBoard(const Uint8* keyState){



	if (keyState[SDL_SCANCODE_LEFT]){
		mPlayer->Walk(LEFT_FLIP);
	}

	if (keyState[SDL_SCANCODE_RIGHT]){
		mPlayer->Walk(RIGHT_FLIP);
	}

	if (keyState[SDL_SCANCODE_X]){
		mPlayer->Jump();
	}
	else{
		mPlayer->jumpKeyDown = false;
	}

}

void Game_World::GameOver(){

}

void Game_World::GameWon(){

}



