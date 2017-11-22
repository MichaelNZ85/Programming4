///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GameManager.h
// Game Manager Header File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Tile.h"
#include "TileList.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "SpriteList.h"

//define constants
#define MINROOMS 8
#define MAXROOMS 12
#define NUMMOSTERS 20
#define NUMPOTIONS 10
#define NUMDAMAGERS 8
#define NUMTREASURE 15
#define PLAYERHP 100
#define MINHITPROB 2
#define MAXHITPROB 6
#define MINDAMAGE 10
#define MAXDAMAGE 40
#define TILESIZE 16
#define SLEEPDURATION 1000
#define SCOREINCREASE 20
#define HPINCREASE 20
#define HPDECREASE 20
#define PLAYERVELOCITY 5
#define EXPINCREASE 100



using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;		// contains the .NET list class
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

ref class GameManager
{
private:
	Graphics^ gameManagerCanvas;
	Random^ rGen;
	TileList^ tiles;
	Tilemap^ theTiles;
	Dungeon^ theDungeon;
	Sprite^ player;

	//temporary sprites to populate lists
	Sprite^ newMonster;
	Sprite^ newPotion;
	Sprite^ newDamager;
	Sprite^ newTreasure;
	Sprite^ staircase; //staircase to next level
	//lists
	SpriteList^ monsterList;
	SpriteList^ potionList;
	SpriteList^ damagerList;
	SpriteList^ treasureList;
	Label^ feedbackLbl;
public:
	property int score;//game score
	property int numberOfRooms; 
	property String^ feedback; //status read into this String
	property int exp; //experience points
	property int playerHP;//property to hold player HP when generating a new level
	property bool gameOver;
	property System::Windows::Forms::Timer^ theTimer;//timer passed in so can be controlled from the Game Manager
public:
	//constructor
	GameManager(Graphics^ startCanvas, Random^ startRGen, Label^ startLabel, System::Windows::Forms::Timer^ startTimer);
	//generator methods for the different types of sprites
	Sprite^ generatePlayerSprite(int startXPos, int startYPos);
	Sprite^ generateMonsterSprite(int startXPos, int startYPos);
	Sprite^ generatePotionSprite(int startXPos, int startYPos);
	Sprite^ generateDamagerSprite(int startXPos, int startYPos);
	Sprite^ generateTreasureSprite(int startXPos, int startYPos);
	Sprite^ generateStaircaseSprite(int startXPos, int startYPos);

	void makeDungeon();
	void makePlayer();//creates player
	void setUpGame();//sets up dungeon
	void movePlayer(); //moves player
	void setPlayerDirection(EDirection direction);
	int getPlayerHP() { return player->hp; }
	void runGame();//makes the game run
	void fight(Sprite^ theMonster);//combat method
	void resetDungeon();//makes new level
};

