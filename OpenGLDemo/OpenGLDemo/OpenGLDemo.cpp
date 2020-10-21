#include"Game.h"
using namespace std;

////Tutorial Used
//Sharma, S. (2020). C++ OpenGL 3D Tutorial - 
//YouTube. [online] www.youtube.com. 
//Available at: https://www.youtube.com/playlist?list=PL6xSOsbVA1eYSZTKBxnoXYboy7wc4yg-Z [Accessed 29 Sep. 2020].


int main(void)
{
    Game game("Hi Ashveer", 640, 480, 3, 3, true);

    


    //http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/



    //MAIN LOOP
    while (!game.getWindowShouldClose())
    {
        //UDATE INPUT
        game.update();
        game.render();
        game.userCommands();
    }

    //glfwTerminate();
    return 0;
}

