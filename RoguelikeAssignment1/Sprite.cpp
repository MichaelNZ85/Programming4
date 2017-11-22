///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprite.cpp
// Sprite CPP File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Sprite.h"


//first constructor
Sprite::Sprite(Graphics^ startCanvas, array<String^>^ startFileNames, Random^ startRGen, int startNFrames, Tilemap^ startTilemap, ESpriteType startSpriteType)
{
	canvas = startCanvas;
	//load sprite sheets
	spriteSheets = gcnew array<Bitmap^>(SPRITESHEETS);
	for (int i = 0; i < SPRITESHEETS; i++)
	{
		spriteSheets[i] = gcnew Bitmap(startFileNames[i]);
		spriteSheets[i]->MakeTransparent(spriteSheets[i]->GetPixel(0, 0));
	}
	rGen = startRGen;
	nFrames = startNFrames;
	currentFrame = 0;
	frameHeight = spriteSheets[0]->Height;
	frameWidth = (int)spriteSheets[0]->Width / nFrames;
	xPos = 300;
	yPos = 300;
	xVel = 5;
	yVel = 5;
	spriteDirection = EDirection::EAST;
	spriteType = startSpriteType;
	boundingRectangle = Rectangle(0, 0, FORMWIDTH, FORMHEIGHT);
	isAlive = true;
	hp = 0;

	//set directions
	velocityDirections = gcnew array<Point>(DIRECTIONS);
	velocityDirections[0] = Point(1, 0); //east
	velocityDirections[1] = Point(0, 1);//south
	velocityDirections[2] = Point(-1, 0);//west
	velocityDirections[3] = Point(0, -1);//north

	//set points for collision detection
	topLeft = Point(xPos, yPos);
	topRight = Point(xPos + frameWidth, yPos);
	bottomLeft = Point(xPos, yPos + frameHeight);
	bottomRight = Point(xPos + frameWidth, yPos + frameHeight);

}

//second constructor - used exclusively in this game
Sprite::Sprite(Graphics^ startCanvas, array<String^>^ startFileNames, Random^ startRGen, int startNFrames, Tilemap^ startTilemap, ESpriteType startSpriteType, int startXPos, int startYPos, int startHP, int startHitProb)
{
	canvas = startCanvas;
	//set sprite sheets
	spriteSheets = gcnew array<Bitmap^>(SPRITESHEETS);
	for (int i = 0; i < SPRITESHEETS; i++)
	{
		spriteSheets[i] = gcnew Bitmap(startFileNames[i]);
		spriteSheets[i]->MakeTransparent(spriteSheets[i]->GetPixel(0, 0));
	}
	rGen = startRGen;
	nFrames = startNFrames;
	currentFrame = 0;
	frameHeight = spriteSheets[0]->Height;
	frameWidth = (int)spriteSheets[0]->Width / nFrames;
	xPos = startXPos;
	yPos = startYPos;
	xVel = 5;
	yVel = 5;
	spriteDirection = EDirection::EAST;
	spriteType = startSpriteType;
	isAlive = true; 
	theTiles = startTilemap;
	hp = startHP;
	hitProb = startHitProb;
	

	velocityDirections = gcnew array<Point>(DIRECTIONS);
	velocityDirections[0] = Point(1, 0); //east
	velocityDirections[1] = Point(0, 1);//south
	velocityDirections[2] = Point(-1, 0);//west
	velocityDirections[3] = Point(0, -1);//north

	//points for collision detection
	topLeft = Point(xPos, yPos);
	topRight = Point(xPos + frameWidth, yPos);
	bottomLeft = Point(xPos, yPos + frameHeight);
	bottomRight = Point(xPos + frameWidth, yPos + frameHeight);
}

