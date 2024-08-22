#include <QApplication>
#include <QScreen>
#include "snake.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    Snake window;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    window.resize(400,400);
    window.setWindowTitle("Snakinator-3000");
    window.show();

    return app.exec();
}