#include "Player_Object.h"

void Player_Object::Update(){

	walkAnimationWeight += DELTA_TIME;
	if ((walkAnimationWeight) > 0.08f){
		walkAnimationWeight = 0;
	}

	if (!jumpKeyDown && velocityY < 0){
		velocityY += accelGrav;
	}
	else{
		velocityY += accelGrav / 3;
	}


	if (velocityX >= max_velocityX){ velocityX = max_velocityX; }
	if (velocityX <= -max_velocityX){ velocityX = -max_velocityX; }
	if (velocityY >= max_velocityY){ velocityY = max_velocityY; }

	if (!isWalking){
		
		if (jumping){ de_accelX /= 2; }

		if (velocityX < 0){
			velocityX += de_accelX;
		}
		
		if(velocityX > 0){
			velocityX -= de_accelX;
		}

		de_accelX = 1.f;

		if (velocityX > 0 && velocityX < de_accelX) velocityX = 0;
		if (velocityX < 0 && velocityX > -de_accelX) velocityX = 0;


	}

	NextAnimationFrame();

	//Move(positionX + velocityX, positionY + velocityY);
	DesirePosition(positionX + velocityX, positionY + velocityY);
	isWalking = false;

}

void Player_Object::Walk(char direction){

	switch (direction){
	case RIGHT_FLIP:
		velocityX += accelX;
		isWalking = true;
		obj_Texture_Key.flipping = SDL_FLIP_NONE;
		break;

	case LEFT_FLIP:
		velocityX -= accelX;
		isWalking = true;
		obj_Texture_Key.flipping = SDL_FLIP_HORIZONTAL;
		break;
	}

}

void Player_Object::Jump(){
	
	//jumpHoldDeprecation++;
	
	if (!jumping && !jumpKeyDown){
		
		//jumpHoldDeprecation = 1;
		jumping = true;
		jumpKeyDown = true;
		velocityY -= jumpSpeedY;
	}

}


void Player_Object::Ground(){
	jumping = false;
}

void Player_Object::NextAnimationFrame(){

	if (isWalking && !jumping){
		if (walkAnimationWeight == 0){
			obj_Texture_Key.clip_key++;
		}
		if (obj_Texture_Key.clip_key > 10){ obj_Texture_Key.clip_key = 4; }
	}

	if (jumping){
		if (walkAnimationWeight == 0){
			if (velocityY < 0){
				if (jumpLength < 4){
					jumpLength++;
					obj_Texture_Key.clip_key = 42 + jumpLength;
				}
			}
			else if(jumpLength > 0){
				jumpLength--;
				obj_Texture_Key.clip_key = 46 + jumpLength/2;
			}
		}
	}
	
	if(!isWalking && !jumping){
		
		

		//if (obj_Texture_Key.clip_key >= 3) obj_Texture_Key.clip_key = -1;

		//obj_Texture_Key.clip_key++;
		obj_Texture_Key.clip_key = 3;
		
		jumpLength = 0;
	}
}