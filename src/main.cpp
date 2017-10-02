#include "launcher.h"
#include "chobby_config.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    ChobbyConfig::initialize();

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    Launcher w;
    w.show();

    return a.exec();
}
