///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GameManager.cpp
// GameManager CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GameManager.h"

//constructor
GameManager::GameManager(Graphics^ startCanvas, Random^ startRGen, Label^ startLabel, System::Windows::Forms::Timer^ startTimer)
{
	gameManagerCanvas = startCanvas;
	rGen = startRGen;
	tiles = gcnew TileList;
	theTiles = gcnew Tilemap(tiles, gameManagerCanvas);
	theDungeon = gcnew Dungeon();
	numberOfRooms = rGen->Next(MINROOMS, MAXROOMS);
	feedback = "";
	feedbackLbl = startLabel;
	gameOver = false;
	theTimer = startTimer;
	score = 0;
	exp = 0;
	playerHP = 100;
	
}
//creates a new dungeon and draws it to the screen
void GameManager::makeDungeon()
{
	theDungeon->makeNewDungeon(numberOfRooms);
	theTiles->LoadMapFromDungeon(theDungeon);
	theTiles->DrawMap();
}

//create player character in the middle of the first room
void GameManager::makePlayer()
{
	player = generatePlayerSprite(theDungeon->roomList[0]->middleCol * TILESIZE, theDungeon->roomList[0]->middleRow * TILESIZE);
}


//create monsters and items and add to appropriate lists
void GameManager::setUpGame()
{
	//create monsters and populate monster list
	monsterList = gcnew SpriteList();
	for (int i = 0; i < NUMMOSTERS; i++)
	{
		bool foundAPlace = false;
		while (foundAPlace == false)//while we haven't found a place
		{
			//create a random x and y location
			int initX = rGen->Next(1, FORMWIDTH);
			int initY = rGen->Next(1, FORMHEIGHT);

			int directionCornerX = initX;
			int directionCornerY = initY;

			//translate x and y into tilemap co-ordinates
			int col = directionCornerX / TILESIDE;
			int row = directionCornerY / TILESIDE;

			//check tilemap to see whether tile is floor
			if (theTiles->IsItemPlaceable(col, row) == true)//is the tile floor?
			{
				newMonster = generateMonsterSprite(initX, initY);//add monster at location
				monsterList->addSprite(newMonster);//add monster to list
				foundAPlace = true;//break out of while loop
			}
		}
		
	}

	//create potions and populate list
	potionList = gcnew SpriteList();
	for (int i = 0; i < NUMPOTIONS; i++)
	{
		bool foundAPlace = false;
		while (foundAPlace == false)
		{
			//create random x and y location
			int initX = rGen->Next(1, FORMWIDTH);
			int initY = rGen->Next(1, FORMHEIGHT);

			int directionCornerX = initX;
			int directionCornerY = initY;

			//translate x and y location to tilemap co-ordinates
			int col = directionCornerX / TILESIDE;
			int row = directionCornerY / TILESIDE;

			//check tilemap to see if tile is floor
			if (theTiles->IsItemPlaceable(col, row) == true)
			{
				newPotion = generatePotionSprite(initX, initY);//add potion
				potionList->addSprite(newPotion);//add potion to list
				foundAPlace = true;//break out of while loop
			}
		}
	}//end for

	//create damagers (poisonous berries) and populate list
	damagerList = gcnew SpriteList();
	for (int i = 0; i < NUMDAMAGERS; i++)
	{
		bool foundAPlace = false;
		while (foundAPlace == false)
		{
		
			//generate temp x and y position
			int initX = rGen->Next(1, FORMWIDTH);
			int initY = rGen->Next(1, FORMHEIGHT);

			int directionCornerX = initX;
			int directionCornerY = initY;

			//determine row and column co-ordinate for tilemap
			int col = directionCornerX / TILESIDE;
			int row = directionCornerY / TILESIDE;

			//check whether square is floor
			if (theTiles->IsItemPlaceable(col, row) == true)
			{
				newDamager = generateDamagerSprite(initX, initY);//create damager at x and y location
				damagerList->addSprite(newDamager);//add damager to list
				foundAPlace = true; //break out of while loop
			}
		}
	}
	
	//create treasure and populate list
	treasureList = gcnew SpriteList();
	for (int i = 0; i < NUMTREASURE; i++)
	{
		bool foundAPlace = false;
		while (foundAPlace == false)
		{
			//create initial x and y location
			int initX = rGen->Next(1, FORMWIDTH);
			int initY = rGen->Next(1, FORMHEIGHT);

			int directionCornerX = initX;
			int directionCornerY = initY;

			//translate into tilemap co-ordinates
			int col = directionCornerX / TILESIDE;
			int row = directionCornerY / TILESIDE;

			//check tilemap to see if location is floor
			if (theTiles->IsItemPlaceable(col, row) == true)
			{
				newTreasure = generateTreasureSprite(initX, initY);//add treasure at specified location
				treasureList->addSprite(newTreasure);//add treasure to list
				foundAPlace = true;//break out of while loop
			}
		}
	}

	//make the staircase in the last room
	staircase = generateStaircaseSprite(theDungeon->roomList[numberOfRooms - 1]->middleCol * TILESIZE, theDungeon->roomList[numberOfRooms - 1]->middleRow * TILESIZE);

}

