#include "./exceptions.h"

using namespace std;
using namespace game_exceptions;

InutException::InutException(string errorMessage)
{
    errorName=errorMessage;
}

void InutException::printError() throw()
{
    cout << "excpetion thrown" << errorName << endl;
}

InutException::~InutException() throw()
{

}
