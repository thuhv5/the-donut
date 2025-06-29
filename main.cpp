#include <QCoreApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //the terminal is 80x24, the pixel is .,-~:;=!*#$@ from dimmest to brightest
    // now build the static simple plate with @
    for (int i = 0; i < 25; ++i)
    {
        for (int j = 0; j < 80; ++j)
            if ((12-i)*(12-i) + (12-j)*(12-j) <= 12*12
                    && (12-i)*(12-i) + (12-j)*(12-j) >= 11*11)
                cout << "@@";
            else
                cout << "  ";
        cout << endl;
    }

    return a.exec();
}
