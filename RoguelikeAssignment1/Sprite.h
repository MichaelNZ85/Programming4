///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprite.h
// Sprite Header File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Tilemap.h"

//constants
#define TILESIDE 16
#define SPRITESHEETS 4
#define DIRECTIONS 4
#define FORMWIDTH 1280
#define FORMHEIGHT 720

public enum EDirection { EAST, SOUTH, WEST, NORTH }; //direction enum
public enum ESpriteType {PLAYER, MONSTER, POTION, DAMAGER, TREASURE, STAIRCASE}; //sprite type enum - not used

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class Sprite
{
private:
	Graphics^ canvas;
	array<Bitmap^>^ spriteSheets;

	Random^ rGen;
	int nFrames;
	int currentFrame;
	int xPos;
	int yPos;
	int frameWidth;
	int frameHeight;
	int xVel;
	int yVel;
	array<Point>^ velocityDirections;
	Rectangle boundingRectangle;
	TileList^ tiles;
	Tilemap^ theTiles;//tilemap needed for terrain collisions

public:
	Sprite^ Next;//needed for list
	EDirection spriteDirection;
	ESpriteType spriteType;
	property bool isAlive;
	//corners for collision detection
	property Point topLeft;
	property Point topRight;
	property Point bottomLeft;
	property Point bottomRight;
	//game stats
	property int hp;
	property int hitProb;
	

public:
	//constructors
	Sprite(Graphics^ startCanvas, array<String^>^ startFileNames, Random^ startRGen, int startNFrames, Tilemap^ startTilemap, ESpriteType startSpriteType);
	Sprite(Graphics^ startCanvas, array<String^>^ startFileNames, Random^ startRGen, int startNFrames, Tilemap^ startTilemap, ESpriteType startSpriteType, int startXPos, int startYPos, int startHP, int startHitProb);
	Sprite(Graphics^ startCanvas, array<String^>^ startFileNames, Random^ startRGen, int startNFrames, Tilemap^ startTilemap, ESpriteType startSpriteType, int startXPos, int startYPos, int startBRX, int startBRY, int startBRWidth, int startBRHeight);
	void Draw();
	void Erase();
	void Move();
	bool CheckOutOfBounds();
	void UpdateFrame();
	void SetSpriteSheets(array<String^>^ newFileName, int newNFrames);
	void Wander();
	void changeDir();
	bool CollidedWithMe(Sprite^ otherGuy);//check collision
	void ChangeImages(array<String^>^ names);
	void ComputeFrameHeightAndWidth();

	//gets and sets
	void setXVel(int newX) { xVel = newX; }
	void setYVel(int newY) { yVel = newY; }

	int getXVel() { return xVel; }
	int getYVel() { return yVel; }

	void setXPos(int newX) { xPos = newX; }
	void setYPos(int newY) { yPos = newY; }

	int getXPos() { return xPos; }
	int getYPos() { return yPos; }

	void setHP(int startHP)	{ hp = startHP; }
};