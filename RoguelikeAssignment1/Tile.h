///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tile.h
// Tile Header File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Tile
{
public:
	property Bitmap^ tileBitmap;//picture of tile
	property bool isWalkable;
public:
	//constructors
	Tile(Bitmap^ startTileBitmap);
	Tile(Bitmap^ startTileBitmap, bool startIsWalkable);

};
