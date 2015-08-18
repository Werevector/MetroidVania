#pragma once
#include "SDL.h"
#include <vector>

enum DIRECTION{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class CollisionBox{
public:

	CollisionBox(SDL_Rect CollBox, int x, int y){

		mBoundingCollBox = CollBox;
		mCollPointsOrigin = {

			    //Top of head
				{ -CollBox.w / 4, -CollBox.h/2 },
				{ CollBox.w / 4, -CollBox.h/2 },

				//Feet
				{ -CollBox.w / 4, CollBox.h/2 },
				{ CollBox.w / 4, CollBox.h/2 },

				//Left arm
				{ -CollBox.w/2, -CollBox.h / 4 },
				{ -CollBox.w/2, CollBox.h / 4 },

				//Right arm
				{ CollBox.w/2, -CollBox.h / 4 },
				{ CollBox.w/2, CollBox.h / 4 }


		};

		mCollPoints = mCollPointsOrigin;
		for (int i = 0; i < mCollPointsOrigin.size(); ++i){
			mCollPoints[i][0] -= x;
			mCollPoints[i][1] -= y;
		}



	}

	std::vector<std::vector<int>>* GetCollisionPointArrayP(){
		return &mCollPoints;
	}

	SDL_Rect* GetBoundingBox(){
		return &mBoundingCollBox;
	}

	void SetBoundingPos(int x, int y){
		mBoundingCollBox.x = x;
		mBoundingCollBox.y = y;
	}
	void SetBoundingCenter(int x, int y){
		mBoundingCollBoxCenter.x = x;
		mBoundingCollBoxCenter.y = y;

		mBoundingCollBox.x = x - (mBoundingCollBox.w/2);
		mBoundingCollBox.y = y - (mBoundingCollBox.h / 2);

		for (int i = 0; i < mCollPoints.size(); ++i){
			mCollPoints[i][0] = mCollPointsOrigin[i][0] + x;
			mCollPoints[i][1] = mCollPointsOrigin[i][1] + y;
		}

	}
	SDL_Point GetBoundingCenter(){
		return mBoundingCollBoxCenter;
	}

private:
	SDL_Rect mBoundingCollBox;
	SDL_Point mBoundingCollBoxCenter;

	//Eigth points around the collison box, for collision checks
	/*SDL_Point mCollPoint_U_L;
	SDL_Point mCollPoint_U_R;
	SDL_Point mCollPoint_M_L;
	SDL_Point mCollPoint_M_R;
	SDL_Point mCollPoint_Lo_L;
	SDL_Point mCollPoint_Lo_R;*/

	//std::vector<SDL_Point> mCollPoints;
	std::vector<std::vector<int>> mCollPointsOrigin;
	std::vector<std::vector<int>> mCollPoints;


};