///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TileList.cpp
// TileList CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TileList.h"

//constant
#define NUMBEROFTILES 5

//constructor
TileList::TileList()
{
	//create the tile array
	tileArray = gcnew array<Tile^>(NUMBEROFTILES);

	//create bitmaps
	Bitmap^ dirt = gcnew Bitmap("images/dirt.jpg");
	Bitmap^ door = gcnew Bitmap("images/door.jpg");
	Bitmap^ floor = gcnew Bitmap("images/floor.jpg");
	Bitmap^ wall = gcnew Bitmap("images/wall.jpg");
	Bitmap^ corridor = gcnew Bitmap("images/corridor.jpg");

	//create tiles using bitmaps
	Tile^ tile0 = gcnew Tile(dirt, false);
	Tile^ tile1 = gcnew Tile(door, true);
	Tile^ tile2 = gcnew Tile(floor, true);
	Tile^ tile3 = gcnew Tile(wall, false);
	Tile^ tile4 = gcnew Tile(corridor, true);
	
	//fill up tile array
	tileArray[0] = tile0;//dirt
	tileArray[1] = tile1;//door
	tileArray[2] = tile2;//floor
	tileArray[3] = tile3;//wall
	tileArray[4] = tile4;//corridor
	

}
//returns a bitmap object at the specified index
Bitmap^ TileList::GetTileBitmap(int tileIndex)
{
	return tileArray[tileIndex]->tileBitmap;
}
//sets tile array entry to specified tile at specified location
void TileList::SetTileArrayEntry(int tileIndex, Tile^ tileToEnter)
{
	tileArray[tileIndex] = tileToEnter;
}

//determines if tile is walkable
bool TileList::IsTileWalkable(int tileIndex)
{
	bool isWalkable = false;
	if (tileArray[tileIndex]->isWalkable == true)//if the tile at the index location is walkable
		isWalkable = true;//set walkable to true

	return isWalkable;
}