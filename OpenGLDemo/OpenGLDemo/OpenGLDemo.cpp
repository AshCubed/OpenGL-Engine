#include"Game.h"
#include <string>
#include <iostream>
#include <filesystem>


////Tutorial Used
//Sharma, S. (2020). C++ OpenGL 3D Tutorial - 
//YouTube. [online] www.youtube.com. 
//Available at: https://www.youtube.com/playlist?list=PL6xSOsbVA1eYSZTKBxnoXYboy7wc4yg-Z [Accessed 29 Sep. 2020].


int main(void)
{
    boolean loadGOOD = false;

    string temp;
    cout << "Welcome to engine, made by Ashveer Jugdav 17611612 \n";
    cout << "What level file would you like to load? Please enter the file name or END to exit \n";
    cin >> temp;

    while (loadGOOD == false)
    {
        if (temp == "END")
        {
            cout << "\n Thank you for choosing this engine, Goodbye! \n";
            return 0;
        }
        else {
            temp = "CSVFile/" + temp;
            ifstream input_file(temp);
            if (!input_file.is_open())
            {
                cout << "FILE NO FOUND! \n";
                cout << "What level file would you like to load? Please enter the file name or END to exit \n";
                cin >> temp;
            }
            else {
                loadGOOD = true;
                input_file.close();
            }
        }
    }

    Game game("Ashveer Jugdav 17611612", 640, 480, 3, 3, true, temp);

    cout << "Level Loaded" + temp + "\n";

    //http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/

    //MAIN LOOP
    while (!game.getWindowShouldClose())
    {
        //UDATE INPUT
        game.update();
        game.userCommands();
    }

    //glfwTerminate();
    return 0;
}


