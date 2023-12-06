#include <conio.h>

#include "./src/test/simpleWindow/SimpleWindow.h"
#include "./src/test/triangle/Triangle.h"
#include "./src/test/rectangle/Rectangle.h"
#include "./src/test/cube/Cube.h"
#include "./src/test/lighting/Lighting.h"
#include "./src/test/maths/Maths.h"
#include "./src/test/loadModel/LoadModel.h"
#include "./src/test/textRendering/TextRendering.h"

using namespace std;

int main(void)
{
    cout << "Welcome to examples opengl learning." << '\n';

    while (true)
    {
        cout << "Select number to init example:\n\n";
        cout << "1 - Simple windows\n";
        cout << "2 - Triangle\n";
        cout << "3 - Rectangle\n";
        cout << "4 - Cube\n";
        cout << "5 - Lighting\n";
        cout << "6 - Maths\n";
        cout << "7 - Load models\n";
        cout << "8 - Text rendering\n\n";
        cout << "10 - Exit\n";
        cout << "Digit your option: ";

        int option = 0;
        cin >> option;
        cout << '\n';

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
        else if (option == 8)
            textRendering();
        else if (option == 10)
            break;

        system("cls");
    }

    cout << "Created by: SYSMA\n";

    return 0;
}