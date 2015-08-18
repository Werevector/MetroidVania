#pragma once
#include "World_Object.h"

class Living_Object : public World_Object{

public:

	Living_Object(int x, int y, int healthAmount) : World_Object(x, y){
		
		positionX = x;
		positionY = y;
		previousPosX = x;
		previousPosY = y;
		desiredPosX = x;
		desiredPosY = y;
		health = healthAmount;
		velocityX = 0;
		velocityY = 0;

	}

	void Move(int posX, int posY);
	void DesirePosition(int posX, int posY);
	void MoveToDesired();
	void TakeDamage(int damage);
	void Spawn();
	void DeSpawn();
	void AddVelocity(float vX, float vY);
	void KillVelocityX();
	void KillVelocityY();
	void PartialCollResolve(DIRECTION dir);

	float velocityX;
	float velocityY;

	int previousPosX;
	int previousPosY;

	int desiredPosX;
	int desiredPosY;

	int health;



protected:

	


};