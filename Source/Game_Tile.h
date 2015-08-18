#pragma once
#include "TypeSet.h"

//-------------|
// A game tile contains info about where it is placed in the room, and what type and size it is.
//-------------|
class Game_Tile{

public:

	Game_Tile(int Nx, int Ny, int Nh, int Nw, TypeSet type){
		
		x = Nx;
		y = Ny;
		h = Nh;
		w = Nw;
		setBoundingBox(x, y, h, w);
		mTileType = type;

	}

	SDL_Rect* GetBoundingBox(){
		return &mBoundingBox;
	}

	//metrics
	int x, y, h, w;

	//Bounding box
	SDL_Rect mBoundingBox;

	//Type
	TypeSet mTileType;

private:

	void setBoundingBox(int x, int y, int h, int w){
		mBoundingBox.x = x;
		mBoundingBox.y = y;
		mBoundingBox.h = h;
		mBoundingBox.w = w;

	}

};