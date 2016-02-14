#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <iostream>
#include <exception>
#include <cstdlib>
#include <allegro5/allegro.h>
#include <fstream>

using namespace std;

namespace game_exceptions
{
    //throws exceptions for inut events
    class InutException: public exception
    {
    public:
        InutException(string errorMessage);
        void printError() /*const*/ throw ();
        virtual ~InutException() /*const*/ throw();
    private:
        string errorName;
    };

    //throws exceptions for sprites
    class SpriteException : public exception
    {
    public:
        SpriteException(string errorMessage);
        void printError() throw();
        virtual ~SpriteException() throw();
    private:
        string errorName;
    };

}

#endif
