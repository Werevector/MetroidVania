#include "Game_Renderer.h"


bool Game_Renderer::InitRenderer(){

	//mWindow = SDL_CreateWindow("MetroidVania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	mWindow = SDL_CreateWindow("MetroidVania", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

	mCamera.CameraX = 0;
	mCamera.CameraY = 0;
	mCamera.CameraW = 0;
	mCamera.CameraH = 0;

	return true;

}

bool Game_Renderer::LoadSpriteSheet(std::string path){
	
	//--------------------------------
	//Dummy function, it is incomplete
	if (!mTextureSheet.loadFromFile(mRenderer, path)){
		printf("Cannot load character spritesheet");
		return false;
	}
	else{

		for (int y = 0; y < 8; ++y){
			for (int x = 0; x < 8; ++x){
				mClipCollection[(y * 8) + x].x = 0 + (x * 64);
				mClipCollection[(y * 8) + x].y = 0 + (y * 64);
				mClipCollection[(y * 8) + x].w = 64;
				mClipCollection[(y * 8) + x].h = 64;

			}

		}

	}

	if (!mMapTextureSheet.loadFromFile(mRenderer, "testtiles.png")){
		printf("Cannot load spritesheet testtiles.png");
		return false;
	}
	else{
		mMapClipCollection[0].x = 0 + 24 * 0;
		mMapClipCollection[0].y = 0 + 24 * 0;
		mMapClipCollection[0].h = 24;
		mMapClipCollection[0].w = 24;

		mMapClipCollection[1].x = 0 + 24 * 1;
		mMapClipCollection[1].y = 0 + 24 * 0;
		mMapClipCollection[1].h = 24;
		mMapClipCollection[1].w = 24;

		mMapClipCollection[2].x = 0 + 24 * 0;
		mMapClipCollection[2].y = 0 + 24 * 1;
		mMapClipCollection[2].h = 24;
		mMapClipCollection[2].w = 24;
	}

	return true;
}

void Game_Renderer::RenderPlayerInstance(int Xpos, int Ypos, TextureKey tex_Key){
	//Get the clip connected to the tex_Key
	SDL_Rect mCurrentClip = mClipCollection.find(tex_Key.clip_key)->second;
	
	mTextureSheet.render(mRenderer, (Xpos - (mCurrentClip.w / 2)) - mCamera.CameraX, (Ypos - (mCurrentClip.h / 2)) - mCamera.CameraY, &mCurrentClip, NULL, NULL, tex_Key.flipping);
	
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_Rect centerRect;
	centerRect.x = Xpos - (5 / 2) - mCamera.CameraX;
	centerRect.y = Ypos - (5 / 2) - mCamera.CameraY;
	centerRect.w = 5;
	centerRect.h = 5;
	SDL_RenderFillRect(mRenderer, &centerRect);

}

void Game_Renderer::RenderRoom(Game_Room* room){
	SDL_Rect mCurrentClip;
	
	for (auto t : room->TileMap){

		mCurrentClip = mMapClipCollection.find((int)t->mTileType)->second;
		mMapTextureSheet.renderALTER(mRenderer, t->x - mCamera.CameraX , t->y - mCamera.CameraY, &mCurrentClip, t->GetBoundingBox(), NULL, NULL);
		ColorSwitcher(YELLOW);
		//SDL_RenderDrawRect(mRenderer, t->GetBoundingBox());
	}

}

void Game_Renderer::RenderCollPoints(int Xpos, int Ypos, CollisionBox* collBox){

	
	SDL_Rect* pointRect = new SDL_Rect();

	pointRect->h = 5;
	pointRect->w = 5;

	auto points = collBox->GetCollisionPointArrayP();
	
	for (int p = 0; p < points->size(); ++p){
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
		pointRect->x = ((*points)[p][0] - (pointRect->w / 2)) - mCamera.CameraX;
		pointRect->y = ((*points)[p][1] - (pointRect->h / 2)) - mCamera.CameraY;
		SDL_RenderFillRect(mRenderer, pointRect);
		
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawPoint(mRenderer, ((*points)[p][0] - (pointRect->w / 2)) - mCamera.CameraX, ((*points)[p][1] - (pointRect->h / 2)) - mCamera.CameraY);
	}

}

void Game_Renderer::RenderBounding(SDL_Rect* bounding, COLOR color){
	
	SDL_Rect boundRec = *bounding;
	boundRec.x -= mCamera.CameraX;
	boundRec.y -= mCamera.CameraY;

	ColorSwitcher(color);
	SDL_RenderDrawRect(mRenderer, &boundRec);

}

void Game_Renderer::ReadyRendering(Camera cam){
	
	ColorSwitcher(BLACK);
	
	mCamera = cam;

	SDL_RenderClear(mRenderer);
}

void Game_Renderer::ColorSwitcher(COLOR color){
	
	switch (color){
	case RED:
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
		break;
	case GREEN:
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
		break;
	case BLUE:
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
		break;
	case YELLOW:
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0x00, 0xFF);
		break;
	case WHITE:
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		break;
	case BLACK:
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
		break;
	default:
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		break;
	}
}

void Game_Renderer::FlipBuffer(){
	SDL_RenderPresent(mRenderer);
}
