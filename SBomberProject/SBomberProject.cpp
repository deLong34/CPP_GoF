
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;
//========================================================================================================================
//extern FileLogger logger;

int main(void)
{
   FileLogger logger("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

   // MyTools::CloseLogFile();

    return 0;
}
