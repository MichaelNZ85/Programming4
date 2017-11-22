///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TileList.h
// TileList Header File
// TileList contains a list of the different types of tiles
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Tile.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class TileList
{
private:
	array<Tile^>^ tileArray;//array of tiles

public:
	TileList();//constructor

	Bitmap^ GetTileBitmap(int tileIndex);//gets the tile's image
	void SetTileArrayEntry(int tileIndex, Tile^ tileToEnter);//sets a particular tile at set point
	bool IsTileWalkable(int tileIndex);//determines whether tile is walkable
};
