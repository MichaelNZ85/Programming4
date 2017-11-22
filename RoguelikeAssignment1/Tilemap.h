///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tilemap.h
// Tilemap Header File
// Tilemap contains a 2D array of integers used to hold a tile map
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//constants
#define NUMBEROFCOLS 80
#define NUMBEROFROWS 45
#define TILESIZE 16
#define ARRAYDIMENSIONS 2

#include "Tile.h"
#include "TileList.h"
#include "Dungeon.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

ref class Tilemap
{
private:
	TileList^ theTiles;//Tilemap needs a TileList to 
	Graphics^ canvas;
	array<int, 2>^ map;//the tile map
	
public:
	Tilemap(TileList^ startTileList, Graphics^ startCanvas);//constructor
	void SetMapEntry(int col, int row, int tileIndex);//sets the specified tile at the specified point
	int GetMapEntry(int col, int row);//returns the number at the given co-ordinate

	void DrawMap();//draws the tile map
	void LoadMapFromFile(String^ mapFileName); //loads a tile map from an external file - not used
	void LoadMapFromDungeon(Dungeon^ theDungeon); //translates the given dungeon into a tile map of ints
	bool IsTileWalkable(int col, int row);//can character pass over tile?
	bool IsItemPlaceable(int col, int row);//can item be placed on tile?
};