void GameManager::runGame()
{
	
		theTiles->DrawMap();//draw tilemap
		movePlayer();
		//draw monsters and items
		monsterList->drawSprites();
		potionList->drawSprites();
		damagerList->drawSprites();
		treasureList->drawSprites();
		//draw staircase
		staircase->Draw();

		/////////////////////////////////////////////////////////////////////////
		// Set collisions for monsters and items with player character
		/////////////////////////////////////////////////////////////////////////


		//set potion collisions
		Sprite^ potionCollide = potionList->checkCollision(player);//check whether player has collided with each potion
		if (potionCollide != nullptr)
		{
			player->hp += HPINCREASE; //increase player's HP
			feedback = "You found a potion.\nYour HP increased by 20";
			potionCollide->Erase();//erase potion 
			potionList->deleteOneSprite(potionCollide);//delete potion from list

		}

		//set damager collisions
		Sprite^ damagerCollide = damagerList->checkCollision(player);//check whether player has collided with each damager
		if (damagerCollide != nullptr)
		{
			player->hp -= HPDECREASE; //decrease player's HP
			feedback = "Oh no! You touched a poisonous berry!\nYou lost 20 HP!";
			damagerCollide->Erase();
			damagerList->deleteOneSprite(damagerCollide);//delete damager from list
			//if damagers bring player's HP to zero or below, the game is over
			if (player->hp <= 0)
			{
				gameOver = true;
				MessageBox::Show("You died! Game over!");
			}
		}

		//set treasure collisions
		Sprite^ treasureCollide = treasureList->checkCollision(player);//check whether player has collided with each treasure
		if (treasureCollide != nullptr)
		{
			score += SCOREINCREASE;//increase score
			feedback = "You found some treasure!";
			treasureCollide->Erase();//erase treasure
			treasureList->deleteOneSprite(treasureCollide);//delete treasure from list
		}

		//set monster collisions to call fight method
		Sprite^ monsterCollide = monsterList->checkCollision(player);
		if (monsterCollide != nullptr)
		{
			fight(monsterCollide);//FIGHT!!!
		}

		//set staircase collision
		bool collided = staircase->CollidedWithMe(player);
		if (collided == true)
		{
			resetDungeon();//make the next level
		}

	}


//creates the player character
Sprite^ GameManager::generatePlayerSprite(int startXPos, int startYPos)
{
	//player stats
	int framesInPlayerSpriteSheet = 6;
	int directions = 4;
	int initHitProb = 2;
	//creates Strings with filenames
	String^ east = gcnew String("images/heroeast.bmp");
	String^ north = gcnew String("images/heronorth.bmp");
	String^ south = gcnew String("images/herosouth.bmp");
	String^ west = gcnew String("images/herowest.bmp");
	array<String^>^ playerImages = gcnew array<String^>(directions);//add strings to array
	//set images to files
	playerImages[EDirection::EAST] = east;
	playerImages[EDirection::NORTH] = north;
	playerImages[EDirection::SOUTH] = south;
	playerImages[EDirection::WEST] = west;

	//return a new sprite
	return gcnew Sprite(gameManagerCanvas, playerImages, rGen, framesInPlayerSpriteSheet, theTiles, ESpriteType::PLAYER, startXPos, startYPos, playerHP, initHitProb);
}

