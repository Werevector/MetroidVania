#pragma once
#include <vector>
#include "Game_Tile.h"

//-----------|
//Game_Room is a class containing all the info of tiles in a certain room in the game
//Rooms will be chained together and connected with certain special tiles that "teleport" the player from room to room
//-----------|

class Game_Room{

public:

	std::vector<Game_Tile*> TileMap;



private:

	

};