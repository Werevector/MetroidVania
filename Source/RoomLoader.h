#pragma once
#include <iostream>
#include <fstream>
#include "Game_Room.h"
#include "NLTmxMap.h"
#include "Settings.h"
#include "LevelSize.h"

static bool LoadRoomFromTmxFile(std::string path, Game_Room* room);
static bool LoadDummyRoom(Game_Room* room);
static std::string loadFile(const char * filename, bool appendNull);


//static void* loadFile(const char * filename, bool appendNull) {
//	
//	FILE* f;
//	fopen_s(&f, filename, "r");
//	//FILE* f = fopen(filename, "r");
//	
//
//	if (!f) {
//		return 0;
//	}
//
//	fseek(f, 0, SEEK_END);
//	auto length = ftell(f) + appendNull;
//	fseek(f, 0, SEEK_SET);
//
//	void* buffer = malloc(length);
//	fread(buffer, length, 1, f);
//	fclose(f);
//
//	if (appendNull) {
//		((char*)buffer)[length - 1] = 0;
//	}
//
//	return buffer;
//}

static std::string loadFile(const char * filename, bool appendNull){

	//const char* resultString_c;

	ifstream fileStream;
	fileStream.open(filename);

	std::string XMLstring((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

	//resultString_c = XMLstring.c_str();

	fileStream.close();

	return XMLstring;
}


static bool LoadRoomFromTmxFile(std::string path, Game_Room* room){

	//convert string to char*
	const char* path_c = path.c_str();

	//the pointer to the xml file
	std::string xmlString = loadFile(path_c, true);

	char*  xml = new char[xmlString.length() + 1];
	strcpy_s(xml, xmlString.length() + 1, xmlString.c_str());
	
	NLTmxMap* map = NLLoadTmxMap(xml);

	std::cout << "height " << map->height << " width " << map->width << "\n";

	LEVEL_WIDTH_M = map->width*map->tileWidth;
	LEVEL_HEIGHT_M = map->height*map->tileHeight;

	for (int i = 0; i < map->width*map->width; i++){
		if (map->layers[0]->data[i] != 0){
			if (map->layers[0]->data[i] != 4){
				room->TileMap.push_back(new Game_Tile((i % map->width) * map->tileWidth, (i / map->height) * map->tileHeight, map->tileWidth, map->tileHeight, TypeSet(map->layers[0]->data[i] - 1)));
			}

		}
		
	}

	return true;

}

//bool LoadRoomFromFile(std::string path){

	////Success flag
	//bool tilesLoaded = true;
	//Tile *tile = 0;

	//int TOTAL

	////The tile offsets
	//int x = 0, y = 0;

	////Open the map
	//std::ifstream mapStream(path);

	////If the map couldn't be loaded
	//if (!mapStream.is_open())
	//{
	//	printf("Unable to load map file!\n");
	//	tilesLoaded = false;
	//}
	//else
	//{
	//	//Initialize the tiles
	//	for (int i = 0; i < TOTAL_TILES; ++i)
	//	{
	//		//Determines what kind of tile will be made
	//		int tileType = -1;

	//		//Read tile from map file
	//		mapStream >> tileType;

	//		//If the was a problem in reading the map
	//		if (mapStream.fail())
	//		{
	//			//Stop loading map
	//			printf("Error loading map: Unexpected end of file!\n");
	//			tilesLoaded = false;
	//			break;
	//		}

	//		//If the number is a valid tile number
	//		if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
	//		{
	//			tile = new Tile(x, y, TILE_WIDTH, TILE_HEIGHT, tileType);
	//			mTileSet.push_back(*tile);
	//		}
	//		//If we don't recognize the tile type
	//		else
	//		{
	//			//Stop loading map
	//			printf("Error loading map: Invalid tile type at %d!\n", i);
	//			tilesLoaded = false;
	//			break;
	//		}

	//	}

	//}

	////Close the file
	//mapStream.close();

	////If the map was loaded fine
	//return tilesLoaded;
//	return true;
//}

bool LoadDummyRoom(Game_Room* room){

	int tileWidth = 25;
	int tileHeight = 25;

	//Floor1
	for (int i = 0; i < 70; ++i){
		room->TileMap.push_back(new Game_Tile(0 + (tileWidth * i), 575, tileWidth, tileHeight, FLOOR));
	}

	for (int i = 0; i < 4; ++i){
		room->TileMap.push_back(new Game_Tile(30 + tileWidth * i, 300, tileWidth, tileHeight, PLATFORM));
	}

	for (int i = 0; i < 3; ++i){
		room->TileMap.push_back(new Game_Tile(300 + tileWidth * i, 350, tileWidth, tileHeight, PLATFORM));
	}

	for (int i = 0; i < 3; ++i){
		room->TileMap.push_back(new Game_Tile(500 + tileWidth * i, 250, tileWidth, tileHeight, PLATFORM));
	}

	for (int i = 0; i < 30; ++i){
		room->TileMap.push_back(new Game_Tile(0, 0 + tileWidth * i, tileWidth, tileHeight, WALL));
	}

	/*for (int i = 0; i < 30; ++i){
	room->TileMap.push_back(new Game_Tile(800 - tileWidth, 0 + tileWidth * i, tileWidth, tileHeight, WALL));
	}*/




	return true;
}