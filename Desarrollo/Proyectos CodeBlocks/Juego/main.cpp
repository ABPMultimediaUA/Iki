#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

//#include <irrKlang.h>
//#include "lib/irrKlang/conio.h"
#include "Game.h"

//using namespace irrklang;

int main()
{

    Game* game = new Game();
    game->start_game();

}
