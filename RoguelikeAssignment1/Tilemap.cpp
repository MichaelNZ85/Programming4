///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tilemap.cpp
// Tilemap CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Tilemap.h"

//constructor 
Tilemap::Tilemap(TileList^ startTileList, Graphics^ startCanvas)
{
	theTiles = startTileList;
	canvas = startCanvas;
	map = gcnew array<int, ARRAYDIMENSIONS>(NUMBEROFCOLS, NUMBEROFROWS);//creates map
}
//sets map value to specified value at specified point
void Tilemap::SetMapEntry(int col, int row, int tileIndex)
{
	map[col, row] = tileIndex;
}
//returns map value at specified point
int Tilemap::GetMapEntry(int col, int row)
{
	return map[col, row];
}
//draws the tile map
void Tilemap::DrawMap()
{
	int i = 0;
	for (int row = 0; row < NUMBEROFROWS; row++)
	{
		for (int col = 0; col < NUMBEROFCOLS; col++)
		{
			int vm = map[col, row];
			Bitmap^ picture = theTiles->GetTileBitmap(vm);
			int a = col * TILESIZE;
			int b = row * TILESIZE;
			canvas->DrawImage(picture, Rectangle(col * TILESIZE, row * TILESIZE, TILESIZE, TILESIZE));
		}
	}

}
//loads a map from an external file
void Tilemap::LoadMapFromFile(String^ mapFileName)
{

	array<String^>^ indexHolder = gcnew array<String^>(NUMBEROFCOLS);//need constant
	StreamReader^ sr = File::OpenText(mapFileName);//stream reader opens text file

	String^ line = "";
	int rowCounter = 0;
	while ((line = sr->ReadLine()) != nullptr)//while there is text on the line
	{
		indexHolder = line->Split(',');//split at comma
		for (int columnCounter = 0; columnCounter < NUMBEROFCOLS; columnCounter++)
		{
			//fetch value from indexHolder
			int indexValue = Convert::ToInt16(indexHolder[columnCounter]);
			//place value in map[,]
			map[columnCounter, rowCounter] = indexValue;
		}//end for

		rowCounter++;

	}//end while

}

//determines if the tile is walkable for player
bool Tilemap::IsTileWalkable(int col, int row)
{
	bool isWalkable = false;
	int theTile = GetMapEntry(col, row);
	if ((theTile == 1) || (theTile == 2) || (theTile == 4))//if the tile is either floor or door or corridor
	{
		isWalkable = true;//tile is walkable
	}

	return isWalkable;

}
//determines whether tile is floor so that items can be placed
bool Tilemap::IsItemPlaceable(int col, int row)
{
	bool isPlaceable = false;
	int theTile = GetMapEntry(col, row);
	if (theTile == 2)//is the tile floor?
	{
		isPlaceable = true;//item can be placed
	}
	
	return isPlaceable;
}

//fills Tilemap with values from procedurally generated dungeon
void Tilemap::LoadMapFromDungeon(Dungeon^ theDungeon)
{
	for (int col = 0; col < NUMCOLS; col++)
	{
		for (int row = 0; row < NUMROWS; row++)
		{
			ETileType theTile = theDungeon->getMapValue(col, row);//gets value of dungeon's 2D array

			//fill up Tilemap with values from dungeon's 2D array
			switch (theTile)
			{
			case ETileType::DIRT:
				map[col, row] = 0;
				break;
			case ETileType::DOOR:
				map[col, row] = 1;
				break;
			case ETileType::FLOOR:
				map[col, row] = 2;
				break;
			case ETileType::WALL:
				map[col, row] = 3;
				break;
			case ETileType::CORRIDOR:
				map[col, row] = 4;
				break;
			}
		}
	}
}