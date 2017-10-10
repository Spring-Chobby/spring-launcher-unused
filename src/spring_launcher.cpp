#include "spring_launcher.h"

#include <QProcess>

SpringLauncher::SpringLauncher(QObject *parent) : QObject(parent)
{
}

void SpringLauncher::Start(const QString& program, const QStringList& args)
{
    myProcess = new QProcess(this);
    connect(myProcess,  static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this,       &SpringLauncher::Finished);
    myProcess->start(program, args);
}

void SpringLauncher::Finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    emit lobbyClosed();
}
