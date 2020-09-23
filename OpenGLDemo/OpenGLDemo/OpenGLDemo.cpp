#include"Game.h"
using namespace std;


int main(void)
{
    Game game("Hi Ashveer", 640, 480, 3, 3, true);

    //string temp;
    //cout << "Enter a command:.\n ";
    //cin >> temp;
    //cout << "beep: " + temp + "\n";

    //http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/

    //MAIN LOOP
    while (!game.getWindowShouldClose())
    {
        //UDATE INPUT
        game.update();
        game.render();
        //game.fpsCounter();
        
    }

    glfwTerminate();
    return 0;
}

