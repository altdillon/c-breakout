#include "game_elements.h"

using namespace game_elements;

void Ball::bounceX()
{
    vectorX=vectorX*-1;
}

void Ball::bounceY()
{
    vectorY=vectorY*-1;
}

void Ball::nextPos()
{
    sp_pos.x+=vectorX;
    sp_pos.y+=vectorY;
}

bool Ball::hitFloor()
{
    bool did_hit_floor=false;

    if(sp_pos.y>=(screenSizeY-5))
    {
        did_hit_floor=true;
    }

    return did_hit_floor;
}

bool Ball::hitWall()
{
    bool did_hit=false;

    if(sp_pos.x < 0 || sp_pos.x > (this->screenSizeX-sprite_sizeX))
    {
        this->bounceX();
        did_hit=true;
    }

    if(sp_pos.y < 0 || sp_pos.y > (this->screenSizeY-sprite_sizeY))
    {
        this->bounceY();
        did_hit=true;
    }

    return did_hit;
}

void Ball::changeSpeed(float speedX,float speedY)
{
    vectorX=speedX;
    vectorY=speedX;
}
void Ball::deflectOffBat()
{
    //vectorX=vectorX*-1;
    vectorY=vectorY*-1;
}

void Ball::ballDeflectOffBlock()
{
    //vectorX=vectorX*-1;
    vectorY=vectorY*-1;
}
