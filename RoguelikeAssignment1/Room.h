///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Room.h
// Room Header File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
using namespace System::Collections::Generic;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Room
{
private:
	
	
public:
	property int height;
	property int width;
	property int upperLeftCol;
	property int upperLeftRow;
	property int middleCol;//room's middle X position
	property int middleRow;//room's middle Y position
public:
	Room(int h, int w, int c, int r);//constructor
};

