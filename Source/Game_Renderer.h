#pragma once
#include "SDL.h"
#include "Texture.h"
#include <map>
#include "Settings.h"
#include "TextureKey.h"
#include "Game_Room.h"
#include <vector>
#include "World_Object.h"
#include "Camera.h"

enum COLOR{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	WHITE,
	BLACK
};

class Game_Renderer{

public:

	bool InitRenderer();
	void ReadyRendering(Camera cam);
	bool LoadSpriteSheet(std::string path);
	void RenderPlayerInstance(int Xpos, int Ypos, TextureKey tex_Key);
	void RenderRoom(Game_Room* room);
	void FlipBuffer();
	void RenderCollPoints(int Xpos, int Ypos, CollisionBox* collBox);
	void RenderBounding(SDL_Rect* bounding, COLOR color);


private:

	Camera mCamera;
	SDL_Renderer* mRenderer = nullptr;
	SDL_Window* mWindow = nullptr;

	Texture mTextureSheet;
	Texture mMapTextureSheet;
	std::map<int, SDL_Rect> mClipCollection;
	std::map<int, SDL_Rect> mMapClipCollection;

	void ColorSwitcher(COLOR color);


};