#include "launcher.h"
#include "chobby_config.h"

#ifdef __linux__
#elif _WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin);
#endif


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
