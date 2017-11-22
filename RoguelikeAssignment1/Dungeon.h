///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dungeon.h
// Dungeon Header File
// Dungeon holds information about the dungeon - including a list of rooms
// Created by: Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Room.h"

//define constants
#define NUMCOLS 64
#define NUMROWS 45
#define MINROOMSIZE 5
#define MAXROOMSIZE 12
#define ARRAYDIMENSIONS 2

//create enum for tile types
public enum ETileType {DIRT, DOOR, FLOOR, WALL, CORRIDOR};

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Dungeon
{
private:
	int numberOfRooms;
	List<Room^>^ deleteRoomList;//list for rooms to be deleted
	Random^ rGen;
	

public:
	array<ETileType, ARRAYDIMENSIONS>^ map; //dungeon map - array of ETileTypes
	property List<Room^>^ roomList;	//list of the rooms
public:
	Dungeon();

	Room^ createNewLegalRoom();//creates a new legal room at a random point
	void makeNewDungeon(int startNumberOfRooms);//creates a new dungeon
	void setTerrain(Room^ theRoom);//sets the terrain in the room
	void createCorridor();//creates corridors
	void clearDungeon(int startNumberOfRooms);//clears dungeon

	//get map value
	ETileType getMapValue(int col, int row)		{ return map[col, row]; }
};

