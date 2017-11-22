///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tile.cpp
// Tile CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Tile.h"

//constructor - sets isWalkable to false by default
Tile::Tile(Bitmap^ startTileBitmap)
{
	tileBitmap = startTileBitmap;
	isWalkable = false;
}

//constructor with isWalkable passed in
Tile::Tile(Bitmap^ startTileBitmap, bool startIsWalkable)
{
	tileBitmap = startTileBitmap;
	isWalkable = startIsWalkable;
}
