#include <QCoreApplication>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#define RX 0.5 // dãn trục mặc định

void clearScreen()
{
    // \033[2J: Xóa toàn bộ màn hình
    // \033[H : Di chuyển con trỏ về góc trên bên trái (tọa độ 0,0)
    // std::cout << "\033[2J\033[H" << std::flush;
    system("cls");
}

bool isInsideDonut(double x, double y, double alpha)
{
    // 1. Áp dụng tỷ lệ dãn trục mặc định cho tọa độ màn hình x
    x *= RX;

    double r1 = 12;
    double r2 = 9;
    double xCenter = 12;  // ứng với x màn hình thực tế là 24 (vì 24 * 0.5 = 12)
    double yCenter = 12;

    // 2. Tính khoảng cách tương đối từ điểm đang xét tới TÂM donut
    double xCentered = x - xCenter;
    double yCentered = y - yCenter;

    // 3. Thực hiện PHÉP QUAY quanh trục đứng (Trục Y)
    // Khi xoay quanh trục Y, khoảng cách theo trục X toán học sẽ co giãn theo cos(alpha)
    double xRotated = xCentered / cos(alpha);

    // 4. Phương trình donut sau khi đã xoay
    double distanceSquared = xRotated * xRotated + yCentered * yCentered;

    if (distanceSquared <= r1 * r1 && distanceSquared >= r2 * r2)
        return true;
    return false;
}

void renderFrame(double alpha)
{
    for (int y = 0; y < 30 - 1; ++y)  // in theo dòng để xuống dòng, -1 để đỡ phải cuộn chuột lên, _ ko ra khỏi khung view
    {
        for (int x = 0; x < 60 - 1; ++x)
        {
            // rx < 1: co theo trục x vì chiều rộng ký tự ~ 1/2 chiều cao ký tự, trục x giờ sẽ nhiều ký tự gấp đôi y
            if (isInsideDonut(x, y, alpha))
                cout << "@";
            else
                cout << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //the terminal is 120x30 for qt-cmd on windows, the pixel is .,-~:;=!*#$@ from dimmest to brightest
    // now build the static simple plate with @

//    • Công thức: (x - a)^2 + (y - b)^2 = R^2
//    • Trong đó:
//        • Tâm đường tròn là I(a; b).
//        • Bán kính là R > 0.

    double alpha = 0.0; // rad
    while (true)
    {
        renderFrame(alpha);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        clearScreen();
        alpha += 0.1;
    }

    return a.exec();
}
