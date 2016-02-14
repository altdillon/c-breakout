#include "exceptions.h"

using namespace game_exceptions;

SpriteException::SpriteException(string errorMessage)
{
    errorName=errorMessage;
}

void SpriteException::printError() throw()
{
    cout << "sprite exception: " << errorName << endl;
}

SpriteException::~SpriteException() throw()
{

}