//generate monster sprite
Sprite^ GameManager::generateMonsterSprite(int startXPos, int startYPos)
{
	//monster stats
	int framesInMonsterSpriteSheet = 2;
	int directions = 4;
	int monster1HP = 80;
	int monster2HP = 60;
	int monster1HitProb = 3;
	int monster2HitProb = 5;
	//array with monster 1 (beetle) images loaded in
	String^ east1 = gcnew String("images/monster1.bmp");
	String^ north1 = gcnew String("images/monster1.bmp");
	String^ south1 = gcnew String("images/monster1.bmp");
	String^ west1 = gcnew String("images/monster1.bmp");
	array<String^>^ monster1Images = gcnew array<String^>(directions);
	monster1Images[EDirection::EAST] = east1;
	monster1Images[EDirection::NORTH] = north1;
	monster1Images[EDirection::SOUTH] = south1;
	monster1Images[EDirection::WEST] = west1;

	//array with monster 2 (ghost) images loaded in
	String^ east2 = gcnew String("images/monster2.bmp");
	String^ north2 = gcnew String("images/monster2.bmp");
	String^ south2 = gcnew String("images/monster2.bmp");
	String^ west2 = gcnew String("images/monster2.bmp");
	array<String^>^ monster2Images = gcnew array<String^>(directions);
	monster2Images[EDirection::EAST] = east2;
	monster2Images[EDirection::NORTH] = north2;
	monster2Images[EDirection::SOUTH] = south2;
	monster2Images[EDirection::WEST] = west2;

	//generates a random number to determine which monster image will be used
	int selectImage = rGen->Next(2);
	Sprite^ monster;

	//determine which image the monster will have
	switch (selectImage)
	{
	case 0://creates a beetle
		if (startXPos != theDungeon->roomList[0]->middleCol * TILESIZE)//make sure monster isn't placed in same x position as player
		{
			monster = gcnew Sprite(gameManagerCanvas, monster1Images, rGen, framesInMonsterSpriteSheet, theTiles, ESpriteType::MONSTER, startXPos, startYPos, monster1HP, monster1HitProb);
		}
		break;
	case 1://creates a ghost
		if (startYPos != startXPos != theDungeon->roomList[0]->middleRow * TILESIZE)//make sure monster isn't placed in same y position as player
		{
			monster = gcnew Sprite(gameManagerCanvas, monster2Images, rGen, framesInMonsterSpriteSheet, theTiles, ESpriteType::MONSTER, startXPos, startYPos, monster2HP, monster2HitProb);
		}
		break;
	}

	return monster; //returns the monster
}

//generate potions
Sprite^ GameManager::generatePotionSprite(int startXPos, int startYPos)
{
	//stats
	int framesInPotionSpriteSheet = 2;
	int directions = 4;
	//populate array with filenames
	String^ east = gcnew String("images/potion.bmp");
	String^ north = gcnew String("images/potion.bmp");
	String^ south = gcnew String("images/potion.bmp");
	String^ west = gcnew String("images/potion.bmp");
	array<String^>^ potionImages = gcnew array<String^>(directions);
	potionImages[EDirection::EAST] = east;
	potionImages[EDirection::NORTH] = north;
	potionImages[EDirection::SOUTH] = south;
	potionImages[EDirection::WEST] = west;

	//return new potion
	return gcnew Sprite(gameManagerCanvas, potionImages, rGen, framesInPotionSpriteSheet, theTiles, ESpriteType::POTION, startXPos, startYPos,0,0);
}

//generate damagers
Sprite^ GameManager::generateDamagerSprite(int startXPos, int startYPos)
{
	//stats
	int framesInDamagerSpriteSheet = 2;
	int directions = 4;
	//populate array with filenames
	String^ east = gcnew String("images/damager.bmp");
	String^ north = gcnew String("images/damager.bmp");
	String^ south = gcnew String("images/damager.bmp");
	String^ west = gcnew String("images/damager.bmp");
	array<String^>^ damagerImages = gcnew array<String^>(directions);
	damagerImages[EDirection::EAST] = east;
	damagerImages[EDirection::NORTH] = north;
	damagerImages[EDirection::SOUTH] = south;
	damagerImages[EDirection::WEST] = west;

	//generate new damager
	return gcnew Sprite(gameManagerCanvas, damagerImages, rGen, framesInDamagerSpriteSheet, theTiles, ESpriteType::DAMAGER, startXPos, startYPos,0,0);

}

//generate treasure
Sprite^ GameManager::generateTreasureSprite(int startXPos, int startYPos)
{
	//stats
	int framesInTreasureSpriteSheet = 2;
	int directions = 4;
	//populate array with filenames
	String^ east = gcnew String("images/treasure.bmp");
	String^ north = gcnew String("images/treasure.bmp");
	String^ south = gcnew String("images/treasure.bmp");
	String^ west = gcnew String("images/treasure.bmp");
	array<String^>^ treasureImages = gcnew array<String^>(directions);
	treasureImages[EDirection::EAST] = east;
	treasureImages[EDirection::NORTH] = north;
	treasureImages[EDirection::SOUTH] = south;
	treasureImages[EDirection::WEST] = west;

	//return new treasure
	return gcnew Sprite(gameManagerCanvas, treasureImages, rGen, framesInTreasureSpriteSheet, theTiles, ESpriteType::TREASURE, startXPos, startYPos,0,0);

}

