#include "spring_launcher.h"

SpringLauncher::SpringLauncher(QObject *parent) : QObject(parent)
{
}

void SpringLauncher::Start()
{
    QString program = "./path/to/Qt/examples/widgets/analogclock";
    QStringList arguments;
    arguments << "-style" << "fusion";
    QProcess *myProcess = new QProcess(parent);
    myProcess->start(program, arguments);
    emit lobbyClosed();
}
