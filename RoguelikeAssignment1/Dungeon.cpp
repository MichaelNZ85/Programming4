///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dungeon.cpp
// Dungeon CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Dungeon.h"
#include "Room.h"

//constructor
Dungeon::Dungeon()
{
	map = gcnew array<ETileType, 2>(NUMCOLS, NUMROWS);
	rGen = gcnew Random();
	roomList = gcnew List<Room^>();
}

//determines whether a room can be created
Room^ Dungeon::createNewLegalRoom()
{
	Room^ legalRoom = nullptr; //create a room pointer
	bool foundARoom = false;
	int x, y, width, height;
	while (!foundARoom)
	{
		
		bool isLegal = true;
		bool isOutOfBoundary = false;
		
		
		width = rGen->Next(MINROOMSIZE, MAXROOMSIZE);//generate random width
		height = rGen->Next(MINROOMSIZE, MAXROOMSIZE);//and height
		x = rGen->Next(NUMCOLS - MAXROOMSIZE);//generate random location
		y = rGen->Next(NUMROWS - MAXROOMSIZE);
		//loop through map checking if room area is dirt
		for (int col = x; col < (x + width); col++)
		{
			for (int row = y; row < (y + height); row++)
			{
				if ((col < NUMCOLS) && (row < NUMROWS))
				{
					if (map[col, row] != ETileType::DIRT)//if map entry is not dirt
					{
						isLegal = false;//it is not a legal room
						break;
					}
				}
				else{
					isOutOfBoundary = true;//room is out of bounds
					break;
				}
			}
		}
		if ((isLegal == true) && (isOutOfBoundary == false))//if the room is both legal and in bounds
		{
			foundARoom = true;//we've found a room!
		}
	}//end while !foundAroom

	if (foundARoom){
		legalRoom = gcnew Room(height, width, x, y);
		
	}
	return legalRoom;//return the legal room
	

}

//creates a new dungeon
void Dungeon::makeNewDungeon(int startNumberOfRooms)
{
	for (int i = 0; i < startNumberOfRooms; i++)
	{
		Room^ theRoom = createNewLegalRoom();//make a room
		setTerrain(theRoom); //set the terrain
		roomList->Add(theRoom); //add to room list
	}

		createCorridor(); //create the corridors between rooms
	
}

//set the dungeon terrain types
void Dungeon::setTerrain(Room^ theRoom)
{
	//set top row to walls
	for (int i = theRoom->upperLeftCol; i < theRoom->upperLeftCol + theRoom->width; i++)
	{
		if (i < 80){
			map[i, theRoom->upperLeftRow] = ETileType::WALL;
		}
		else{
			break;
		}
	}

	//set bottom rows to walls
	for (int j = theRoom->upperLeftCol; j < theRoom->upperLeftCol + theRoom->width; j++)
	{
		int temp = theRoom->upperLeftRow + theRoom->height;
		if ((j < 80)&&(temp < 45)){
			map[j, temp] = ETileType::WALL;
		}
		else{
			break;
		}
	}

	//set first column to walls
	for (int k = theRoom->upperLeftRow; k < theRoom->upperLeftRow + theRoom->height; k++)
	{
		if (k < NUMROWS){
			map[theRoom->upperLeftCol, k] = ETileType::WALL;
		}
		
	}

	//set last column to walls
	for (int l = theRoom->upperLeftRow; l < theRoom->upperLeftRow + theRoom->height; l++)
	{
		int eastWall =  theRoom->upperLeftCol + theRoom->width;
		if ((eastWall < 80) && (l < 45)){
			map[eastWall, l] = ETileType::WALL;
		}
		else {
			break;
		}
	}

	//if not a wall, set to floor
	for (int col = theRoom->upperLeftCol; col < theRoom->upperLeftCol + theRoom->width; col++)
	{
		for (int row = theRoom->upperLeftRow; row < theRoom->upperLeftRow + theRoom->height; row++)
		{
			if ((col < NUMCOLS) && (row < NUMROWS)){
				if (map[col, row] != ETileType::WALL)
					map[col, row] = ETileType::FLOOR;
			}
		}
	}
}

//create the corridors between rooms
void Dungeon::createCorridor()
{
	for (int i = 0; i < roomList->Count - 1; i++)
	{
		//create some room pointers
		Room^ r1 = roomList[i];//g
		Room^ r2 = roomList[i + 1];
		Room^ east;
		Room^ west;

		//determine which room is west and which is east and set pointers
		if (r2->upperLeftCol < r1->upperLeftCol)
		{
			east = r1;
			west = r2;
		}
		else
		{
			east = r2;
			west = r1;
		}

		int colDifference = east->middleCol - west->middleCol;
		//int rowDifference = east->middleRow - west->middleRow;
		int rowDifference = Math::Abs(east->middleRow - west->middleRow);

		int col = west->middleCol;
		int row = west->middleRow;
		
			//set horizontal arm of corridor
			for (int i = 0; i < colDifference; i++)
			{
				if ((col + i < NUMCOLS) && (row < NUMROWS))
				{
					if (map[col + i, row] == ETileType::WALL)//if the tile is a wall
					{
						map[col + i, row] = ETileType::DOOR;//set to a door
					}
					else
					{
						map[col + i, row] = ETileType::CORRIDOR;//else set to corridor
					}

				}
			}
			//set vertical arm of corridor
			for (int j = 0; j < rowDifference; j++)
			{
				if ((col < NUMCOLS) && (row < NUMROWS))
				{
					//determine whether arm has to go up or down
					if (west->middleRow < east->middleRow)//up
					{
						//if wall, set to door
						if (map[east->middleCol, row + j] == ETileType::WALL)
						{
							map[east->middleCol, row + j] = ETileType::DOOR;
						}
						else{
							map[east->middleCol, row + j] = ETileType::CORRIDOR;//else set to corridor
						}
					}
					else //down
					{
						//if wall, set to door
						if (map[east->middleCol, row - j] == ETileType::WALL)
						{
							map[east->middleCol, row - j] = ETileType::DOOR;
						}
						else 
						{
							map[east->middleCol, row - j] = ETileType::CORRIDOR;//else set to corridor
						}
					}
				}
			}
		}
	
	}

//erase the dungeon
void Dungeon::clearDungeon(int startNumberOfRooms)
{
	//create a list to hold the rooms to be deleted
	deleteRoomList = gcnew List<Room^>();
	
	//populate the delete list
	for (int i = 0; i < startNumberOfRooms; i++)
	{
		Room^ tempRoom = roomList[i];
		deleteRoomList->Add(tempRoom);
	}

	//loop through the room list and delete the rooms
	for each(Room^ currentRoom in deleteRoomList)
	{
		roomList->Remove(currentRoom);
	}

	//clear the delete list
	deleteRoomList->Clear();

	//sets all tiles to dirt
	for (int col = 0; col < NUMCOLS; col++)
	{
		for (int row = 0; row < NUMROWS; row++)
		{
			map[col, row] = ETileType::DIRT;
		}
	}

}

