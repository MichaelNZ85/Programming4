///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Room.cpp
// Room CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Room.h"

//constructor 
Room::Room(int h, int w, int c, int r)
{
	height = h;
	width = w;
	upperLeftCol = c;
	upperLeftRow = r;
	middleCol = upperLeftCol + (width / 2);//calculate middle column
	middleRow = upperLeftRow + (height / 2);//calculate middle row
}


