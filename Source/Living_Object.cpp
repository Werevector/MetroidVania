#include "Living_Object.h"

void Living_Object::Move(int posX, int posY){
	
	previousPosX = positionX;
	previousPosY = positionY;

	

	positionX = posX;
	positionY = posY;
	
	mCollisionBox->SetBoundingCenter(posX , posY);
	mSelectorBox->SetBoundingCenter(posX, posY);
}

void Living_Object::MoveToDesired(){
	previousPosX = positionX;
	previousPosY = positionY;

	positionX = desiredPosX;
	positionY = desiredPosY;
	mCollisionBox->SetBoundingCenter(positionX, positionY);
	mSelectorBox->SetBoundingCenter(positionX, positionY);
}

void Living_Object::DesirePosition(int posX, int posY){
	desiredPosX = posX;
	desiredPosY = posY;
	mCollisionBox->SetBoundingCenter(posX, posY);
	mSelectorBox->SetBoundingCenter(posX, posY);
}

void Living_Object::AddVelocity(float vX, float vY){
	velocityX += vX;
	velocityY += vY;
}

void Living_Object::KillVelocityX(){
	velocityX = 0;
}

void Living_Object::KillVelocityY(){
	velocityY = 0;
}

void Living_Object::PartialCollResolve(DIRECTION dir){
	
	switch (dir){
	
	case UP:
		desiredPosY++;
		KillVelocityY();
		break;

	case DOWN:
		desiredPosY--;
		KillVelocityY();
		break;

	case LEFT:
		desiredPosX++;
		KillVelocityX();
		break;

	case RIGHT:
		desiredPosX--;
		KillVelocityX();
		break;
	
	}


	//float moveLengthX = desiredPosX - positionX;
	//float moveLengthY = desiredPosY - positionY;

	//float moveLength = sqrt((moveLengthX * moveLengthX) + (moveLengthY * moveLengthY));
	//

	////Normalise vectors
	//if (moveLength != 0){
	//	moveLengthX /= moveLength;
	//	moveLengthY /= moveLength;
	//}
	//
	///*int moveLengthX = positionX - previousPosX;
	//int moveLengthY = positionY - previousPosY;*/
	//
	//if (moveLengthX != 0 && velocityY == 0){
	//	//positionX = (previousPosX + moveLengthX) - 1;
	//	//positionX -= moveLengthX/4;
	//	//desiredPosX += -floor(moveLengthX+0.5) ;
	//	desiredPosX += -round(moveLengthX);
	//}

	//if (moveLengthY != 0){
	//	//desiredPosY += -floor(moveLengthY+0.5);
	//	desiredPosY += -round(moveLengthY);
	//}

	mCollisionBox->SetBoundingCenter(desiredPosX, desiredPosY);
	mSelectorBox->SetBoundingCenter(desiredPosX, desiredPosY);
}
