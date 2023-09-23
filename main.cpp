#include <conio.h>

#include "./src/test/simpleWindow/SimpleWindow.h"
#include "./src/test/triangle/Triangle.h"
#include "./src/test/rectangle/Rectangle.h"
#include "./src/test/cube/Cube.h"
#include "./src/test/lighting/Lighting.h"
#include "./src/test/maths/Maths.h"
#include "./src/test/loadModel/LoadModel.h"

using namespace std;

int main(void)
{
    cout << "Welcome to examples opengl learning." << endl;

    while (true)
    {
        int option = 0;

        cout << "Select number to init example:" << endl
             << endl;
        cout << "1 - Simple windows" << endl;
        cout << "2 - Triangle" << endl;
        cout << "3 - Rectangle" << endl;
        cout << "4 - Cube" << endl;
        cout << "5 - Lighting" << endl;
        cout << "6 - Maths" << endl;
        cout << "7 - Load models" << endl;
        cout << endl
             << "10 - Exit" << endl;
        cout << "Digit your option: ";
        cin >> option;
        cout << endl;

        if (option == 1)
            simpleWindow();
        else if (option == 2)
            triangle();
        else if (option == 3)
            rectangle();
        else if (option == 4)
            cube();
        else if (option == 5)
            lighting();
        else if (option == 6)
        {
            vectors();

            getch();
        }
        else if (option == 7)
            loadModel();
        else if (option == 10)
            break;

        system("cls");
    }

    cout << "Created by: SYSMA" << endl;

    return 0;
}