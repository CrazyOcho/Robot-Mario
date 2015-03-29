// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 2.0

#ifndef paddle_h             // Prevent multiple definitions if this 
#define paddle_h             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace paddleNS
{
    const int WIDTH = 50;                  // image width
    const int HEIGHT = 100;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH;     // location on screen
    const int Y = GAME_HEIGHT - HEIGHT;
    const float SPEED = 200;                // pixels per second
    const float MASS = 1.0e6f;
}

// inherits from Entity class
class Paddle : public Entity
{
public:
    // constructor
    Paddle();

    // inherited member functions
    void update(float frameTime, State state, Direction direction);
};
#endif

