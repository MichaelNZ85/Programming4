///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpriteList.cpp
// SpriteList CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SpriteList.h"
#include "Sprite.h"

//constructor
SpriteList::SpriteList()
{
	head = nullptr;
	tail = nullptr;
}

//add a Sprite 
void SpriteList::addSprite(Sprite^ newSprite)
{
	if (head == nullptr)
	{
		head = newSprite;
		tail = newSprite;
	}
	else
	{
		tail->Next = newSprite;
		tail = newSprite;
	}
}
//delete one Sprite
void SpriteList::deleteOneSprite(Sprite^ SpriteToDelete)
{
	Sprite^ nodeWalker;
	nodeWalker = head;

	if (nodeWalker->Next == nullptr)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (SpriteToDelete == nodeWalker)
	{
		head = nodeWalker->Next;
	}
	else if (SpriteToDelete->Next == nullptr)
	{
		while (nodeWalker->Next != SpriteToDelete)
		{
			nodeWalker = nodeWalker->Next;
		}
		tail = nodeWalker;
		tail->Next = nullptr;
	}
	else {
		while (nodeWalker->Next != SpriteToDelete)//find Sprite before SpriteToDelete
		{
			nodeWalker = nodeWalker->Next;
		}
		//found it
		nodeWalker->Next = SpriteToDelete->Next;
	}
}


//deletes all the dead Sprites
void SpriteList::deleteAllDeadSprites()
{
	Sprite^ nodeWalker = head;
	int count = 0;
	while (nodeWalker != nullptr)
	{
		if (nodeWalker->isAlive == false){
			deleteOneSprite(nodeWalker);
		}
		nodeWalker = nodeWalker->Next;
		count++;
	}
}

//move the Sprites upward
void SpriteList::moveSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		bool outOfBounds;
		nodeWalker->Move();
		/*outOfBounds = nodeWalker->CheckOutOfBounds();
		if (outOfBounds == true)
		{
			nodeWalker->UpdateOnOutOfBounds();
		}*/
		nodeWalker = nodeWalker->Next;
	}
}


//draw the Sprites to the screen
void SpriteList::drawSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Erase();
		nodeWalker->Draw();
		nodeWalker->UpdateFrame();

		nodeWalker = nodeWalker->Next;
	}
}
//make the sprites wander - not used
void SpriteList::wanderSprites()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->Wander();
		nodeWalker->Move();
		nodeWalker = nodeWalker->Next;
	}
}
//change the sprites' direction
void SpriteList::changeSpritesDir()
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		nodeWalker->changeDir();
		nodeWalker = nodeWalker->Next;
	}
}


//count the Sprites
int SpriteList::countSprites()
{
	Sprite^ nodeWalker = head;
	int count = 0;
	while (nodeWalker != nullptr)
	{
		count++;
		nodeWalker = nodeWalker->Next;
	}

	return count;
}
//check sprites for collision
Sprite^ SpriteList::checkCollision(Sprite^ otherGuy)
{
	Sprite^ nodeWalker;
	nodeWalker = head;
	while (nodeWalker != nullptr)
	{
		if (nodeWalker->CollidedWithMe(otherGuy))//calls sprite's collision detection method
		{
			return nodeWalker;
		}

		nodeWalker = nodeWalker->Next;
	}
	return nullptr;
}