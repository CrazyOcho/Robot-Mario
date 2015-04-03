// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw bouncing ball
// Chapter 6 version 2.0
// Last modification: April-13-2013

#include "gravity.h"

//=============================================================================
// Constructor
//=============================================================================
Gravity::Gravity()
{}

//=============================================================================
// Destructor
//=============================================================================
Gravity::~Gravity()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Gravity::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
    // backdrop texture
    if (!backdropTexture.initialize(graphics,BACKDROP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // ball texture
    if (!ballTexture.initialize(graphics,BALL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball texture"));

    // mario texture
    if (!marioTexture.initialize(graphics,MARIO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));

    // backdrop
    if (!backdrop.initialize(graphics,0,0,0,&backdropTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

    // ball
    if (!ball.initialize(this,ballNS::WIDTH,ballNS::HEIGHT,0,&ballTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));
    ball.setX(GAME_WIDTH/4 - ballNS::WIDTH);
    ball.setY(GAME_HEIGHT/2 - ballNS::HEIGHT);
    ball.setVelocity(VECTOR2(ballNS::SPEED,-ballNS::SPEED)); // VECTOR2(X, Y)

    // mario
	if (!mario.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, 0, &marioTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Gravity::update()
{
	//Both state and direction must be initialized
	State state = STANDING;
	static Direction direction = RIGHT; //Static because direction persists

	if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0))
	{
		state = CROUCHING;
		mario.setCurrentFrame(6);
		mario.setFrames(6, 6);
	}
	else if (input->isKeyDown(LEFT_KEY) || input->getGamepadDPadLeft(0))
	{
		mario.setX(mario.getX() - marioNS::SPEED*frameTime);
		state = WALKING;
		direction = LEFT;
		mario.setFrames(1, 3);
	}
	else if (input->isKeyDown(RIGHT_KEY) || input->getGamepadDPadRight(0))
	{
		mario.setX(mario.getX() + marioNS::SPEED*frameTime);
		state = WALKING;
		direction = RIGHT;
		mario.setFrames(1, 3);
	}
	else
	{
		mario.setCurrentFrame(0);
		mario.setFrames(0,0);
	}
	
	if (input->isKeyDown(UP_KEY) || input->getGamepadDPadDown(0))
	{
		mario.setCurrentFrame(5);
		mario.setFrames(5,5);
		state = JUMPING;
	}

    ball.update(frameTime);
    mario.update(frameTime, state, direction);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Gravity::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Gravity::collisions()
{
    VECTOR2 cv;
    if(ball.collidesWith(mario, cv))
        ball.bounce(cv, mario);
}

//=============================================================================
// Render game items
//=============================================================================
void Gravity::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    backdrop.draw();                        // add the backdrop to the scene
    ball.draw();                            // add the ball to the scene
    mario.draw();                          // add the mario to the scene
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Gravity::releaseAll()
{
    marioTexture.onLostDevice();           // mario texture
    ballTexture.onLostDevice();             // ball texture
    backdropTexture.onLostDevice();         // backdrop texture

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Gravity::resetAll()
{
    backdropTexture.onResetDevice();
    ballTexture.onResetDevice();
    marioTexture.onResetDevice();

    Game::resetAll();
    return;
}