//constructor call for using bounding rectangle - not used
Sprite::Sprite(Graphics^ startCanvas, array<String^>^ startFileNames, Random^ startRGen, int startNFrames, Tilemap^ startTilemap, ESpriteType startSpriteType, int startXPos, int startYPos, int startBRX, int startBRY, int startBRWidth, int startBRHeight)
{
	canvas = startCanvas;
	spriteSheets = gcnew array<Bitmap^>(SPRITESHEETS);
	for (int i = 0; i < SPRITESHEETS; i++)
	{
		spriteSheets[i] = gcnew Bitmap(startFileNames[i]);
		spriteSheets[i]->MakeTransparent(spriteSheets[i]->GetPixel(0, 0));
	}
	rGen = startRGen;
	nFrames = startNFrames;
	currentFrame = 0;
	frameHeight = spriteSheets[0]->Height;
	frameWidth = (int)spriteSheets[0]->Width / nFrames;
	xPos = startXPos;
	yPos = startYPos;
	xVel = 5;
	yVel = 5;
	spriteDirection = EDirection::EAST;
	spriteType = startSpriteType;
	boundingRectangle = Rectangle(startBRX, startBRY, startBRWidth, startBRHeight);

	isAlive = true;
	hp = 0;


	velocityDirections = gcnew array<Point>(DIRECTIONS);
	velocityDirections[0] = Point(1, 0); //east
	velocityDirections[1] = Point(0, 1);//south
	velocityDirections[2] = Point(-1, 0);//west
	velocityDirections[3] = Point(0, -1);//north

	topLeft = Point(xPos, yPos);
	topRight = Point(xPos + frameWidth, yPos);
	bottomLeft = Point(xPos, yPos + frameHeight);
	bottomRight = Point(xPos + frameWidth, yPos + frameHeight);
}
//Draws the Sprite to the screen
void Sprite::Draw()
{
	int currFrameX = currentFrame * frameWidth;
	int currFrameY = 0;
	Rectangle drawRect = Rectangle(currFrameX, currFrameY, frameWidth, frameHeight);

	Bitmap^ currentBitmap = spriteSheets[spriteDirection];

	canvas->DrawImage(currentBitmap, xPos, yPos, drawRect, GraphicsUnit::Pixel);
	Pen^ myPen = gcnew Pen(Color::Black);
	canvas->DrawRectangle(myPen, boundingRectangle);
}

//erases the sprite
void Sprite::Erase()
{
	Color c = spriteSheets[0]->GetPixel(0, 0);
	spriteSheets[0]->MakeTransparent(c);
}

//moves the sprite
void Sprite::Move()
{
	int newX = 0;
	int newY = 0;
	int directionCornerX = 0;
	int directionCornerY = 0;
	int row = 0;
	int col = 0;

	//check whether next tile is walkable
	switch (spriteDirection)
	{
	case EDirection::NORTH:
		//create new x and y positions
		newX = xPos + (xVel * velocityDirections[spriteDirection].X);
		newY = yPos + (yVel * velocityDirections[spriteDirection].Y);

		//top left corner
		directionCornerX = newX;
		directionCornerY = newY;

		//translates x and y into tilemap co-ordinates
		col = directionCornerX / TILESIDE;
		row = directionCornerY / TILESIDE;
		//if tile is walkable
		if (theTiles->IsTileWalkable(col, row) == true)
		{
			//sprite moves to new positions
			xPos = newX;
			yPos = newY;
		}
	case EDirection::EAST:
		//create new x and y positions
		newX = xPos + (xVel * velocityDirections[spriteDirection].X);
		newY = yPos + (yVel * velocityDirections[spriteDirection].Y);

		//lower right corner
		directionCornerX = newX + frameWidth;
		directionCornerY = newY; //previously was directionCornerY = newY + frameHeight;
		
		//translates x and y into tilemap co-ordinates
		col = directionCornerX / TILESIDE;
		row = directionCornerY / TILESIDE;
		
		//if tile is walkable
		if (theTiles->IsTileWalkable(col, row) == true)
		{
			//sprite moves to new positions
			xPos = newX;
			yPos = newY;
		}
	case EDirection::SOUTH:
	case EDirection::WEST:
		//create new x and y positions
		newX = xPos + (xVel * velocityDirections[spriteDirection].X);
		newY = yPos + (yVel * velocityDirections[spriteDirection].Y);

		//lower left corner
		directionCornerX = newX;
		directionCornerY = newY + frameHeight;

		//translates x and y into tilemap co-ordinates
		col = directionCornerX / TILESIDE;
		row = directionCornerY / TILESIDE;

		//if tile is walkable
		if (theTiles->IsTileWalkable(col, row) == true)
		{
			//sprite moves to new position
			xPos = newX;
			yPos = newY;
		}

	}
}

