///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpriteList.h
// SpriteList Header File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Sprite.h"
//Sprite list class
ref class SpriteList
{
private:
	//head and tail pointers
	Sprite^ head;
	Sprite^ tail;
public:
	SpriteList(void);
	void addSprite(Sprite^ newSprite);
	void deleteOneSprite(Sprite^ spriteToDelete);
	void deleteAllDeadSprites();
	void moveSprites();
	void wanderSprites();
	void changeSpritesDir();
	void drawSprites();
	int countSprites();
	Sprite^ checkCollision(Sprite^ otherGuy);//check collisions with other sprite

};