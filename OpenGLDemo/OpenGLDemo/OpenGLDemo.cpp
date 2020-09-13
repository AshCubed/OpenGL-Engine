#include"Game.h"
using namespace std;


int main(void)
{
    Game game("Hi Ashveer", 640, 480, 3, 3, true);

    //MAIN LOOP
    while (!game.getWindowShouldClose())
    {
        //UDATE INPUT
        game.update();
        game.render();
    }

    glfwTerminate();
    return 0;
}