// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 2.0

#ifndef mario_h             // Prevent multiple definitions if this 
#define mario_h             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace marioNS
{
    const int WIDTH = 50;                  // image width
    const int HEIGHT = 100;                  // image height
    const int X = GAME_WIDTH/4 - WIDTH;     // location on screen
    const int Y = GAME_HEIGHT - HEIGHT * 2;
    const float SPEED = 300;                // pixels per second
    const float MASS = 1.0e6f;
}

// inherits from Entity class
class Mario : public Entity
{
public:
    // constructor
    Mario();

    // inherited member functions
    void update(float frameTime, State state, Direction direction);

	//In case mario collides with a wall
	void Mario::stop(int wallX, int wallY, int wallLength, int wallHeight);
private:
	bool standingOnSurface_ = true;
	bool floorCollision_ = true;
};
#endif

