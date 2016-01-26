#pragma once
#include "Living_Object.h"
#include "SDL.h"

#define RIGHT_FLIP 1
#define LEFT_FLIP 0


class Player_Object : public Living_Object{

public:

	bool jumpKeyDown;
	
	Player_Object(int x, int y, int healthAmount) : Living_Object(x, y, healthAmount){
		
		jumping = false;
		jumpKeyDown = false;
		isWalking = false;

		jumpLength = 0;
		
		accelX = 0.5f;
		de_accelX = 1.f;

		max_velocityX = 5.0f;
		max_velocityY = 40.0f;

		jumpSpeedY = 10.f;
		accelGrav = 1.f;

		jumpHoldDeprecation = 0;

		flipType = SDL_FLIP_NONE;

		walkAnimationWeight = 0;

	}

	void Update() override;
	void Walk(char);
	void Jump();
	void Ground();

protected:

	//PlayerUpgradeList upgradeList;
	bool jumping;
	bool isWalking;

	//How much to accelerate when walking, and not
	float accelX;
	float de_accelX;
	
	//acceleration of gravity
	float accelGrav;

	//velocity max values
	float max_velocityX;
	float max_velocityY;
	
	//The speed of a jump
	float jumpSpeedY;

	//Hold the jump button to control the jump more finely
	float jumpHoldDeprecation;

	SDL_RendererFlip flipType;

	float walkAnimationWeight;
	float jumpLength;


	void NextAnimationFrame();


};