//checks whether sprite is out of bounds
bool Sprite::CheckOutOfBounds()
{
	bool outOfBounds = false;
	if ((xPos < boundingRectangle.Left) || ((xPos + frameWidth) > boundingRectangle.Right) || (yPos < boundingRectangle.Top) || ((yPos + frameHeight) > boundingRectangle.Bottom))
	{
		outOfBounds = true;
	}

	return outOfBounds;
}

//updates the frame to cause animation
void Sprite::UpdateFrame()
{
	currentFrame = (currentFrame + 1) % nFrames;
}

//sets a new set of sprite sheets - not used
void Sprite::SetSpriteSheets(array<String^>^ newFileNames, int newNFrames)
{
	spriteSheets = gcnew array<Bitmap^>(DIRECTIONS);
	for (int i = 0; i < 4; i++)
	{
		spriteSheets[i] = gcnew Bitmap(newFileNames[i]);
		spriteSheets[i]->MakeTransparent(spriteSheets[i]->GetPixel(0, 0));
	}

	nFrames = newNFrames;
	frameWidth = spriteSheets[0]->Width / nFrames;
	frameHeight = spriteSheets[0]->Height;

}

//changes direction
void Sprite::changeDir()
{

	if (xPos <= 0)
	{
		spriteDirection = EDirection::EAST;
	}
	if ((xPos + frameWidth) >= FORMWIDTH)
	{
		spriteDirection = EDirection::WEST;
	}

	if (yPos <= 0)
	{
		spriteDirection = EDirection::SOUTH;
	}
	if ((yPos + frameHeight) >= FORMHEIGHT)
	{
		spriteDirection = EDirection::NORTH;
	}
}

//wander method - not used
void Sprite::Wander()
{
	int wanderProb = 5;
	int prob = rGen->Next(wanderProb);
	if (prob == 0)
	{
		if (spriteDirection = EDirection::EAST)
		{
			spriteDirection = EDirection::WEST;
		}
		else
		{
			spriteDirection = EDirection::EAST;
		}
	}
	int prob2 = rGen->Next(wanderProb);
	if (prob2 == 0)
	{
		if (spriteDirection = EDirection::NORTH)
		{
			spriteDirection = EDirection::SOUTH;
		}
		else
		{
			spriteDirection = EDirection::NORTH;
		}
	}
}

//collision detection method
bool Sprite::CollidedWithMe(Sprite^ otherGuy)
{
	bool collided = true;

	//determine points for collision detection
	topLeft = Point(xPos, yPos);
	topRight = Point(xPos + frameWidth, yPos);
	bottomLeft = Point(xPos, yPos + frameHeight);
	bottomRight = Point(xPos + frameWidth, yPos + frameHeight);

	//determine sprite to check's points for collision detection
	otherGuy->topLeft = Point(otherGuy->xPos, otherGuy->yPos);
	otherGuy->topRight = Point(otherGuy->xPos + otherGuy->frameWidth, otherGuy->yPos);
	otherGuy->bottomLeft = Point(otherGuy->xPos, otherGuy->yPos + otherGuy->frameHeight);
	otherGuy->bottomRight = Point(otherGuy->xPos + otherGuy->frameWidth, otherGuy->yPos + otherGuy->frameHeight);

	//check sprites to see if they have collided - 0.3 is to shrink rectangle
	if ((topLeft.X + (0.3 * frameWidth)> otherGuy->topRight.X + (0.3 * frameWidth)))
	{
		collided = false;
	}
	if ((topLeft.Y + (0.3 * frameHeight) > (otherGuy->bottomLeft.Y + (0.3 * frameHeight))))
	{
		collided = false;
	}
	if (topRight.X + (0.3 * frameWidth) < (otherGuy->topLeft.X + 0.3 * frameWidth))
	{
		collided = false;
	}
	if ((bottomLeft.Y + (0.3 * frameHeight) < otherGuy->topLeft.Y + (0.3 * frameHeight)))
	{
		collided = false;
	}

	return collided;

}
//changes the sprite's images
void Sprite::ChangeImages(array<String^>^ names)
{
	for (int i = 0; i < 4; i++)
	{
		spriteSheets[i] = gcnew Bitmap(names[i]);
		spriteSheets[i]->MakeTransparent(spriteSheets[i]->GetPixel(0, 0));
	}
}
//calculates height and width of frame
void Sprite::ComputeFrameHeightAndWidth()
{
	frameHeight = spriteSheets[0]->Height;
	frameWidth = (int)spriteSheets[0]->Width / nFrames;
}