//generate staircase to next dungeon
Sprite^ GameManager::generateStaircaseSprite(int startXPos, int startYPos)
{
	int framesInStaircaseSpriteSheet = 1;
	int directions = 4;
	String^ east = gcnew String("images/staircase.bmp");
	array<String^>^ staircaseImages = gcnew array<String^>(directions);
	staircaseImages[EDirection::EAST] = east;
	staircaseImages[EDirection::NORTH] = east;
	staircaseImages[EDirection::SOUTH] = east;
	staircaseImages[EDirection::WEST] = east;

	//generate new staircase
	return gcnew Sprite(gameManagerCanvas, staircaseImages, rGen, framesInStaircaseSpriteSheet, theTiles, ESpriteType::STAIRCASE, startXPos, startYPos, 0, 0);

}

//move's the player around the screen
void GameManager::movePlayer()
{
	player->Erase();
	player->Move();
	player->UpdateFrame();
	player->Draw();
	player->changeDir();
}

//sets player's direction
void GameManager::setPlayerDirection(EDirection direction)
{
	player->spriteDirection = direction;
}

//fight method - player fights a monster
void GameManager::fight(Sprite^ theMonster)
{
	//stop player
	player->setXVel(0);
	player->setYVel(0);

	//declare 2 variables to calculate hit probability
	int playerHit, monsterHit; 

	//start combat!
	while ((player->hp > 0) && (theMonster->hp > 0))//player and monster have HP greater than zero
	{
		//determine whether player and monster hit each other
		 playerHit = rGen->Next(player->hitProb);
		 monsterHit = rGen->Next(theMonster->hitProb);
		
		 //player strikes monster
		if ((playerHit == 0) && (monsterHit !=0))//the player strikes!
		{
			int damage = rGen->Next(MINDAMAGE, MAXDAMAGE);
			theMonster->hp -= damage;//decrease monster's HP
			feedback = "You hit the monster and did " + damage + " damage!\nYour HP is " + player->hp + "\nMonster's HP is " + theMonster->hp;
			Thread::Sleep(SLEEPDURATION);//pause for 1 sec so combat doesn't happen instantaneously

		} 

		//monster strikes player
		if ((monsterHit == 0) && (playerHit != 0))
		{
			int damage = rGen->Next(MINDAMAGE, MAXDAMAGE);
			player->hp -= damage;//decrease player's HP
			feedback = "The monster hit you and did " + damage + " damage!\nYour HP is " + player->hp + "\nMonster's HP is " + theMonster->hp;
			Thread::Sleep(SLEEPDURATION);//pause for 1 sec so combat doesn't happen instantaneously
		}

		//if monster and player both strike, they block and no damage is done
		if ((monsterHit == 0) && (playerHit == 0))
		{
			feedback = "You blocked the monster's blow!\nYour HP is " + player->hp + "\nMonster's HP is " + theMonster->hp;
			Thread::Sleep(SLEEPDURATION);//pause for 1 sec
		}

		//monster is killed if HP is less than or equal to zero
	if (theMonster->hp <= 0)
	{
		feedback = "You killed the monster!";
		theMonster->Erase();//erase monster
		monsterList->deleteOneSprite(theMonster);//delete monster from list
		exp += EXPINCREASE;//increase EXP

	}

	//player is killed if HP is less than or equal to zero
	if (player->hp <= 0)
	{
		gameOver = true;//end game
		MessageBox::Show("You died! Game over!");
	}
	feedbackLbl->Text = feedback;//flush buffer
	Application::DoEvents();

	}//end while loop

	//start player walking again
	player->setXVel(PLAYERVELOCITY);
	player->setYVel(PLAYERVELOCITY);

}
//changes the dungeon for the next level
void GameManager::resetDungeon()
{
	
	theTimer->Stop();//stop the timer
	playerHP = player->hp; //store the player's HP so he starts with the same amount of HP he had when he exited the previous level
	player = nullptr;//delete the player
	theDungeon->clearDungeon(numberOfRooms);//clear the dungeon
	numberOfRooms = rGen->Next(MINROOMS, MAXROOMS);//generate new number of rooms
	makeDungeon();//make a new dungeon
	makePlayer();//recreate the player
	setUpGame();//create the items
	theTimer->Start();//start the timer
}