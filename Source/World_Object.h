#pragma once
#include "Generic_Object.h"
#include "TextureKey.h"
#include <vector>
#include "CollisionBox.h"

class World_Object : public Generic_Object{

public:

	World_Object(int x, int y) : Generic_Object(x, y){
		positionX = x;
		positionY = y;
	}

	bool HitCheck();

	void Update() = 0;

	TextureKey GetTextureKey(){
		return obj_Texture_Key; 
	}

	CollisionBox* GetCollisionBoxP(){
		return mCollisionBox;
	}

	CollisionBox* GetSelectorBoxP(){
		return mSelectorBox;
	}

	void SetCollisionBox(SDL_Rect collbox){
		mCollisionBox = new CollisionBox(collbox, positionX, positionY);
	}

	void SetSelectorBox(SDL_Rect selectorBox){
		mSelectorBox = new CollisionBox(selectorBox, positionX, positionY);
	}

protected:

	CollisionBox* mCollisionBox = nullptr;
	CollisionBox* mSelectorBox = nullptr;
	TextureKey obj_Texture_Key;


};