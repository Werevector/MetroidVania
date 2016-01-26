#pragma once
#include "SDL.h"
#include <iostream>
#include "GlobalTimer.h"
class Generic_Object{

public:

	Generic_Object(int x, int y){
		positionX = x;
		positionY = y;
	}

	SDL_Point ReturnPositon(){
		SDL_Point point;
		point.x = positionX;
		point.y = positionY;
		return point;
	}

	virtual void Update() = 0;

protected:

	int positionX;
	int positionY;


};