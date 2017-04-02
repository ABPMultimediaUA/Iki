#ifdef _MSC_VER
<<<<<<< HEAD

=======
// We'll define this to stop MSVC complaining about sprintf().
>>>>>>> refs/remotes/origin/master
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
